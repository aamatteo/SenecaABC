/***************************************************************************
                          motionchecksummer.cpp  -  description
                             -------------------
    begin                : Thu Feb 7 2002
    copyright            : (C) 2002 by Olaf Stroosma
    email                : stroosma@srshost
 ***************************************************************************/

#include "MotionCheckSummer.hxx"

#define POLYNOMIAL 0x04c11db7L


MotionCheckSummer::MotionCheckSummer(){
	gen_crc_table();
}

MotionCheckSummer::~MotionCheckSummer(){
}

uint32_t MotionCheckSummer::get_crc(int i)
{
	if(i>=0 && i<256)
		return crc_table[i];
	else
		return 0;
}

uint32_t MotionCheckSummer::calculate(char * buffer, int num)
{
	uint32_t checksum = 0xFFFFFFFFL;

	checksum = update_crc(checksum, (char*)buffer, num);

	return checksum;
}

uint32_t MotionCheckSummer::update(uint32_t crc, char * buffer, int num)
{
	uint32_t checksum = 0xFFFFFFFFL;

	checksum = update_crc(crc, (char*)buffer, num);

	return checksum;
}


void MotionCheckSummer::gen_crc_table()
 /* generate the table of CRC remainders for all possible bytes */
{ register int i, j;  register uint32_t crc_accum;
   for ( i = 0;  i < 256;  i++ )
       { crc_accum = ( (uint32_t) i << 24 );
         for ( j = 0;  j < 8;  j++ )
              { if ( crc_accum & 0x80000000L )
                   crc_accum =
                     ( crc_accum << 1 ) ^ POLYNOMIAL;
                else
                   crc_accum =
                     ( crc_accum << 1 ); }
         crc_table[i] = crc_accum; }
   return; }

uint32_t MotionCheckSummer::update_crc(uint32_t crc_accum, char *data_blk_ptr,
                                                    int data_blk_size)
 /* update the CRC on the data block one byte at a time */
 { register int i, j;
   for ( j = 0;  j < data_blk_size;  j++ )
       { i = ( (int) ( crc_accum >> 24) ^ *data_blk_ptr++ ) & 0xff;
         crc_accum = ( crc_accum << 8 ) ^ crc_table[i]; }
   return crc_accum; }
