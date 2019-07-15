/*
 * ethernet.h
 *
 * This file contains all the places for ethernet in buffer
 *  Author: MOHAMED BADRA
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_
#include "utils.h"
// main structure for Ethernet header
typedef struct Ethernet
{
	uint8_t dst_mac[6];
	uint8_t src_mac[6];
} ethernet;

// defining the Ethernet Packet location in buffer
#define ETH_LEN 14
#define ETH_DEST_MAC 0x00
#define ETH_SRC_MAC 0x06
#define ETH_TYPE 0x0C

void init_ether_struct(uint8_t *src_mac);
/*
* Add your Source Mac Address to this function 
* as it will be saved in the structure as it
* be used by the buffer 
*/

void set_ether_dst_mac(uint8_t *dst_mac);
/*
* Add your Destination Mac Address to this function
* as it will be saved in the structure as it
* be used by the buffer
*/

void init_ether_in_buffer(void);
/*
* Adding the structure data to the buffer
*/

#endif /* ETHERNET_H_ */