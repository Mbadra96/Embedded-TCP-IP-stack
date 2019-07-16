/*
 * socket.h
 *
 * Created: 06/07/2019 4:59:42 AM
 *  Author: Mohamed Badra
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <avr/io.h>
#include <util/delay.h>
#include "enc28j60.h"
#include "ethernet.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "dhcp.h"
#include "arp.h"

typedef struct SOCKET
{
	uint8_t dst_ip[4];
	uint16_t src_port;
	uint16_t dst_port;
} socket;

void init_system(void);

// send simple tcp
void send_tcp_data(uint16_t len, uint8_t *data, uint8_t flag);
// send simple udp
void send_udp_data(uint16_t len, uint8_t *data);

// ip configuration
void config_ip_address(void);
void send_dhcp_discover(void);
void send_dhcp_request(void);
/*
* configuration for getting new ip address
*/
uint8_t receive_data(uint8_t (*check_fnc)(void));

uint8_t socket_connect(socket sock);

uint16_t socket_receive(uint8_t *data_ptr, socket sock);
uint8_t socket_send(socket sock, uint16_t len, uint8_t *data);

uint8_t socket_close(socket sock);

#endif /* SOCKET_H_ */