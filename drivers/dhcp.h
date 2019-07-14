/*
 * dhcp.h
 *
 * Created: 06/07/2019 10:02:42 PM
 *  Author: Mohamed Badra and Omar Abdelaziz
 */ 


#ifndef DHCP_H_
#define DHCP_H_
#include "ethernet.h"
#include "utils.h"
#include "udp.h"

typedef struct DHCP {
	uint8_t opcode;
	uint8_t hw_type;
	uint8_t hw_add_len;
	uint8_t hop_count;
	uint8_t trans_id[4];
	uint16_t num_secs;
	uint16_t flags;
	uint8_t client_ip_add[4];
	uint8_t your_ip_add[4];
	uint8_t server_ip_add[4];
	uint8_t gateway_ip_add[4];
	uint8_t client_hw_add[6];
	uint8_t magic_cookie[4];
	}dhcp;


// Addresses indexes

#define DHCP_START UDP_FINISH 
#define DHCP_OPCODE DHCP_START
#define DHCP_HW_TYPE DHCP_OPCODE+1
#define DHCP_HW_ADD_LENGTH DHCP_HW_TYPE+1
#define DHCP_HOP_COUNT DHCP_HW_ADD_LENGTH + 1
#define DHCP_TRANS_ID DHCP_HOP_COUNT+ 1
#define DHCP_SECONDS DHCP_TRANS_ID + 4
#define DHCP_BROADCAST_FLAG DHCP_SECONDS +2
#define DHCP_CLIENT_IP_ADD DHCP_BROADCAST_FLAG+2
#define DHCP_YOUR_IP_ADD DHCP_CLIENT_IP_ADD +4
#define DHCP_SERVER_IP_ADD DHCP_YOUR_IP_ADD+4
#define DHCP_GATEWAY_IP_ADD DHCP_SERVER_IP_ADD+4
#define DHCP_CLIENT_HW_ADD DHCP_GATEWAY_IP_ADD+4
#define DHCP_SERVER_NAME DHCP_CLIENT_HW_ADD+16
#define DHCP_FILENAME DHCP_SERVER_NAME+64
#define DHCP_MAGIC_COOKIE DHCP_FILENAME+128
#define DHCP_OPTIONS_START DHCP_MAGIC_COOKIE+4


void init_dhcp_struct(uint8_t *src_mac);
void init_dhcp_in_buffer(void);
uint16_t set_dhcp_discover_in_buffer(void);
uint8_t get_dhcp_offer_ip_pointer_from_buffer(void);
uint8_t check_id(void);
uint16_t set_dhcp_request_in_buffer(void);
uint8_t check_dhcp_ack(void);
uint8_t *get_dhcp_src_ip(void);

#endif /* DHCP_H_ */