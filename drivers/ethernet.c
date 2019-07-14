/*
 * ethernet.c
 *
 * Created: 06/07/2019 3:33:05 AM
 *  Author: Mohamed Badra
 */ 

#include "ethernet.h"

extern uint8_t buffer[];

ethernet ethernet_struct;

void init_ether_struct(uint8_t *src_mac)
{
	for (uint8_t i=0; i<6;i++)
	{
		ethernet_struct.dst_mac[i]=0xff;
		ethernet_struct.src_mac[i]=src_mac[i];
	}
	
	ethernet_struct.type = 0x0800;
}


void set_ether_dst_mac(uint8_t *dst_mac){
	for (uint8_t i=0; i<6;i++)
	{
		ethernet_struct.dst_mac[i]=dst_mac[i];
	}
}


void init_ether_in_buffer(void){
		for (uint8_t i = 0 ;i<6;i++)
		{
			buffer[ETH_DEST_MAC+i] = ethernet_struct.dst_mac[i];
			buffer[ETH_SRC_MAC+i] = ethernet_struct.src_mac[i];
		}
	buffer[ETH_TYPE] =(uint8_t) (ethernet_struct.type >> 8);
	buffer[ETH_TYPE+1] =(uint8_t) ethernet_struct.type;
}

void set_ether_type(uint16_t type){
	ethernet_struct.type = type;
}
