/*
 * utils.c
 *
 * Created: 06/07/2019 4:16:06 AM
 *  Author: Mohamed Badra
 */ 
 #include "utils.h"
extern uint8_t buffer[];
uint16_t checksum(uint8_t *buffer_ptr,uint8_t check_len){
	uint32_t sum = 0;
	for (int i = 0;i<check_len;i+=2)
	sum+=((uint16_t)buffer_ptr[i] << 8) | buffer_ptr[i+1];
	
	uint8_t mse_no = (uint8_t)((sum>>16));
	uint16_t lse_no =(uint16_t) sum ;
	
	return ~(mse_no+lse_no);
}


void reset_buffer(void){
	/* this function used to reset the buffer */
	memset(buffer,0,1024);
}
