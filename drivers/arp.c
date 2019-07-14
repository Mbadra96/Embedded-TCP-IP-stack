
#include "arp.h"


extern uint8_t buffer[];

arp arp_struct;

arp_cache my_arp_chache[3];

void init_arp_cache(void)
{
    for (uint8_t i=0; i<3;i++)
    {
        for(uint8_t j=0; i<4;i++)
        {
            my_arp_chache[i].ip[j] = 0x00;   
        }
        for(uint8_t j=0; i<6;i++)
        {
            my_arp_chache[i].mac[j] = 0x00;   
        }
    }
}


void init_arp(uint8_t *my_mac, uint8_t *my_ip)
{
    arp_struct.hardware_type = 0x01; //ethernet
    arp_struct.protocol_type = 0x0800; //for ipv4
    arp_struct.hardware_add_len = 0x06;
    arp_struct.protocol_add_len = 0x04;
    arp_struct.op_code = 1; //for request 
    for (uint8_t i=0;i<6;i++)
    {
        arp_struct.sender_mac[i] = my_mac[i];
        arp_struct.dest_mac[i]=0;
    }
    for (uint8_t i=0;i<4;i++)
    {
        arp_struct.sender_ip[i] = my_ip[i];
        arp_struct.dest_ip[i]=0;   
    }
}

void init_request_arp_in_buffer(uint8_t *dest_ip)
{
    for (uint8_t i=0;i<4;i++)
    {
        arp_struct.dest_ip[i]=dest_ip[i];   
    }
    set_ether_struct_arp_request();
    init_ether_in_buffer();
    buffer[ARP_HARDWARE_TYPE] = (uint8_t) (arp_struct.hardware_type>>8);
    buffer[ARP_HARDWARE_TYPE+1] = (uint8_t) (arp_struct.hardware_type);
    buffer[ARP_PROTOCOL_TYPE] = (uint8_t) (arp_struct.protocol_type>>8);
    buffer[ARP_PROTOCOL_TYPE+1] = (uint8_t) (arp_struct.protocol_type);
    buffer[ARP_OP_CODE] = (uint8_t) (arp_struct.op_code>>8);
    buffer[ARP_OP_CODE+1] = (uint8_t) (arp_struct.op_code);
    for (uint8_t i=0; i<6;i++)
    {
        buffer[ARP_SENDER_MAC_ADD+i] = arp_struct.sender_mac[i];
        buffer[ARP_DES_MAC_ADD+i] = arp_struct.dest_mac[i];
    }
    for (uint8_t i=0; i<4;i++)
    {
        buffer[ARP_SENDER_IP_ADD+i] = arp_struct.sender_ip[i];
        buffer[ARP_DES_IP_ADD+i] = arp_struct.dest_ip[i];
    }
   
}

void set_ether_struct_arp_request(void)
{
    uint8_t dst_mac[6] = {255,255,255,255,255,255};
    set_ether_dst_mac(dst_mac);
	set_ether_type(0x0806);
}

uint8_t check_my_arp_reply(void)
{
    if((buffer[ETH_TYPE] == 0x08 && buffer[ETH_TYPE+1] == 0x06))
    {
       // uint8_t count = 0;
        for (uint8_t i=0;i<4;i++)
        {
            if(buffer[ARP_DES_IP_ADD+i] == arp_struct.sender_ip[i]){}
            else
            {
                return 0;
            }
            
        }
        if(buffer[ARP_OP_CODE+1]==2)
        {return 1;}
    }
    return 0;
}

void arp_dest_save_to_cache(void)
{
    static uint8_t counter_cache;
    for(uint8_t i=0;i<4;i++)
    {
       my_arp_chache[counter_cache].ip[i] = buffer[ARP_SENDER_IP_ADD+i];
    }
    for(uint8_t i=0;i<6;i++)
    {
       my_arp_chache[counter_cache].mac[i] = buffer[ARP_SENDER_MAC_ADD+i];
    }
    counter_cache++;
}

uint8_t check_return_mac(uint8_t *ip)
{
    for (uint8_t i=0;i<3;i++)
    {
        for (uint8_t j=0;j<4;j++)
        {
            if(my_arp_chache[i].ip[j] == ip[j]){}
            else
            {
                break;
            }
            if(j==3)
            {
                return i; //found mac at this index
            }
        }
    }
    return 5; //return number out of index of my_cache
}

uint8_t * get_mac_from_cache(uint8_t index){
	return my_arp_chache[index].mac;
}