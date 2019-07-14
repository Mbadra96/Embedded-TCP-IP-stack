/*
 * utils.h
 *
 * Created: 06/07/2019 4:14:36 AM
 *  Author: Mohamed Badra
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#include <avr/io.h>
#include <inttypes.h>
#include <string.h> // used for memset function

//#define MAC_ADD {0x5e,0x63,0x88,0x92,0xc9,0xa5}
#define MAC_ADD {0x90,0x48,0x9a,0xb3,0x8b,0x1d}
uint16_t checksum(uint8_t *buffer_ptr,uint8_t check_len);
/* checksum Function is a generic function to calculate the sum
*  of the array to the check_len given and returns its complement 
*/

void reset_buffer(void);
/* 
* this function is used to reset the buffer
*/

#endif /* UTILS_H_ */