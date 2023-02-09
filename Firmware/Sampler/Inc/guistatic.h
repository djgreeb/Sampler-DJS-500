/////////////////////////////////////////////////////////////////////////////////////////////////
// GUI variables and static color maps
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

//colors for pads displayed on the LCD
const uint32_t PADS_LABEL_COLOR[8] = {0xFFFF3F7A,
																0xFFFF0000,
																0xFFFF9307,
																0xFFEFD700,
																0xFF5AE000,
																0xFF00ECE8,	
																0xFF0050F8,
																0xFFB53DCB};	

															
//colors for pads displayed on the LCD low brightness
//internal filling of pads
const uint32_t PADS_LABEL_LOW_COLOR[8] = {0xFF320C18,
																		0xFF340000,
																		0xFF321D01,
																		0xFF341E01,
																		0xFF122E00,
																		0xFF001F1E,	
																		0xFF001031,
																		0xFF240C28};	
																							
const uint32_t BLUE_BAR[4][14] = {
    0xffe5e5fb, 0xffe5e5fb, 0xffe5e5fb, 0xffe5e5fb, 0xffe2e2fb, 0xffdcdcfa, 0xffd5d5f8, 0xffc9c9f6, 0xffbbbbf4, 0xffaaaaf2, 0xff9696ef, 0xff8181ec, 0xff6c6ce8, 0xff5757e5, 
    0xffe2e2fb, 0xffe1e1fb, 0xffe0e0fb, 0xffddddf9, 0xffd9d9f9, 0xffd1d1f8, 0xffc8c8f7, 0xffbcbcf5, 0xffadadf2, 0xff9c9cf0, 0xff8888ee, 0xff7474ea, 0xff6060e6, 0xff4d4de4, 
    0xffc0c0f5, 0xffbfbff5, 0xffbcbcf5, 0xffb7b7f4, 0xffafaff3, 0xffa7a7f2, 0xff9b9bf0, 0xff8e8eee, 0xff8080ec, 0xff7171e9, 0xff6060e7, 0xff5050e4, 0xff4040e2, 0xff3232e1, 
    0xff7878ea, 0xff7878ea, 0xff7575ea, 0xff7070e9, 0xff6a6ae8, 0xff6363e7, 0xff5959e6, 0xff5050e5, 0xff4646e3, 0xff3a3ae2, 0xff3030df, 0xff2626de, 0xff1d1ddc, 0xff1414db
};
const uint32_t RED_BAR[4][14] = {
    0xfffae3df, 0xfffae3df, 0xfffae3de, 0xfffae2dd, 0xfff9dfdb, 0xfff8dbd7, 0xfff6d5ce, 0xfff6ccc3, 0xfff3bfb5, 0xfff0b0a5, 0xffed9f92, 0xffea8e7d, 0xffe77d68, 0xffe46a55, 
    0xfff9dfdb, 0xfff9dfdb, 0xfff9deda, 0xfff8dcd7, 0xfff8d8d3, 0xfff6d2cc, 0xfff5cac2, 0xfff4c0b6, 0xfff1b3a8, 0xffefa497, 0xffec9484, 0xffe88371, 0xffe5725d, 0xffe3624b, 
    0xfff4c2ba, 0xfff4c2b9, 0xfff3c0b6, 0xfff3bbb1, 0xfff1b6aa, 0xfff0ada2, 0xffefa597, 0xffed998a, 0xffea8d7c, 0xffe87f6d, 0xffe5725d, 0xffe3644d, 0xffe0573e, 0xffde4b30, 
    0xffe98775, 0xffe98674, 0xffe88472, 0xffe8806c, 0xffe77b66, 0xffe67460, 0xffe46d57, 0xffe2654e, 0xffe15c44, 0xffe05339, 0xffdd492e, 0xffdc4125, 0xffda391b, 0xffd93113
};
																																																	
//original from dump cdj																	
const uint32_t WF_COLOR_MAP[9] = {
											0xFFFAFAFF,
											0xFFD0E8F8,
											0xFF90C0F8,
											0xFF78C0E0,
											0xFF10B8E8,
											0xFF0890F8,
											0xFF1080B8,
											0xFF106098,
											0xFF106098};	//<= duplicate last color for blocking overflow																	
																												
const uint32_t WS_COLOR_MAP[2] = {0xFF9DC7ED,		
																	0xFF5D799E};

#define CUE_COLOR									0xFFF08138
#define DARK_CUE_COLOR						0xFF9C4F1C																			
#define	CUE_COLOR_0								0xFF331A09 																
#define	CUE_COLOR_1								0xFF40200B															
#define	CUE_COLOR_2								0xFF4F280E 																		
#define	CUE_COLOR_3								0xFF5E3011																		
#define	BLUE_COLOR_0							0xFF2A2A54 																
#define	BLUE_COLOR_1							0xFF343469																
#define	BLUE_COLOR_2							0xFF414182																	
#define	BLUE_COLOR_3							0xFF4E4E9C																										
#define	BLUE_GRADIENT_00					0xFF2F2F5C 																			
#define	BLUE_GRADIENT_0						0xFF36376D 																
#define	BLUE_GRADIENT_1						0xFF404082																
#define	BLUE_GRADIENT_2						0xFF4E4E9B																	
#define	BLUE_GRADIENT_3						0xFF5A5AB4
#define	RED_GRADIENT_00						0xFF6B0000	
#define	RED_GRADIENT_0						0xFF7A0000															
#define	RED_GRADIENT_1						0xFF8D0000																
#define	RED_GRADIENT_2						0xFF9F0000																	
#define	RED_GRADIENT_3						0xFFB70000
#define	GREY_GRADIENT_00					0xFF454545
#define	GREY_GRADIENT_0						0xFF505050 																
#define	GREY_GRADIENT_1						0xFF5F5F5F																
#define	GREY_GRADIENT_2						0xFF6E6E6E																	
#define	GREY_GRADIENT_3						0xFF7E7E7E
#define	GREY_PERIMETER_L					0xFF333333	
#define	GREY_PERIMETER_H					0xFF7D7D7D
#define	RED_PERIMETER_L						0xFF4E2727
#define	RED_PERIMETER_H						0xFFB32121
#define	BLUE_PERIMETER_L					0xFF27274F	
#define	BLUE_PERIMETER_H					0xFF5959B2
#define	RED_PERIMETER_SQ					0xFFD90000
#define	GREY_SQ_L									0xFF999999	//0xFFABABAB	
#define	GREY_SQ_H									0xFFE2E2E2
#define	RED_SQ_L									0xFFBF5F5F	//0xFFD46969	
#define	RED_SQ_H									0xFFFF4848
#define	BLUE_SQ_L									0xFF5F5FBF	//0xFF6969D4	
#define	BLUE_SQ_H									0xFF9898FF
#define	PAD_BACK_COLOR 						0xFF000000		//0xFF101010	//0xFF252525
#define	SQ_BACK_COLOR 						0xFF000000 		//0xFF141414
#define	PERIPH_PAD_GRADIENT_0			0xFF676767	//0xFF333333
#define	PERIPH_PAD_GRADIENT_1			0xFF828282	//0xFF414141
#define	PERIPH_PAD_GRADIENT_2			0xFF909090	//0xFF525252
#define	PERIPH_PAD_GRADIENT_3			0xFF9E9E9E
#define LCD_COLOR_DGREEN           	((uint32_t)0xFF00CD00)
#define LCD_COLOR_LIGHT_1           ((uint32_t)0xFFDFDFDF)				//color for line-cursor browser
#define LCD_COLOR_LIGHT_2           ((uint32_t)0xFFEFEFEF)				//color for line-cursor browser
#define LCD_COLOR_LIGHT_3						((uint32_t)0xFFCFCFCF)				//color for secondary line-cursor UTILITY
#define LCD_COLOR_LIGHT_4						((uint32_t)0xFFAFAFAF)				//color for secondary line-cursor UTILITY
#define LCD_COLOR_LIGHT_5						((uint32_t)0xFFBFBFBF)				//color for secondary line-cursor UTILITY
#define LCD_COLOR_DARK_1           	((uint32_t)0xFF606060)
#define LCD_COLOR_DARK_2           	((uint32_t)0xFF404040)
#define LCD_COLOR_DARK_11          	((uint32_t)0xFF737373)
#define LCD_COLOR_DARK_12           ((uint32_t)0xFFC1C1C1)
#define LCD_COLOR_DARK_21          	((uint32_t)0xFF4D4D4D)
#define LCD_COLOR_DARK_22           ((uint32_t)0xFF7F7F7F)
#define LCD_COLOR_PAPER           	((uint32_t)0xFFFFFCE3)
#define LCD_COLOR_SHADOW           	((uint32_t)0xFFD4D4D4)
#define LCD_COLOR_DISABLE 					((uint32_t)0xFF7A766C)
#define TEXT_PAD_COLOR 							((uint32_t)0xFF171717)
#define DIALOG_BACK_COLOR 					((uint32_t)0xFFD90052)
#define PATH_COLOR 									((uint32_t)0xFF7BA2C4)				//color for pad_x edit - path
#define ICON_SELBG_COLOR						((uint32_t)0xFFBDBBA8)
#define ICON_SELROND_COLOR					((uint32_t)0xFFDEDBC5)
#define KBRD_TRANPARENT_COLOR				((uint32_t)0x8F000000)
#define KBRD_RED_COLOR							((uint32_t)0xFFFF9F9F)
#define SQ_STEP_CLR_0								0xFFFF5F8F
#define SQ_STEP_CLR_1								0xFFFF89B0
#define SQ_STEP_CLR_2								0xFFFFB6D5
#define SQ_STEP_CLR_3								0xFFFFD7EF
#define MOVE_PRESET_COLOR						0xFFC60000

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

