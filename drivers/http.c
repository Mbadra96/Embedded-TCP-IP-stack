/*
 * http.c
 *
 * Created: 11/07/2019 6:05:02 PM
 *  Author: Mohamed Badra
 */ 


#include "http.h"
socket sock;

uint8_t get_array[] = "GET / HTTP/1.1\r\n";
uint8_t host[] = "Host: 192.168.1.4:65432\r\n";

void init_http(uint8_t *dst_ip,uint16_t src_port,uint16_t dst_port){
	init_system();
	for (uint8_t i=0;i<4;i++)
	{
		sock.dst_ip[i]=dst_ip[i];
	}
	sock.src_port = src_port;
	sock.dst_port =dst_port;
	config_ip_address();
}

uint16_t get_request(uint16_t body_len,uint8_t *body){
	socket_connect(sock);
	uint16_t head_count = 0;
	uint8_t data[sizeof(get_array)+sizeof(host)+2+body_len];
	uint8_t i;
	for (i = head_count ;i<sizeof(get_array)+head_count-1;i++)
	{
		data[i]=get_array[i-head_count];
	}
	head_count=i;
	for (i = head_count ;i<sizeof(host)+head_count-1;i++)
	{
		data[i]=host[i-head_count];
	}
	head_count=i;
	data[head_count]='\r';
	data[head_count+1]='\n';
	head_count+=2;
	
	for (i = head_count ;i<body_len+head_count-1;i++)
	{
		data[i]=body[i-head_count];
	}
	head_count=i;
	//uint8_t len = socket_receive(data,sock);
	socket_send(sock,head_count,data);
	uint8_t d[200];
	socket_receive(d,sock);
	socket_close(sock);
	return 1;
}
