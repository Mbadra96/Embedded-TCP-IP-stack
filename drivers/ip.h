/*
 * ip.h
 *
 * This file contains all the places for ethernet in buffer
 *  Author: Mohamed Badra
 */ 



#ifndef IP_H_
#define IP_H_

#include "utils.h" // used for checksum function

typedef struct Ip{
	uint8_t vesion_header;
	uint8_t tos;
	uint16_t id;
	uint16_t flag_frag_off;
	uint8_t ttl;
	uint8_t protocol;
	uint8_t src_add[4];
	uint8_t dst_add[4];
}ip;

// defining the IP Packet location in buffer
#define IP_START 0x0E
#define IP_VER_HEAD_LEN IP_START+0x00
#define IP_TOS IP_VER_HEAD_LEN+0x01
#define IP_TOT_LEN IP_TOS+0x01
#define IP_ID IP_TOT_LEN+0x02
#define IP_FLAGS_FRAG_OFF IP_ID+0x02
#define IP_TTL IP_FLAGS_FRAG_OFF+0x02
#define IP_PROTOCOL IP_TTL+0x01
#define IP_CHECK_SUM IP_PROTOCOL+0x01
#define IP_SRC_ADD IP_CHECK_SUM+0x02
#define IP_DST_ADD IP_SRC_ADD+0x04
// WE HAVE NO OPTIONS :D


void init_ip_struct(void);
/*
* initiation of IP Structure
*/
void set_src_ip(uint8_t *src_ip);
/*
* Add your Source IP Address to this function
* as it will be saved in the structure as it
* be used by the buffer
*/

void set_dst_ip(uint8_t *dst_ip);
/*
* Add your Destination IP Address to this function
* as it will be saved in the structure as it
* be used by the buffer
*/

void set_ip_total_length(uint16_t length);
/*
* Add Total packet length and checksum to this function
* as it will be saved in the structure as it
* be used by the buffer
*/
void init_ip_in_buffer(void);
/*
* Adding the structure data to the buffer
*/
void set_ip_protocol(uint8_t type);
/*
* for UDP set 6 
* for TCP set 17
*/



#endif /* IP_H_ */