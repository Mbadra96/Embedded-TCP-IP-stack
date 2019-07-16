/*
 * tcp.h
 *
 * Created: 06/07/2019 4:23:45 AM
 *  Author: Mohamed Badra
 */

#ifndef TCP_H_
#define TCP_H_

#include "utils.h" //for checksum
#include "ip.h"	//for IP_DST_ADD

typedef enum TCP_STATES
{
	CLOSED,
	SYN_SENT,
	ESTABLISHED,
	FIN_WAIT_1,
	FIN_WAIT_2,
	FIN_RECVED,
	CLOSING,
	TIME_WAIT
} tcp_state;

typedef union SEQ {
	uint32_t num;
	uint8_t array[4];
} seq;

typedef struct TCP
{
	tcp_state state;
	uint16_t src_port;
	uint16_t dst_port;
	seq ackno;
	seq seqno;
	uint16_t ack_offset; // used to check ack offset of data
	uint16_t hl_config;
} tcp;

// defining the TCP Packet location in buffer
#define TCP_LEN 20
#define TCP_START IP_DST_ADD + 0x04
#define TCP_SRC_PORT TCP_START
#define TCP_DST_PORT TCP_SRC_PORT + 0x02
#define TCP_SEQ_NUM TCP_DST_PORT + 0X02
#define TCP_ACK TCP_SEQ_NUM + 0x04
#define TCP_HEAD_LEN_RESERVED_CONFIG TCP_ACK + 0x04 //including bits : URG, ACK, PSH, RST, SYN, FIN
#define TCP_WINDOW_SIZE TCP_HEAD_LEN_RESERVED_CONFIG + 0x02
#define TCP_CHECK_SUM TCP_WINDOW_SIZE + 0x02
#define TCP_UGRENT_POINTER TCP_CHECK_SUM + 0x02
#define TCP_FINISH TCP_UGRENT_POINTER + 0x02
// WE STILL HAVE NO OPTIONS :P :P

// ENUM for flags
#define TCP_URG_FLAG 0x20
#define TCP_ACK_FLAG 0x10
#define TCP_PSH_FLAG 0x08
#define TCP_RST_FLAG 0x04
#define TCP_SYN_FLAG 0x02
#define TCP_FIN_FLAG 0x01

//

void init_tcp_struct();

void init_tcp_in_buffer(uint8_t flag);
/* this function used to initialize the buffer
 * with the tcp data
 * flag: 0 for URG 
 * flag: 1 for ACK 
 * flag: 2 for PSH 
 * flag: 3 for RST 
 * flag: 4 for SYN 
 * flag: 5 for FIN 
 */

uint16_t get_src_port(void);
/* 
 * Get Source PORT from buffer
 */
uint16_t get_dst_port(void);
/* 
 * Get Destination PORT from buffer
 */

void set_tcp_dst_port(uint16_t port);

void set_tcp_src_port(uint16_t port);

uint8_t check_tcp_ack(void);

void add_to_tcp_seq_ack(uint32_t seq_inc, uint32_t ack_inc);

void set_tcp_ack_offset(uint16_t len);

uint8_t get_tcp_state(void);

void set_tcp_state(uint8_t state);

uint16_t get_data_length(void);

#endif /* TCP_H_ */