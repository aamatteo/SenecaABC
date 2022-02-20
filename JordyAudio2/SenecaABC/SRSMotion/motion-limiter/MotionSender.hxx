/***************************************************************************
                          motionsender.h  -  description
                             -------------------
    begin                : Thu Feb 7 2002
    copyright            : (C) 2002 by Olaf Stroosma
    email                : stroosma@srshost
 ***************************************************************************/

#ifndef MOTIONSENDER_H
#define MOTIONSENDER_H

#include "MotionCheckSummer.hxx"

//#include "MotionCommandedPosVelAcc.hxx"
#include "comm-objects.h"

/**
  *@author Olaf Stroosma
  */

// total packet size in bytes
#define SENDBUFFERLEN 88

// defines for the motion commands
#define CMD_SHUTDOWN		0
#define CMD_ERROR		1
#define CMD_DOWNANDLOCK		2
#define CMD_NEUTRAL		3
#define CMD_DITHER		4
#define CMD_CUE			5

class MotionSender {
public:
	MotionSender();
	~MotionSender();

	bool isPrepared();

	int send(char * buffer);

	// utility functions
	// send a packet with message counter 'counter',
	// CMD_SHUTDOWN and down position
	bool sendShutDown(uint32_t counter);
	// send a packet with message counter 'counter',
	// CMD_DOWNANDLOCK and down position
	bool sendDown(uint32_t counter);
	// send a packet with message counter 'counter',
	// CMD_NEUTRAL and neutral position
	bool sendNeutral(uint32_t counter);
	// send a packet with message counter 'counter',
	// CMD_CUE and setpoint from 'setpoints'
	bool sendCue(uint32_t counter, const MotionCommandedPosVelAcc& cpva);
	// send a packet with message counter 'counter',
	// CMD_ERROR and down position
	bool sendError(uint32_t counter);

	void closeport(); // debug
private:
	// file descriptor of the serial port
	int fd;

	// scaling before sending
	float scaling[(SENDBUFFERLEN/4)-4];
	// offset before sending
	float offset[(SENDBUFFERLEN/4)-4];

	// working buffer
	char buffer[SENDBUFFERLEN];

	// predefined buffer for shutdown packet
	// just fill in the counter
	char shutdownbuffer[SENDBUFFERLEN-8];

	// predefined buffer for down packet
	// just fill in the counter
	char downbuffer[SENDBUFFERLEN-8];

	// predefined buffer for neutral packet
	// just fill in the counter
	char neutralbuffer[SENDBUFFERLEN-8];

	// predefined buffer for cue packet
	// fill in the counter + setpoints
	char cuebuffer[SENDBUFFERLEN-8];

	// predefined buffer for error packet
	// just fill in the counter
	char errorbuffer[SENDBUFFERLEN-8];

	// check sum generator
	MotionCheckSummer cs;
};

#endif
