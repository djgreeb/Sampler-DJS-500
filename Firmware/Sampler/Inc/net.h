#ifndef NET_H_
#define NET_H_
//-----------------------------------------------
#include "stm32f7xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "lwip.h"
#include "lwip/udp.h"
//-----------------------------------------------
void udp_client_connect(void);
void udp_client_send (uint8_t part);
//-----------------------------------------------
#endif /* NET_H_ */
