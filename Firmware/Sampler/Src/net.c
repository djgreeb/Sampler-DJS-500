//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "net.h"
#include "usart.h"
//-----------------------------------------------
struct udp_pcb *upcb;
struct udp_pcb *upcb2;


//char str1[54] = {0x51, 0x73, 0x70, 0x74, 0x31, 0x57, 0x6D, 0x4A, 0x4F, 0x4C, 0x06, 0x00, 0x43, 0x44, 0x4a, 0x2d,
//								 0x31, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//								 0x01, 0x02, 0x00, 0x36, 0x05, 0x01, 0xEE, 0x81, 0xEA, 0xAA, 0xDD, 0xF1, 169, 254, 40, 241, 
//								 0x01, 0x00, 0x00, 0x00, 0x01, 0x00};

char str1[54] = {0x51, 0x73, 0x70, 0x74, 0x31, 0x57, 0x6D, 0x4A, 0x4F, 0x4C, 0x06, 0x00, 0x43, 0x44, 0x4a, 0x2d,
								 0x32, 0x30, 0x30, 0x30, 0x6E, 0x65, 0x78, 0x75, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
								 0x01, 0x02, 0x00, 0x36, 0x03, 0x01, 0xEE, 0x81, 0xEA, 0xAA, 0xDD, 0xF1, 169, 254, 40, 241, 
								 0x01, 0x00, 0x00, 0x00, 0x01, 0x00};
								 								 
//uint8_t TXDATA[190] = {0};
								 
extern uint32_t UTILITY_SETTINGS[10];

//-----------------------------------------------
void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);


///////////////////////////////////////////////
//receive callback	
//	
void udp_client_connect(void)
	{
  ip_addr_t DestIPaddr;
	ip_addr_t DestIPaddr2;
//  err_t err;
	upcb2 = udp_new();
  if (upcb2!=NULL)
		{
  	IP4_ADDR(&DestIPaddr2, UTILITY_SETTINGS[7]>>24, (UTILITY_SETTINGS[7]>>16)&0x000000FF, (UTILITY_SETTINGS[7]>>8)&0x000000FF, UTILITY_SETTINGS[7]&0x000000FF);		//adress PC					//169, 254, 40, 241   - board IP
  	upcb2->local_port = 50002;			//port discovery
  	udp_connect(upcb2, &DestIPaddr2, 50000);				//port PC (CDJ)		
		}

  upcb = udp_new();
  if (upcb!=NULL)
		{
  	IP4_ADDR(&DestIPaddr, UTILITY_SETTINGS[8]>>24, (UTILITY_SETTINGS[8]>>16)&0x000000FF, (UTILITY_SETTINGS[8]>>8)&0x000000FF, UTILITY_SETTINGS[8]&0x000000FF);			//adress PC					//169, 254, 40, 241   - board IP
  	upcb->local_port = 50002;			//port discovery
  	udp_connect(upcb, &DestIPaddr, 50000);				//port PC (CDJ)
		}
	}

	
///////////////////////////////////////////////
//UDP SEND
//	
void udp_client_send(uint8_t part)
	{
  struct pbuf *p;
	
	if(part==1)
		{
		p = pbuf_alloc(PBUF_TRANSPORT, 54, PBUF_POOL);		
		if(p!=NULL)
			{
			pbuf_take(p, (void *) str1, 54);			
			udp_send(upcb, p);	
			pbuf_free(p);
			}	
		}
	else if(part==2)
		{
		p = pbuf_alloc(PBUF_TRANSPORT, 54, PBUF_POOL);
		if(p!=NULL)
			{
			pbuf_take(p, (void *) str1, 54);			
			udp_send(upcb2, p);	
			pbuf_free(p);
			}				
		}
	}

	
	
	

///////////////////////////////////////////////
//receive callback	
//	
void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
	{
  //strncpy(str1,p->payload,p->len);
  //str1[p->len]=0;
  
//	memcpy(TXDATA, p->payload,p->len);
//  TXDATA[p->len]=13;	
	//HAL_UART_Transmit(&huart1, TXDATA, p->len, 100);	
		
		
//  HAL_GPIO_TogglePin(GPIOI, LED_Pin);
	pbuf_free(p);		
	}


	
	
	



