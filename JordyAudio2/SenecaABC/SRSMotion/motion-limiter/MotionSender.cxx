/***************************************************************************
                          MotionSender.cxx  -  description
                             -------------------
    begin                : Thu Feb 7 2002
    copyright            : (C) 2002 by Olaf Stroosma
    email                : stroosma@srshost
 ***************************************************************************/

#include "MotionSender.hxx"

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
#warning "B460800 define not specified, assuming a value"
#define  B460800 460800
#endif

MotionSender::MotionSender()
{
  
  // open the serial port
  fd = open("/dev/ttyS04", O_WRONLY | O_NOCTTY | O_NDELAY);
  
  if(fd == -1) {
    E_MOD("MotionLimiter couldn't open ttyS04");
    return;
    
    // throw something ...
  }
  else {
    I_MOD("MotionLimiter opened ttyS04 with fd: " << fd);
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
  
  // raw output
  cfmakeraw(&options);
  
  // set it
  tcsetattr(fd, TCSANOW, &options);

  // sync word
  uint32_t syncword = 0x00FF8877;
  memcpy(&buffer[0], &syncword, 4);
  
  // set the scaling and offset values
  /* scaling, per float value */
  /* assumptions: pos [m]:           -5 .. 5    */
  /*              att [rad]:         -1 .. 1    */
  /*              posvel [m/s]:      -5 .. 5    */
  /*              attvel [rad/s]:    -1 .. 1    */
  /*              posacc [m/s2]:     -30 .. 30  */
  /*              attacc [rad/s2]:   -25 .. 25  */
  for(int i=0; i<3; i++)
    {
		scaling[i]    = 429496729.50; /* x/y/z */
		scaling[3+i]  = 2147483647.5; /* phi/theta/psi */
		scaling[6+i]  = 429496729.50; /* xdot/ydot/zdot */
		scaling[9+i]  = 2147483647.5; /* phidot/thetadot/psidot or p/q/r*/
		scaling[12+i] = 71582788.25; /* xdot/ydot/zdot */
		scaling[15+i] = 85899345.9; /* phidotdot/thetadotdot/psidotdot or pdot/qdot/rdot */

		offset[i]     = 5.0; /* x/y/z */
		offset[3+i]   = 1.0; /* phi/theta/psi */
		offset[6+i]   = 5.0; /* xdot/ydot/zdot */
		offset[9+i]   = 1.0; /* phidot/thetadot/psidot or p/q/r*/
		offset[12+i]  = 30.0; /* xdot/ydot/zdot */
		offset[15+i]  = 25.0; /* phidotdot/thetadotdot/psidotdot or pdot/qdot/rdot */
	}

	// prepare the standard packet buffers
	uint32_t dummy;

	// counter (overwritten every time)
	dummy = 0;
	memcpy(&shutdownbuffer[0], &dummy, 4);
	memcpy(&downbuffer[0], &dummy, 4);
	memcpy(&neutralbuffer[0], &dummy, 4);
	memcpy(&cuebuffer[0], &dummy, 4);
	memcpy(&errorbuffer[0], &dummy, 4);

	// command
	dummy = CMD_SHUTDOWN;
	memcpy(&shutdownbuffer[4], &dummy, 4);
	dummy = CMD_DOWNANDLOCK;
	memcpy(&downbuffer[4], &dummy, 4);
	dummy = CMD_NEUTRAL;
	memcpy(&neutralbuffer[4], &dummy, 4);
	dummy = CMD_CUE;
	memcpy(&cuebuffer[4], &dummy, 4);
	dummy = CMD_ERROR;
	memcpy(&errorbuffer[4], &dummy, 4);

	// setpoints
	for(int i=0; i<18; i++)
	{
		dummy = (uint32_t)((offset[i] + 0.0)*scaling[i]);
		memcpy(&shutdownbuffer[8+4*i], &dummy, 4);
		memcpy(&downbuffer[8+4*i], &dummy, 4);
		memcpy(&neutralbuffer[8+4*i], &dummy, 4);
		memcpy(&cuebuffer[8+4*i], &dummy, 4);
		memcpy(&errorbuffer[8+4*i], &dummy, 4);
	}
	dummy = (uint32_t)((offset[2]+0.69)*scaling[2]); // z [m] in down position
	memcpy(&downbuffer[16], &dummy, 4);
	memcpy(&shutdownbuffer[16], &dummy, 4);
	memcpy(&errorbuffer[16], &dummy, 4);
}


MotionSender::~MotionSender(){

	// close the serial port
	if(fd >= 0) close(fd);
}

void MotionSender::closeport()
{
	// close the serial port
	if(fd >= 0) close(fd);
	fd = -1;
}

bool MotionSender::isPrepared()
{
	bool prep = (fd >= 0);

	return prep;
}

int MotionSender::send(char *buf)
{
  assert(fd >= 0);
  
	int n;
	uint32_t checksum=0xFFFFFFFFL;

	// complete it with sync word and checksum
	memcpy(&buffer[4], buf, SENDBUFFERLEN-8);

//	checksum = cs.calculate(&buffer[0], SENDBUFFERLEN-4);// include the sync word in checksum!
	for(int i=0; i< SENDBUFFERLEN-4;i++) checksum = cs.update(checksum, &buffer[i], 1);
//	for(int i=0; i<1;i++) checksum = cs.update(checksum, &buffer[i], 1);

	//cout << "Checksum: " << hex << checksum << endl;
	//cout << "CRC[128]: " << hex << cs.get_crc(128) << endl;

	//debug
	//checksum = 0x0FF0CC33L;

	memcpy(&buffer[SENDBUFFERLEN-4], &checksum, 4);

	//cout << "end of buffer:" << hex << (unsigned int)buffer[84] <<
	//hex << (unsigned int)buffer[85] << hex << (unsigned int)buffer[86] <<
	//hex << (unsigned int)buffer[87] <<endl;

	//debug
	uint32_t* dummy = (uint32_t*)(&buffer[0]);

	for(int j=0;j<22;j++)
	{
	  D_MOD("send buffer[" << dec << j << "]:" << hex << dummy[j] << dec);
	}

	// write it out
	n = write(fd, buffer, SENDBUFFERLEN);

	if (n<0) {
		W_MOD("MotionLimiter low level write failed: " << strerror(errno));
	}
	else{
	  D_MOD("wrote " << dec << n << " bytes");}

	return n;
}

bool MotionSender::sendShutDown(uint32_t counter)
{
	int n;

	// fill in the counter
	memcpy(&shutdownbuffer[0], &counter, 4);

	// pass it on
	n = send(shutdownbuffer);

	return (n==SENDBUFFERLEN);
}

bool MotionSender::sendDown(uint32_t counter)
{
	int n;

	// fill in the counter
	memcpy(&downbuffer[0], &counter, 4);

	// pass it on
	n = send(downbuffer);

	return (n==SENDBUFFERLEN);
}

bool MotionSender::sendNeutral(uint32_t counter)
{
	int n;

	// fill in the counter
	memcpy(&neutralbuffer[0], &counter, 4);

	// pass it on
	n = send(neutralbuffer);

	return (n==SENDBUFFERLEN);
}

bool MotionSender::sendCue(uint32_t counter, const MotionCommandedPosVelAcc& cpva)
{
	int n;

	// fill in the counter
	memcpy(&cuebuffer[0], &counter, 4);

	// fill in the setpoints
	uint32_t dummy;

	dummy = (uint32_t)((cpva.x + offset[0])*scaling[0]);
	memcpy(&cuebuffer[8], &dummy, 4);
	dummy = (uint32_t)((cpva.y + offset[1])*scaling[1]);
	memcpy(&cuebuffer[12], &dummy, 4);
	dummy = (uint32_t)((cpva.z + offset[2])*scaling[2]);
	memcpy(&cuebuffer[16], &dummy, 4);

	dummy = (uint32_t)((cpva.phi + offset[3])*scaling[3]);
	memcpy(&cuebuffer[20], &dummy, 4);
	dummy = (uint32_t)((cpva.theta + offset[4])*scaling[4]);
	memcpy(&cuebuffer[24], &dummy, 4);
	dummy = (uint32_t)((cpva.psi + offset[5])*scaling[5]);
	memcpy(&cuebuffer[28], &dummy, 4);

	dummy = (uint32_t)((cpva.xdot + offset[6])*scaling[6]);
	memcpy(&cuebuffer[32], &dummy, 4);
	dummy = (uint32_t)((cpva.ydot + offset[7])*scaling[7]);
	memcpy(&cuebuffer[36], &dummy, 4);
	dummy = (uint32_t)((cpva.zdot + offset[8])*scaling[8]);
	memcpy(&cuebuffer[40], &dummy, 4);

	dummy = (uint32_t)((cpva.p + offset[9])*scaling[9]);
	memcpy(&cuebuffer[44], &dummy, 4);
	dummy = (uint32_t)((cpva.q + offset[10])*scaling[10]);
	memcpy(&cuebuffer[48], &dummy, 4);
	dummy = (uint32_t)((cpva.r + offset[11])*scaling[11]);
	memcpy(&cuebuffer[52], &dummy, 4);

	dummy = (uint32_t)((cpva.xdotdot + offset[12])*scaling[12]);
	memcpy(&cuebuffer[56], &dummy, 4);
	dummy = (uint32_t)((cpva.ydotdot + offset[13])*scaling[13]);
	memcpy(&cuebuffer[60], &dummy, 4);
	dummy = (uint32_t)((cpva.zdotdot + offset[14])*scaling[14]);
	memcpy(&cuebuffer[64], &dummy, 4);

	dummy = (uint32_t)((cpva.pdot + offset[15])*scaling[15]);
	memcpy(&cuebuffer[68], &dummy, 4);
	dummy = (uint32_t)((cpva.qdot + offset[16])*scaling[16]);
	memcpy(&cuebuffer[72], &dummy, 4);
	dummy = (uint32_t)((cpva.rdot + offset[17])*scaling[17]);
	memcpy(&cuebuffer[76], &dummy, 4);

	// pass it on
	n = send(cuebuffer);

	return (n==SENDBUFFERLEN);
}

bool MotionSender::sendError(uint32_t counter)
{
	int n;

	// fill in the counter
	memcpy(&errorbuffer[0], &counter, 4);

	// pass it on
	n = send(errorbuffer);

	return (n==SENDBUFFERLEN);
}
