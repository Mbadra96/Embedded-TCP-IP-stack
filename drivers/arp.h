

#ifndef ARP_H_
#define ARP_H_

#include "utils.h"
#include "ethernet.h"
#define ARP_START 0x0E
#define ARP_HARDWARE_TYPE ARP_START
#define ARP_PROTOCOL_TYPE ARP_HARDWARE_TYPE+0x02
#define ARP_HARDWARE_ADD_LEN ARP_PROTOCOL_TYPE+0x02
#define ARP_PROTOCOL_ADD_LEN ARP_HARDWARE_ADD_LEN+0x01
#define ARP_OP_CODE ARP_PROTOCOL_ADD_LEN+0x01
#define ARP_SENDER_MAC_ADD ARP_OP_CODE+0x02
#define ARP_SENDER_IP_ADD ARP_SENDER_MAC_ADD+0x06
#define ARP_DES_MAC_ADD ARP_SENDER_IP_ADD+0x04
#define ARP_DES_IP_ADD ARP_DES_MAC_ADD+0x06
#define ARP_FINISH ARP_DES_IP_ADD+0x04




typedef struct ARP{

   // uint16_t hardware_type;
    //uint16_t protocol_type;
    //uint8_t hardware_add_len;
    //uint8_t protocol_add_len;
    //uint16_t op_code;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t dest_mac[6];
    uint8_t dest_ip[4];

}arp;

typedef struct ARP_CACHE{
    uint8_t ip[4];
    uint8_t mac[6];
}arp_cache;

void init_arp_cache(void);
void init_arp(uint8_t *my_mac, uint8_t *my_ip);
void init_request_arp_in_buffer(uint8_t *dest_ip);
void set_ether_struct_arp_request(void);
uint8_t check_my_arp_reply(void);
void arp_dest_save_to_cache(void);
uint8_t check_return_mac(uint8_t *ip);
uint8_t * get_mac_from_cache(uint8_t index);


#endif
