/*
 * tcp.c
 *
 * Created: 06/07/2019 4:30:56 AM
 *  Author: Mohamed Badra
 
 */ 
#include "tcp.h"

extern uint8_t buffer[];
tcp tcp_struct;


void init_tcp_struct(void){
	tcp_struct.state = CLOSED; 
	tcp_struct.src_port=0;
	tcp_struct.dst_port=0;
	tcp_struct.ackno.num =0;
	tcp_struct.seqno.num =0;
	tcp_struct.hl_config = 0x5000;
	tcp_struct.window_size =1024;
	tcp_struct.urgent_pointer = 0;
}

void init_tcp_in_buffer(uint8_t flag){
		buffer[TCP_SRC_PORT] = (uint8_t) (tcp_struct.src_port >>8);
		buffer[TCP_SRC_PORT+1] = (uint8_t) tcp_struct.src_port;
		buffer[TCP_DST_PORT] = (uint8_t) (tcp_struct.dst_port >>8);
		buffer[TCP_DST_PORT+1] = (uint8_t) tcp_struct.dst_port;
	for (uint8_t i = 0;i<4;i++){
		buffer[TCP_SEQ_NUM+i] = tcp_struct.seqno.array[3-i];
		buffer[TCP_ACK+i] = tcp_struct.ackno.array[3-i];
	}
	buffer[TCP_HEAD_LEN_RESERVED_CONFIG] = (uint8_t)(tcp_struct.hl_config >> 8);
	buffer[TCP_HEAD_LEN_RESERVED_CONFIG+1] = (uint8_t) tcp_struct.hl_config;
	buffer[TCP_HEAD_LEN_RESERVED_CONFIG+1] |=flag;
	buffer[TCP_WINDOW_SIZE] = (uint8_t)(tcp_struct.window_size >> 8);
	buffer[TCP_WINDOW_SIZE+1] = (uint8_t) tcp_struct.window_size;
	buffer[TCP_UGRENT_POINTER] = (uint8_t)(tcp_struct.urgent_pointer >> 8);
	buffer[TCP_UGRENT_POINTER+1] = (uint8_t) tcp_struct.urgent_pointer;
	uint16_t tmp_sum = checksum(&buffer[TCP_START],20);
	buffer[TCP_CHECK_SUM] = (uint8_t) (tmp_sum >> 8);
	buffer[TCP_CHECK_SUM+1] = (uint8_t) tmp_sum;
	
}

uint16_t get_src_port(void){
	return ((uint16_t) buffer[TCP_SRC_PORT]<<8)|buffer[TCP_SRC_PORT+1];
}

uint16_t get_dst_port(void){
	return ((uint16_t) buffer[TCP_DST_PORT]<<8)|buffer[TCP_DST_PORT+1];
}

void set_tcp_src_port(uint16_t port){
	tcp_struct.src_port = port;
}

void set_tcp_dst_port(uint16_t port){
	tcp_struct.dst_port = port;
}

uint8_t check_tcp_ack(void){
	seq data;
	data.num = tcp_struct.seqno.num+tcp_struct.ack_offset;
	
	for(uint8_t i = 0 ;i<4;i++){
		if(data.array[3-i] != buffer[TCP_ACK+i]){
			return 0;
		}
	}
	
	for(uint8_t i=0;i<4;i++){
		tcp_struct.ackno.array[3-i] = buffer[TCP_SEQ_NUM+i];
	}
	
	if(buffer[TCP_HEAD_LEN_RESERVED_CONFIG+1] == (TCP_ACK_FLAG|TCP_SYN_FLAG)){
		set_tcp_state(ESTABLISHED);
	}
	else if(buffer[TCP_HEAD_LEN_RESERVED_CONFIG+1] == (TCP_ACK_FLAG)){
		
		 //if(get_tcp_state()==FIN_WAIT_1) set_tcp_state(FIN_WAIT_2);
		 //else if(get_tcp_state()==CLOSING) set_tcp_state(TIME_WAIT);
		
	}
	else if(buffer[TCP_HEAD_LEN_RESERVED_CONFIG+1] == (TCP_ACK_FLAG|TCP_FIN_FLAG)){
		//if(get_tcp_state()==FIN_WAIT_1) set_tcp_state(TIME_WAIT);
	}
	else if(buffer[TCP_HEAD_LEN_RESERVED_CONFIG+1] == (TCP_FIN_FLAG)){
		//if(get_tcp_state()==FIN_WAIT_1) set_tcp_state(CLOSING);
		//else if(get_tcp_state()==FIN_WAIT_2) set_tcp_state(TIME_WAIT);
	}
	return 1;
	
	
}

void add_to_tcp_seq_ack(uint32_t seq_inc,uint32_t ack_inc){
	
	//for (uint8_t i=0;i<4;i++)
	//{
	//	tcp_struct.ackno.array[3-i]=buffer[TCP_SEQ_NUM+i];
	//}
	tcp_struct.seqno.num +=seq_inc;
	tcp_struct.ackno.num +=ack_inc;

}

void set_tcp_ack_offset(uint16_t len){
	tcp_struct.ack_offset = len;
}

uint8_t get_tcp_state(void){
	return tcp_struct.state;
}

void set_tcp_state(uint8_t state){
	if(state<=5) tcp_struct.state =state;
}

uint16_t get_data_length(void){
	return ((uint16_t)(buffer[IP_TOT_LEN]<<8)|(buffer[IP_TOT_LEN+1])) - ((buffer[IP_VER_HEAD_LEN] & 0x0f)*4)-(((buffer[TCP_HEAD_LEN_RESERVED_CONFIG]& 0xf0)>>4)*4);
}