/*
 * dhcp.c
 *
 * Created: 06/07/2019 10:53:59 PM
 *  Author: Mohamed Badra and Omar Abdelaziz
 */

#include "dhcp.h"

extern uint8_t buffer[];

dhcp dhcp_struct;

void init_dhcp_struct(uint8_t *src_mac)
{
	dhcp_struct.trans_id[0] = 10;
	dhcp_struct.trans_id[1] = 20;
	dhcp_struct.trans_id[2] = 30;
	dhcp_struct.trans_id[3] = 40;
	for (uint8_t i = 0; i < 4; i++)
	{
		dhcp_struct.client_ip_add[i] = 0;
		dhcp_struct.your_ip_add[i] = 0;
		dhcp_struct.server_ip_add[i] = 0;
		dhcp_struct.gateway_ip_add[i] = 0;
	}
	for (int i = 0; i < 6; i++)
	{
		dhcp_struct.client_hw_add[i] = src_mac[i];
	}
}

void init_dhcp_in_buffer(void)
{
	buffer[DHCP_OPCODE] = 1;
	buffer[DHCP_HW_TYPE] = 1;
	buffer[DHCP_HW_ADD_LENGTH] = 6;
	buffer[DHCP_HOP_COUNT] = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		buffer[DHCP_TRANS_ID + i] = dhcp_struct.trans_id[i];
		buffer[DHCP_CLIENT_IP_ADD + i] = dhcp_struct.client_ip_add[i];
		buffer[DHCP_YOUR_IP_ADD + i] = dhcp_struct.your_ip_add[i];
		buffer[DHCP_SERVER_IP_ADD + i] = dhcp_struct.server_ip_add[i];
		buffer[DHCP_GATEWAY_IP_ADD + i] = dhcp_struct.gateway_ip_add[i];
	}
	buffer[DHCP_MAGIC_COOKIE] = 99;
	buffer[DHCP_MAGIC_COOKIE + 1] = 130;
	buffer[DHCP_MAGIC_COOKIE + 2] = 83;
	buffer[DHCP_MAGIC_COOKIE + 3] = 99;
	buffer[DHCP_SECONDS] = 0;
	buffer[DHCP_SECONDS + 1] = 0;
	buffer[DHCP_BROADCAST_FLAG] = 0;
	buffer[DHCP_BROADCAST_FLAG + 1] = 0;
	for (uint8_t i = 0; i < 6; i++)
	{
		buffer[DHCP_CLIENT_HW_ADD + i] = dhcp_struct.client_hw_add[i];
	}
	for (uint8_t i = 0; i < 64; i++)
	{
		buffer[DHCP_SERVER_NAME + i] = 0;
	}
	for (uint8_t i = 0; i < 128; i++)
	{
		buffer[DHCP_FILENAME + i] = 0;
	}
}
uint16_t set_dhcp_discover_in_buffer(void)
{
	// for broadcasting
	uint8_t src_mac[6] = MAC_ADD;
	uint8_t dst_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	set_ether_dst_mac(dst_mac);
	uint8_t src_ip[4] = {0, 0, 0, 0};
	uint8_t dst_ip[4] = {255, 255, 255, 255};
	set_src_ip(src_ip);
	set_dst_ip(dst_ip);
	// option discover
	buffer[DHCP_OPTIONS_START] = 0x35;
	buffer[DHCP_OPTIONS_START + 1] = 0x01;
	buffer[DHCP_OPTIONS_START + 2] = 0x01;
	// option parameter list
	buffer[DHCP_OPTIONS_START + 3] = 55;
	buffer[DHCP_OPTIONS_START + 4] = 3;
	buffer[DHCP_OPTIONS_START + 5] = 1;
	buffer[DHCP_OPTIONS_START + 6] = 121;
	buffer[DHCP_OPTIONS_START + 7] = 3;
	// max DHCP size length
	buffer[DHCP_OPTIONS_START + 8] = 57;
	buffer[DHCP_OPTIONS_START + 9] = 2;
	buffer[DHCP_OPTIONS_START + 10] = 0x02;
	buffer[DHCP_OPTIONS_START + 11] = 0xbc;
	//client id
	buffer[DHCP_OPTIONS_START + 12] = 61;
	buffer[DHCP_OPTIONS_START + 13] = 7;
	buffer[DHCP_OPTIONS_START + 14] = 1;
	buffer[DHCP_OPTIONS_START + 15] = src_mac[0];
	buffer[DHCP_OPTIONS_START + 16] = src_mac[1];
	buffer[DHCP_OPTIONS_START + 17] = src_mac[2];
	buffer[DHCP_OPTIONS_START + 18] = src_mac[3];
	buffer[DHCP_OPTIONS_START + 19] = src_mac[4];
	buffer[DHCP_OPTIONS_START + 20] = src_mac[5];
	//host name
	buffer[DHCP_OPTIONS_START + 21] = 12;
	buffer[DHCP_OPTIONS_START + 22] = 3;
	buffer[DHCP_OPTIONS_START + 23] = 'A';
	buffer[DHCP_OPTIONS_START + 24] = 'V';
	buffer[DHCP_OPTIONS_START + 25] = 'R';
	//end options
	buffer[DHCP_OPTIONS_START + 26] = 0xff;
	return 26 + DHCP_OPTIONS_START - DHCP_START;
}
uint8_t get_dhcp_offer_ip_pointer_from_buffer(void)
{
	for (int i = 0; i < 4; i++)
	{
		dhcp_struct.server_ip_add[i] = buffer[DHCP_SERVER_IP_ADD + i]; // get gateway server ip address
		dhcp_struct.your_ip_add[i] = buffer[DHCP_YOUR_IP_ADD + i];	 // get your new ip address
	}
	return DHCP_YOUR_IP_ADD;
}
uint16_t set_dhcp_request_in_buffer(void)
{
	// for broadcasting
	uint8_t dst_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	set_ether_dst_mac(dst_mac);
	uint8_t src_ip[4] = {0, 0, 0, 0};
	uint8_t dst_ip[4] = {255, 255, 255, 255};
	set_src_ip(src_ip);
	set_dst_ip(dst_ip);
	for (int i = 0; i < 4; i++)
	{
		buffer[DHCP_SERVER_IP_ADD + i] = dhcp_struct.server_ip_add[i];
	}
	// type request
	buffer[DHCP_OPTIONS_START] = 0x35;
	buffer[DHCP_OPTIONS_START + 1] = 0x01;
	buffer[DHCP_OPTIONS_START + 2] = 0x03;
	// Request the ip address
	buffer[DHCP_OPTIONS_START + 3] = 0x32;
	buffer[DHCP_OPTIONS_START + 4] = 0x04;
	buffer[DHCP_OPTIONS_START + 5] = dhcp_struct.your_ip_add[0];
	buffer[DHCP_OPTIONS_START + 6] = dhcp_struct.your_ip_add[1];
	buffer[DHCP_OPTIONS_START + 7] = dhcp_struct.your_ip_add[2];
	buffer[DHCP_OPTIONS_START + 8] = dhcp_struct.your_ip_add[3];
	//finish
	buffer[DHCP_OPTIONS_START + 9] = 0xff;
	return 9 + DHCP_OPTIONS_START - DHCP_START;
}
uint8_t check_dhcp_ack(void)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		if (buffer[DHCP_YOUR_IP_ADD + i] != dhcp_struct.your_ip_add[i])
			return 0;
	}
	// the dhcp server ack to the ip requested
	set_src_ip(dhcp_struct.your_ip_add);
	return 1;
}

uint8_t check_id(void)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		if (dhcp_struct.trans_id[i] != buffer[DHCP_TRANS_ID + i])
		{
			return 0;
		}
	}
	return 1;
}

uint8_t *get_dhcp_src_ip(void)
{
	return dhcp_struct.your_ip_add;
}