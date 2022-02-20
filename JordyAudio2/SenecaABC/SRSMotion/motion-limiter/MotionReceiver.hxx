/***************************************************************************
                          motionreceiver.h  -  description
                             -------------------
    begin                : Thu Feb 7 2002
    copyright            : (C) 2002 by Olaf Stroosma
    email                : stroosma@srshost
 ***************************************************************************/

#ifndef MOTIONRECEIVER_H
#define MOTIONRECEIVER_H

#include "MotionCheckSummer.hxx"

//#include "MotionBaseResultData.hxx"
#include "comm-objects.h"

/**
  *@author Olaf Stroosma
  */
// define this if the remote loopback connector is used instead of the dSpace
//#define REMOTELOOPBACK

// total packet size in bytes
#ifdef REMOTELOOPBACK
#define RECEIVEBUFFERLEN 88
#else
#define RECEIVEBUFFERLEN 64
#endif

class MotionReceiver {
public:
  MotionReceiver();
  ~MotionReceiver();
  
  bool isPrepared();
  
  int read(MotionBaseResultData& mbrd);

private:
  // file descriptor of the serial port
  int fd;
  
  // scaling after receiving
  float scaling[(RECEIVEBUFFERLEN/4)-4];
  // offset after receiving
  float offset[(RECEIVEBUFFERLEN/4)-4];
  
  // working buffer
  char buffer[RECEIVEBUFFERLEN];
  
  // check sum generator
  MotionCheckSummer cs;
  
  // packet counters
  double good_packet_count, bad_packet_count;
  
  // low level read function
  int readPacket(char* buffer, int& bytes_to_read);
};

#endif
