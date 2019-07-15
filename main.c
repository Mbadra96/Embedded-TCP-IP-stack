/*
 * RestAvr.c
 *
 * Created: 06/07/2019 2:05:30 AM
 * Author : Mohamed Badra and Ahmed Saad
 */

#include <avr/io.h>
#include "drivers/http.h"
int main(void)
{
	init_system();

	_delay_ms(3000);
	// dst_ip[]={192,168,1,4};
	//init_http(dst_ip,1111,65432);
	//uint8_t data[]= "{\"HELLO\":\"BADRA\"}";
	//get_request(0,NULL);
}
