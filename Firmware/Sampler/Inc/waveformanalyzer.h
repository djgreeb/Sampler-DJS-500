/////////////////////////////////////////////////////////////////////////////////////////////////
// 	waveform analyzer
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void WFMCREATE(void);

uint32_t anlz_time;
static int16_t fir_x[15]; //input samples

//////////////80 Hz
int16_t FIRCoef[15] = { 
        16466,
        16642,
        16844,
        17086,
        17393,
        17816,
        18516,
        20610,
        18516,
        17816,
        17393,
        17086,
        16844,
        16642,
        16466};

int16_t fir(int16_t NewSample) 
	{
	int64_t y=0;            //output sample
	int n;
	for(n=14;n>0;n--)
		{
		fir_x[n] = fir_x[n-1];
		}
	fir_x[0] = NewSample;
	for(n=0;n<15;n++)
			{
			y+=FIRCoef[n]*fir_x[n];
			}
	y = y/262144;		
	return y;
	}

/////////////////////////////////////////////////	
//
// create waveform 100px
//	
void WFMCREATE(void)
	{	
	uint32_t i, pxl;
	uint32_t WFM[100];
	uint32_t CKL, addr, wmax;
	int16_t	CH1, CH2;	
	CKL = new_all_data/100;
	for(pxl=0;pxl<100;pxl++)				//scan amplitude
		{
		WFM[pxl] = 0;
		for(i=0;i<CKL;i++)	
			{
			addr = pxl*CKL + i;	
			CH1&=0x0000;	
			CH2&=0x0000;		
			CH1|=PCM[addr/8192][addr%8192][0];	
			CH2|=PCM[addr/8192][addr%8192][1];
			WFM[pxl]+= abs(CH1) + abs(CH2);	
			}		
		}
	wmax = 0;	
	for(pxl=0;pxl<100;pxl++)				//search max
		{		
		if(WFM[pxl]>wmax)
			{
			wmax = WFM[pxl];	
			}
		}	
	wmax = wmax/14;		//search devider	
	for(pxl=0;pxl<100;pxl++)				//normalize amplitude
		{		
		P_WAVEFORM[pad_x-1][pxl] = WFM[pxl]/wmax; 
		if(P_WAVEFORM[pad_x-1][pxl]>14)
			{
			P_WAVEFORM[pad_x-1][pxl] = 14;	
			}	
		}
	for(pxl=0;pxl<100;pxl++)
		{
		WFM[pxl] = 0;
		for(i=0;i<CKL;i++)	
			{
			addr = pxl*CKL + i;	
			WFM[pxl]+= abs(fir(PCM[addr/8192][addr%8192][0]));	
			}		
		for(i=0;i<CKL;i++)	
			{
			addr = pxl*CKL + i;
			WFM[pxl]+= abs(fir(PCM[addr/8192][addr%8192][1]));	
			}		
		}
	for(pxl=0;pxl<100;pxl++)				//colorize HF and LF
		{		 
		WFM[pxl]/=wmax;	
		if(WFM[pxl]>14)
			{
			WFM[pxl] = 14;	
			}		
		if(P_WAVEFORM[pad_x-1][pxl]>3)
			{
			if(((3*P_WAVEFORM[pad_x-1][pxl])<(4*WFM[pxl])))		//level 3/4
				{
				P_WAVEFORM[pad_x-1][pxl]|= 0x80;	
				}				
			}
		else if(P_WAVEFORM[pad_x-1][pxl]>0)
			{
			if(P_WAVEFORM[pad_x-1][pxl]==WFM[pxl])
				{
				P_WAVEFORM[pad_x-1][pxl]|= 0x80;	
				}		
			}
		}	
	return;	
	}
	
	

/////////////////////////////////////////////////////////////////////////////////////////////////

