/*
 * RestAvr.c
 *
 * Created: 06/07/2019 2:05:30 AM
 * Author : Mohamed Badra and Ahmed Saad
 */

#include <avr/io.h>
#include "drivers/socket.h"
int main(void)
{
	init_system();
	config_ip_address();
	// _delay_ms(3000);
	// socket sock;
	// sock.dst_ip[0] = 192;
	// sock.dst_ip[1] = 168;
	// sock.dst_ip[2] = 1;
	// sock.dst_ip[3] = 8;
	// sock.dst_port = 65432;
	// sock.src_port = 1111;

	// socket_connect(sock);
	// uint8_t data[] = "HELLO";
	// socket_send(sock, 5, data);
	// uint8_t *ptr;
	// socket_receive(ptr, sock);
	// while (!socket_close(sock))
	// 	;

	uint8_t data[] = {255,
					  255,
					  255,
					  255,
					  255,
					  255,
					  94,
					  99,
					  136,
					  146,
					  201,
					  165,
					  8,
					  0,
					  69,
					  0,
					  0,
					  46,
					  0,
					  0,
					  64,
					  0,
					  64,
					  17,
					  183,
					  97,
					  192,
					  168,
					  1,
					  5,
					  192,
					  168,
					  1,
					  8,
					  0,
					  10,
					  4,
					  87,
					  0,
					  26,
					  119,
					  251,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0,
					  0};

	while (1)
	{
		enc28j60PacketSend(60, data);
		_delay_ms(3000);
	}
}
