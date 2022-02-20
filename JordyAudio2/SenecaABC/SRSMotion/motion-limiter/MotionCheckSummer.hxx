/***************************************************************************
                          motionchecksummer.h  -  description
                             -------------------
    begin                : Thu Feb 7 2002
    copyright            : (C) 2002 by Olaf Stroosma
    email                : stroosma@srshost
 ***************************************************************************/

#ifndef MOTIONCHECKSUMMER_H
#define MOTIONCHECKSUMMER_H

#include <stdint.h>

/**
  *@author Olaf Stroosma
  */

class MotionCheckSummer {
public: 
	MotionCheckSummer();
	~MotionCheckSummer();

 	uint32_t calculate(char * buffer, int num);
	uint32_t update(uint32_t crc, char * buffer, int num);

	// debug
	uint32_t get_crc(int i);
private:
	/* generate the table of CRC remainders for all possible bytes */
	void gen_crc_table();

 	/* update the CRC on the data block one byte at a time */
	uint32_t update_crc(uint32_t crc_accum, char *data_blk_ptr,
                                                    int data_blk_size);

	uint32_t crc_table[256];
};

#endif
