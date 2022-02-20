/***************************************************************************
                          MotionReceiver.cxx  -  description
                             -------------------
    begin                : Thu Feb 7 2002
    copyright            : (C) 2002 by Olaf Stroosma
    email                : stroosma@srshost
 ***************************************************************************/

#include "MotionReceiver.hxx"

#include <iostream>

// serial port
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cassert>

//memcpy
#include <string.h>
#include <errno.h>

//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug-direct.h>

#ifndef B460800
#warning "Baudrate define not specified, assuming a value"
#define  B460800 460800
#endif

MotionReceiver::MotionReceiver():
good_packet_count(0), bad_packet_count(0)
{
  // open the serial port
  fd = open("/dev/ttyS05", O_RDONLY | O_NOCTTY);
  
  if(fd == -1) {
    E_MOD("MotionLimiter couldn't open ttyS05");
    // throw something ...
    return;
  }
  else {
    I_MOD("MotionLimiter opened ttyS05 with fd: " << fd);
  }

  // configure the thing...
  // baudrate
  struct termios options;
  
  tcgetattr(fd, &options);
  
  cfsetispeed(&options, B460800);
  cfsetospeed(&options, B460800);
  
  options.c_cflag |= (CLOCAL | CREAD);
  
  // no parity
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  
  // disable hardware flow control
  options.c_cflag &= ~CRTSCTS;
  
  // raw input
  cfmakeraw(&options);

  // no software flow control
  options.c_iflag &= ~(IXON | IXOFF | IXANY);

  // set it
  tcsetattr(fd, TCSANOW, &options);
  
  // set blocking
  //fcntl(fd, F_SETFL, 0);
  
  // sync word
  uint32_t syncword = 0x0FF0CC33;
  memcpy(&buffer[0], &syncword, 4);
  
  // set the scaling and offset values
  /* scaling, per float value */
  /* assumptions: pos [m]:           -5 .. 5    */
  /*              att [rad]:         -1 .. 1    */
  for(int i=0; i<3; i++) {
    scaling[i]    = 429496729.50; /* x/y/z */
    scaling[3+i]  = 2147483647.5; /* phi/theta/psi */
    scaling[6+i]  = 3067833782.14; /* act. lengths */
    scaling[9+i]  = 3067833782.14; /* act. lengths */

    offset[i]     = 5.0; /* x/y/z */
    offset[3+i]   = 1.0; /* phi/theta/psi */
    offset[6+i]   = 0.7; /* act. lengths */ 
    offset[9+i]   = 0.7; /* act. lengths */ 
  }
}

MotionReceiver::~MotionReceiver()
{
  // close the serial port
  close(fd);
}

bool MotionReceiver::isPrepared()
{
  bool prep = (fd >= 0);
  
  return prep;
}

int MotionReceiver::read(MotionBaseResultData& mbrd)
{
  assert(fd >= 0);
  
  union {
    char c[RECEIVEBUFFERLEN];
    uint32_t w[RECEIVEBUFFERLEN/4];
  } buf;
  int n;
  int to_read = RECEIVEBUFFERLEN;
  uint32_t checksum;
  
  // fill the buffer from the serial FIFO, stripping the sync and checksum

  // assemble packet, in fragments if needed
  // TODO handle lost sync!
  /*
  while (to_read > 0) {

    n = ::read(fd, &buf.c[RECEIVEBUFFERLEN-to_read], to_read);
  
    if( n < 0) {
      if( errno == EINTR ){
	I_MOD("MCC2Host comms interrupted by signal");}
      else {
	W_MOD("MCC2Host comms error: " << strerror(errno));}
      break;
    }

    // n down, how many to go?
    to_read -= n;

#ifdef D_MOD_ACTIVE  
    if (n < RECEIVEBUFFERLEN){
      if(to_read > 0) {
	D_MOD("MCC2Host comms read incomplete packet (" << n << " bytes), waiting for " 
	      << to_read << " more");
      } else {
	D_MOD("MCC2Host comms read remainder of incomplete packet (" << n << " bytes)"); 
      }      
    }
#endif
  }
  */

  n = readPacket(&buf.c[0], to_read);
    
  if(to_read == 0) { // full packet was read, no premature exit

#ifdef REMOTELOOPBACK
    // debug: print whole packet    
    for(int i=0;i<RECEIVEBUFFERLEN/4;i++) {
      D_MOD("Received [" << dec<< i << "]:" << hex << buf.w[i] << dec);
    }
    
    // check sync
    if( buf.w[0] == 0x00FF8877) {
      D_MOD("Sync detected!");}
    else {
      D_MOD("Expected sync (0x00FF8877), but received: " << hex << buf.w[0] << dec);
    }

    // check checksum
    checksum = cs.calculate(&buf.c[0],RECEIVEBUFFERLEN-4);
    if( buf.w[RECEIVEBUFFERLEN/4-1] == checksum) {
      D_MOD("Checksum word received OK:" << hex << checksum << dec);
    }
    else {
      D_MOD("Expected checksum: " << hex << checksum <<
	    " , but received: " << hex << buf.w[RECEIVEBUFFERLEN/4-1] << dec);}
#else

    // check sync
    if( buf.w[0] != 0x0FF0CC33) {
      W_MOD("MCC2Host comms: Expected sync word, but received: " << hex << buf.w[0] << dec);
      // TODO: tally this error and panic if it happens too often.
      // TODO: rest of packet is probably rubbish as well...

      // recover sync by continued reading until new sync word 
      int n_tries = 0;
      union {
	char c[4];
	uint32_t w;
      } sync_buf; // read buffer to use during sync search
      sync_buf.w = 0x00000000;

      while(sync_buf.w != 0x0FF0CC33 && n_tries < 2*RECEIVEBUFFERLEN) {
	memmove(&sync_buf.c[0], &sync_buf.c[1],3);
	::read(fd, &sync_buf.c[3], 1);
	n_tries++;
      }
      if(sync_buf.w == 0x0FF0CC33) {
	I_MOD("MCC2Host recovered sync after " << n_tries << " bytes");
	// continue as normal, first copying over sync word to regular buffer
	memcpy(&buf.c[0], &sync_buf.c[0], 4);

	// read remainder of packet
	to_read = RECEIVEBUFFERLEN-4;
	n = readPacket(&buf.c[0], to_read);
      } else {
	W_MOD("MCC2Host did not recover sync after " << n_tries << " bytes");
	// better luck next time...
      }
   }
    
    // check checksum and process packet if OK
    checksum = cs.calculate(&buf.c[0],RECEIVEBUFFERLEN-4);
    
    if( buf.w[RECEIVEBUFFERLEN/4-1] == checksum) {
      int i = 0;

      // fill mbrd from buffer, using offset and scaling
      mbrd.counter = buf.w[1];
      mbrd.status = buf.w[2];
      for (i=0;i<6;i++)
	mbrd.actual_pos[i] = ((float)buf.w[3+i]/scaling[i]-offset[i]);
      for (i=0;i<6;i++)
	mbrd.actual_len[i] = ((float)buf.w[9+i]/scaling[6+i]-offset[6+i]);
      
      good_packet_count++;
    }
    else {
      W_MOD("MCC2Host comms: Expected checksum: " << hex << checksum <<
	    " , but received: " << hex << buf.w[RECEIVEBUFFERLEN/4-1] << dec);
      // TODO: tally this error and panic if it happens too often.
      bad_packet_count++;
      W_MOD("MCC2Host comms: bad packet rate: " <<
	    bad_packet_count/(bad_packet_count+good_packet_count)*100.0 << "%");
    }
#endif

    // return the total number of bytes read, supposedly a full packet
    return RECEIVEBUFFERLEN;

  } else { // premature exit from reading loop, error is still in variable n
    return n;
  }
}

// read (remainder of) packet from serial,
// possibly starting later in the packet (e.g. after sync word following sync recovery),
// but always up to the end
int MotionReceiver::readPacket(char* buffer, int& bytes_to_read)
{
  int n = 0;

  while (bytes_to_read > 0) {

    n = ::read(fd, &buffer[RECEIVEBUFFERLEN-bytes_to_read], bytes_to_read);
  
    if( n < 0) {
      if( errno == EINTR ){
	I_MOD("MCC2Host comms interrupted by signal");}
      else {
	W_MOD("MCC2Host comms error: " << strerror(errno));}
      break;
    }

    // n down, how many to go?
    bytes_to_read -= n;

#ifdef D_MOD_ACTIVE  
    if (n < RECEIVEBUFFERLEN){
      if(bytes_to_read > 0) {
	D_MOD("MCC2Host comms read incomplete packet (" << n << " bytes), waiting for " 
	      << bytes_to_read << " more");
      } else {
	D_MOD("MCC2Host comms read remainder of incomplete packet (" << n << " bytes)"); 
      }      
    }
#endif
  }
  
  return n;
}
  
