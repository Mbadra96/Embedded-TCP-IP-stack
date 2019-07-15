/*
 * socket.c
 *
 * Created: 06/07/2019 5:00:00 AM
 *  Author: Mohamed Badra
 */

#include "socket.h"
uint8_t buffer[1024] = {0};
uint8_t src_mac[] = MAC_ADD;

void init_system(void)
{

	_delay_loop_1(50);
	enc28j60Init(src_mac);
	enc28j60clkout(2);
	_delay_loop_1(50);

	init_ether_struct(src_mac);

	init_ip_struct();
	init_udp_struct();
	init_tcp_struct();
	init_dhcp_struct(src_mac);
}

void send_tcp_data(uint16_t len, uint8_t *data, uint8_t flag)
{
	reset_buffer();
	init_ether_in_buffer();

	set_ip_protocol(6); // 17 for udp 6 for tcp which is the default value

	init_ip_in_buffer();

	init_tcp_in_buffer(flag);
	for (uint16_t i = 0; i < len; i++)
	{
		buffer[TCP_FINISH + i] = data[i];
	}

	set_ip_total_length(TCP_LEN + IP_LEN + len);
	enc28j60PacketSend(len + TCP_LEN + IP_LEN + ETH_LEN, buffer);
}
void send_udp_data(uint16_t len, uint8_t *data)
{
	reset_buffer();
	init_ether_in_buffer();
	set_ip_protocol(17); // 17 for udp 6 for tcp which is the default value
	init_ip_in_buffer();
	init_udp_in_buffer(len);
	for (uint16_t i = 0; i < len; i++)
	{
		buffer[UDP_FINISH + i] = data[i];
	}

	set_ip_total_length(IP_LEN + UDP_LEN + len);
	enc28j60PacketSend(len + IP_LEN + UDP_LEN + ETH_LEN, buffer);
}

uint8_t receive_data(uint8_t (*check_fnc)(void))
{
	reset_buffer();
	uint8_t flag = 0;

	uint16_t len = enc28j60PacketReceive(1024, buffer);
	while (!flag)
	{
		if (len > 0)
		{
			flag = check_fnc();
		}
		else
		{
			return 0;
		}
		_delay_ms(100);
		if (!flag)
		{
			reset_buffer();
			len = enc28j60PacketReceive(1024, buffer); //max length to receive is 1024
		}
	}
	return 1;
}

void send_dhcp_discover(void)
{
	reset_buffer();
	uint16_t len = set_dhcp_discover_in_buffer();
	init_dhcp_in_buffer();
	set_udp_src_port(68);
	set_udp_dst_port(67);
	init_udp_in_buffer(len);
	set_ip_protocol(17); // 17 for udp 6 for tcp which is the default value
	init_ip_in_buffer();
	init_ether_in_buffer();
	set_ip_total_length(IP_LEN + UDP_LEN + len);
	enc28j60PacketSend(len + IP_LEN + UDP_LEN + ETH_LEN, buffer);
}

void config_ip_address(void)
{

	send_dhcp_discover();
	reset_buffer();
	while (!receive_data(check_id))
	{
		send_dhcp_discover();
	}
	get_dhcp_offer_ip_pointer_from_buffer();
	send_dhcp_request();
}

void send_dhcp_request(void)
{
	reset_buffer();
	uint16_t len = set_dhcp_request_in_buffer();
	init_dhcp_in_buffer();
	set_udp_src_port(68);
	set_udp_dst_port(67);
	init_udp_in_buffer(len);
	set_ip_protocol(17); // 17 for udp 6 for tcp which is the default value
	init_ip_in_buffer();
	init_ether_in_buffer();
	set_ip_total_length(IP_LEN + UDP_LEN + len);
	enc28j60PacketSend(len + IP_LEN + UDP_LEN + ETH_LEN, buffer);
}

uint8_t socket_connect(socket sock)
{

	uint8_t dst_mac[] = {0xec, 0x55, 0xf9, 0x90, 0x12, 0xfd};
	;
	//get_mac_from_cache(check_return_mac(dst_ip));
	set_src_ip(get_dhcp_src_ip());
	set_dst_ip(sock.dst_ip);
	set_ether_dst_mac(dst_mac);
	set_tcp_src_port(sock.src_port);
	set_tcp_dst_port(sock.dst_port);
	set_tcp_ack_offset(1);
	// Send SYN and wait for ACK
	uint8_t count = 5;
	do
	{
		if (count % 5 == 0)
		{
			send_tcp_data(0, 0, TCP_SYN_FLAG);
			set_tcp_state(SYN_SENT);
		}
		count++;
		if (count > 50)
			return 0;
	} while (!receive_data(check_tcp_ack));

	// adding the new seq in the ack
	add_to_tcp_seq_ack(1, 1);
	// send new ack to connect
	send_tcp_data(0, 0, TCP_ACK_FLAG);
	return 1;
}

uint8_t socket_send(socket sock, uint16_t len, uint8_t *data)
{
	uint8_t dst_mac[] = {0xec, 0x55, 0xf9, 0x90, 0x12, 0xfd};
	set_src_ip(get_dhcp_src_ip());
	set_dst_ip(sock.dst_ip);
	set_ether_dst_mac(dst_mac);
	set_tcp_src_port(sock.src_port);
	set_tcp_dst_port(sock.dst_port);
	if (get_tcp_state() == ESTABLISHED)
	{
		set_tcp_ack_offset(len);
		uint8_t count = 5;
		do
		{
			if (count % 5 == 0)
			{
				send_tcp_data(len, data, TCP_PSH_FLAG | TCP_ACK_FLAG);
			}
			count++;
			if (count > 50)
				return 0;
		} while (!receive_data(check_tcp_ack));
		add_to_tcp_seq_ack(len, 0);
		return 1;
	}
	return 0;
}

uint16_t socket_receive(uint8_t *data, socket sock)
{
	uint8_t dst_mac[] = {0xec, 0x55, 0xf9, 0x90, 0x12, 0xfd};
	//get_mac_from_cache(check_return_mac(dst_ip));
	set_src_ip(get_dhcp_src_ip());
	set_dst_ip(sock.dst_ip);
	set_ether_dst_mac(dst_mac);
	set_tcp_src_port(sock.src_port);
	set_tcp_dst_port(sock.dst_port);
	set_tcp_ack_offset(0);
	while (!receive_data(check_tcp_ack))
		;

	uint16_t data_len = get_data_length();

	for (uint16_t i = 0; i < data_len; i++)
	{
		data[i] = buffer[TCP_FINISH + i];
	}

	add_to_tcp_seq_ack(0, data_len);

	send_tcp_data(0, 0, TCP_ACK_FLAG);

	return data_len;
}

void socket_close(socket sock)
{
	uint8_t dst_mac[] = {0xec, 0x55, 0xf9, 0x90, 0x12, 0xfd};
	//get_mac_from_cache(check_return_mac(dst_ip));
	set_src_ip(get_dhcp_src_ip());
	set_dst_ip(sock.dst_ip);
	set_ether_dst_mac(dst_mac);
	set_tcp_src_port(sock.src_port);
	set_tcp_dst_port(sock.dst_port);
	set_tcp_ack_offset(1);
	add_to_tcp_seq_ack(0, 1);
	_delay_ms(1000);
	if (receive_data(check_tcp_ack))
	{
		send_tcp_data(0, 0, TCP_ACK_FLAG);
		// Send FIN and wait for ACK
		uint8_t count = 5;
		do
		{
			if (count % 5 == 0)
			{
				send_tcp_data(0, 0, TCP_FIN_FLAG | TCP_ACK_FLAG);
			}
			count++;
			if (count > 50)
				return;
		} while (!receive_data(check_tcp_ack));
	}

	else
	{

		uint8_t count = 5;
		do
		{
			if (count % 5 == 0)
			{
				send_tcp_data(0, 0, TCP_FIN_FLAG | TCP_ACK_FLAG);
			}
			count++;
			if (count > 50)
				return;
		} while (!receive_data(check_tcp_ack));
		while (!receive_data(check_tcp_ack))
			;

		send_tcp_data(0, 0, TCP_ACK_FLAG);
	}
}