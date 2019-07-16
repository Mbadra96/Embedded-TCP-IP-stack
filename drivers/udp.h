#ifndef UDP_H_
#define UDP_H_

#include "utils.h" //for checksum
#include "ip.h"	//for IP_DST_ADD
#define UDP_H_LEN 8
#define UDP_START IP_DST_ADD + 0x04
#define UDP_SRC_PORT UDP_START
#define UDP_DST_PORT UDP_SRC_PORT + 0x02
#define UDP_LEN UDP_DST_PORT + 0X02
#define UDP_CHK_SUM UDP_LEN + 0x02
#define UDP_FINISH UDP_CHK_SUM + 0x02
typedef struct UDP
{
	uint16_t src_port;
	uint16_t dst_port;
} udp;

void init_udp_struct(void);

void init_udp_in_buffer(uint16_t app_len);
/* this function used to initialize the buffer*/

void set_udp_src_port(uint16_t port);
/* Get Source PORT from buffer
 */
void set_udp_dst_port(uint16_t port);
/* 
 * Get Destination PORT from buffer
 */

#endif