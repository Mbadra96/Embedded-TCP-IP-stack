

#include "udp.h"


extern uint8_t buffer[];
udp udp_struct;


void init_udp_struct(void){
	udp_struct.src_port=0;
	udp_struct.dst_port=0;
	udp_struct.length = 8;
	udp_struct.check_sum =0;
}


void init_udp_in_buffer(void){
		buffer[UDP_SRC_PORT] = (uint8_t) (udp_struct.src_port >>8);
		buffer[UDP_SRC_PORT+1] = (uint8_t) udp_struct.src_port;
		buffer[UDP_DST_PORT] = (uint8_t) (udp_struct.dst_port >>8);
		buffer[UDP_DST_PORT+1] = (uint8_t) udp_struct.dst_port;
        buffer[UDP_LEN] = (uint8_t) (udp_struct.length>>8);
        buffer[UDP_LEN+1] = (uint8_t) (udp_struct.length);
        buffer[UDP_CHK_SUM] = (uint8_t) (udp_struct.check_sum>>8);
        buffer[UDP_CHK_SUM+1] = (uint8_t) (udp_struct.check_sum);
}


void set_udp_src_port(uint16_t port){
	 udp_struct.src_port =  port;
}

void set_udp_dst_port(uint16_t port){
	 udp_struct.dst_port =  port;
 }


void set_udp_length(uint16_t len){
	
	udp_struct.length = 8+ len;
	
}
