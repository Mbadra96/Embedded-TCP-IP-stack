/*
 * http.h
 *
 * Created: 11/07/2019 6:01:15 PM
 *  Author: Mohamed Badra
 */ 


#ifndef HTTP_H_
#define HTTP_H_

#include "utils.h"
#include "socket.h"


void init_http(uint8_t *dst_ip,uint16_t src_port,uint16_t dst_port);

uint16_t get_request(uint16_t body_len,uint8_t *body);

#endif /* HTTP_H_ */