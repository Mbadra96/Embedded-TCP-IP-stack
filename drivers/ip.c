/*
 * ip.c
 *
 * Created: 06/07/2019 3:55:23 AM
 *  Author: Mohamed Badra
 */
#include "ip.h"

extern uint8_t buffer[];

ip ip_struct;

void init_ip_struct(void)
{
	/*
	* initiation of IP Structure
	*/
	for (uint8_t i = 0; i < 4; i++)
	{
		ip_struct.src_add[i] = 0;
		ip_struct.dst_add[i] = 0;
	}
	ip_struct.protocol = 6; //17 for udp 6 for tcp
}

void set_src_ip(uint8_t *src_ip)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		ip_struct.src_add[i] = src_ip[i];
	}
}

void set_dst_ip(uint8_t *dst_ip)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		ip_struct.dst_add[i] = dst_ip[i];
	}
}

void set_ip_total_length(uint16_t length)
{
	buffer[IP_TOT_LEN] = (uint8_t)(length >> 8);
	buffer[IP_TOT_LEN + 1] = (uint8_t)length;
	uint16_t tmp_sum = checksum(&buffer[IP_START], 20); // ip header is always 20 bytes
	buffer[IP_CHECK_SUM] = (uint8_t)(tmp_sum >> 8);
	buffer[IP_CHECK_SUM + 1] = (uint8_t)tmp_sum;
}

void init_ip_in_buffer(void)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		buffer[IP_DST_ADD + i] = ip_struct.dst_add[i];
		buffer[IP_SRC_ADD + i] = ip_struct.src_add[i];
	}

	buffer[IP_VER_HEAD_LEN] = 0b01000101;
	buffer[IP_TOS] = 0;
	buffer[IP_ID] = 0;
	buffer[IP_ID + 1] = 5;
	buffer[IP_FLAGS_FRAG_OFF] = 0x40;
	buffer[IP_FLAGS_FRAG_OFF + 1] = 0;
	buffer[IP_TTL] = 128;
	buffer[IP_PROTOCOL] = ip_struct.protocol;
}

void set_ip_protocol(uint8_t type)
{
	ip_struct.protocol = type;
}
