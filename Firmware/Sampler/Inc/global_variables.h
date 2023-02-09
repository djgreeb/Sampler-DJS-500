/////////////////////////////////////////////////////////////////////////////////////////////////
// 	global variables
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

					
					
///////////////////////////////////////////FatFS///////////////////
unsigned int nbytes;
FRESULT res;
FIL file;
FILINFO fno;
FATFS FAT;
DIR dir;
uint32_t free_mem = 0;
uint32_t used_mem = 0;
char sample_path[]="0:/SAMPLER";
char presets_path[]="0:/SAMPLER/Presets.pst";
char fldname[]="SAMPLER";
uint8_t need_rw_setings_prc = 0;				//rewrite settings
uint8_t need_rw_preset_prc = 0;					//rewrite preset settings
uint8_t need_rw_pad_prc = 0;						//rewrite pad settings
uint8_t wdata[1584];										//buffer for read/write sd card
uint32_t ram = 0;


/* Global temp counter variables ---------------------------------------------------------*/
uint32_t mi;	

/* Audio processing variables ---------------------------------------------------------*/
#include "audio.h"

/* presets variables ---------------------------------------------------------*/
uint8_t presets_list[64][32] = {0};					//max 64 presets x 32 symbols
uint8_t presets_pads_colors[64][8];					//max 64 presets
uint8_t presets_icon[64];										//max 64 presets
uint8_t presets_rating[64];									//max 64 presets
uint8_t presets_color[64];									//max 64 presets
uint8_t TOTAL_PRESETS = 0;									//0 none 64 max
uint8_t CurrentPRSTPosition = 1;			//1....TOTAL_PRESETS-12
uint8_t PRSTCCP = 0;			//0...12 position
uint8_t CURRENT_PRESET = 0xFF;
uint8_t FAST_LOADING[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t P_WAVEFORM[8][100];	
uint8_t P_SAMPLE_NAME[8][64];
uint8_t P_COLOR[8];		
uint8_t P_TYPE[8];						//0-sample, 1-sequencer;
uint8_t P_QUANTIZE[8];				//0-disable, 1-enable
uint8_t P_SYNC[8];						//0-none sync, 1-sync enable
uint8_t P_TRIG[8];						//0-one shot, 1-loop
uint16_t P_BPM[8];						
uint8_t P_GAIN[8];
uint32_t P_SAMPLE_OFFSET[9];			//P_SAMPLE_OFFSET[pd] = P_SAMPLE_OFFSET[pd-1] + P_ALL_D[pd-1];
uint32_t P_START_ADR[8];					//strat adress in audio file for pointer for reading (in samples)
uint8_t load_status = 0;
uint8_t pad_x = 0;					//current edit pad 1...8. 0 - none

/* Display and static information variables ---------------------------------------------------------*/
#include "guistatic.h"
#define LCD_FRAME_BUFFER    SDRAM_DEVICE_ADDR
#define LCD_FRAME_BUFFER_2	((uint32_t)0xC0780800)	
uint8_t lcd_status = LCD_OK;
uint8_t Buf[64]={0};
uint16_t originalBPM = 0xFFFF;						//this original BPM*100 of track (pitch = 0.00%) 
							
uint16_t previousMD = 0xFF;					//master deck on display
uint16_t previous_MPHASE_color = 0xFF;
uint16_t PreviousSPhase = 0;
uint16_t PreviousMPhase = 0;
	
#define HOME_DISPLAY 				0
#define PRST_LIST 					1
#define FLLIST_DISPLAY			2
#define UTILITY							3
#define EDIT_PRST						4
#define EDIT_LIST						5
#define DELDIALOG						6
#define EDIT_PAD_DISPLAY		7
#define EDIT_PRESET_DISPLAY	8
#define EDIT_FLLIST_DISPLAY	9
#define EDIT_UTILITY				10
#define KEYBOARD						11
#define BROWSER							12
#define MOVE_PRESET					13
uint8_t dSHOW = 0xFF;		

uint8_t ScrollLong = 142;								//5...142
uint8_t ScrollPosition = 0;							//0...142-ScrollLong
#define PRST_LIST_UP		0
#define PRST_LIST_DOWN	1
#define UTILITY_DOWN		2
#define UTILITY_UP			3
#define EP_DOWN					4
#define EP_UP						5
#define EL_DOWN					6
#define EL_UP						7
#define DELDIALOG_DOWN	8
#define DELDIALOG_UP		9
#define EU_DOWN					10
#define EU_UP						11
#define EPD_DOWN				12
#define EPD_UP					13
#define EPRD_DOWN				14
#define EPRD_UP					15
#define BR_LIST_UP			16
#define BR_LIST_DOWN		17
#define EFL_DOWN				18
#define EFL_UP					19
#define MPRST_UP				20
#define MPRST_DOWN			21

uint8_t show_status_string = 0xFF;
uint8_t need_redraw_effect = 0;
uint8_t need_redraw_syncout = 0;
	
/* UDP Ethernet ---------------------------------------------------------*/
uint8_t UDP_SEND_PART = 1;
uint8_t UDP_SPHASE = 0;
uint8_t UDP_MPHASE = 0;
uint8_t UDP_NEED_UPDATE_SPHASE = 0;
uint8_t UDP_NEED_UPDATE_MPHASE = 0;
uint16_t UDP_MPHASE_CNT;
uint32_t UDP_BPM = 0xFFFFFFFF;			//example 120.00 bpm
uint8_t UDP_NEED_UPDATE_BPM = 0;
uint8_t UDP_MD = 0; 
uint8_t UDP_NEED_UPDATE_MD = 0;
uint8_t link_req = 0;     //timer for link request
uint8_t link_status = 0xFF;     //link status 0 - disable 1 - disable.access 2 - connect
uint8_t previous_link_status = 0xFF;
uint8_t send_connect = 0;
uint8_t MAC_ADR[6] = {0};

/* BUTTONS ---------------------------------------------------------*/
uint8_t KEY_PRESET_pressed = 0; 
uint8_t KEY_SHIFT_pressed = 0; 
uint8_t KEY_EDIT_pressed = 0; 
uint8_t KEY_MENU_pressed = 0; 
uint8_t KEY_BACK_pressed = 0; 
uint8_t KEY_SYNC_OUT_pressed = 0; 
uint8_t KEY_EFFECT_pressed = 0; 
uint8_t KEY_ENC_pressed = 0; 
uint8_t SYNC_OUT_ON = 1;
uint8_t EFFECT_ON = 0;
uint32_t sync_out_tim = 0;							//timer for sync out led
uint8_t KEY_MENU_HOLD = 0; 
uint32_t KEY_MENU_HOLD_TIM = 0;
uint32_t KEY_ENC_tim;										//for noise button filter
uint32_t KEY_PRESET_tim;										//for noise button filter
uint32_t KEY_SHIFT_tim;										//for noise button filter
uint32_t KEY_EDIT_tim;										//for noise button filter
uint32_t KEY_BACK_tim;										//for noise button filter
uint32_t KEY_EFFECT_tim;										//for noise button filter


/* ENCODER ---------------------------------------------------------*/
uint8_t enc_prev_dir = 0;
uint32_t enc_prev_time = 0;
uint8_t enc_need_up = 0;
uint8_t enc_need_down = 0;
uint8_t ENCODER_LED_BLINK = 8;
uint8_t END_BLINK = 1;


/* PADS ---------------------------------------------------------*/
#include "pads_color.h"
uint8_t need_load_rgb = 0;		//flag for start load rgb leds from spi			
uint32_t load_rgb_prev_tim;
uint32_t load_rgb_tim;
uint8_t PAD_0_PRESSED = 0;
uint8_t PAD_1_PRESSED = 0;
uint8_t PAD_2_PRESSED = 0;
uint8_t PAD_3_PRESSED = 0;
uint8_t PAD_4_PRESSED = 0;
uint8_t PAD_5_PRESSED = 0;
uint8_t PAD_6_PRESSED = 0;
uint8_t PAD_7_PRESSED = 0;
uint8_t ACTIVE_PAD = 0xFF;			//number of active pad 0...7 0xFF - none														
uint8_t previous_pad = 0xAA;		
uint8_t previous_play_position[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};						//position cursor or sequencer														
uint16_t previous_time_position[8] = {0};								
uint8_t pad_off_tim = 0; 					//timer for pad off, when pad - sequencer
uint8_t pad_sample_on_tim = 0; 		//timer for pad on, when pad - sample
uint32_t pad_timestamp = 0;				//time stamp for pads press timing
uint32_t GUI_STYLE_COLOR = 0;

/* ADCs and VR ---------------------------------------------------------*/			
uint8_t VR_LEVEL = 0;							
uint8_t VR_PARAMETER_1 = 0;
uint8_t VR_PARAMETER_2 = 0;														
uint32_t ADC_1_TEMP;
uint32_t ADC_2_TEMP;
uint32_t ADC_3_TEMP;
uint16_t ADC_1_center;
uint16_t ADC_2_center;
uint16_t ADC_3_center;														
#define	ADC_HYSTERESIS 	28			

/* USART DEBUG ---------------------------------------------------------*/
//#define USART_DEBUG
			
#if defined(USART_DEBUG)			
uint8_t usart_data_cnt = 0;
char U_RX_DATA[16] = {0};
uint8_t usart_new_data = 0;					//usart new data flag
uint8_t m;
uint32_t usart_timeout = 0;
char U_TX_DATA[32] = {0};	
uint16_t uart_tmp = 0;
#endif			
uint8_t need_send_sync = 0;			
uint8_t	sync_pulse[2];
uint16_t uart_bpm;

/* INTERNAL BPM ---------------------------------------------------------*/
uint32_t IBEAT_TIM = 0;						//0...599999
uint16_t IUDP_MPHASE_CNT = 0;
uint32_t THR_TIME = 0;
uint32_t time_tmp;

/* EDIT PRST variables ---------------------------------------------------------*/
uint8_t TOTAL_EP_POSITIONS = 11;			
char EP_BASE[11][8] = { "FL LIST ",
												"PRESET  ",
												"PAD 1   ",
												"PAD 2   ",
												"PAD 3   ",
												"PAD 4   ",
												"PAD 5   ",
												"PAD 6   ",
												"PAD 7   ",
												"PAD 8   ",
												"CANCEL  "};				//EP list
uint8_t CurrentEPPosition = 0;			//0....10

/* EDIT LIST variables ---------------------------------------------------------*/
uint8_t TOTAL_EL_POSITIONS = 5;			
char EL_BASE[5][17] = {	"CREATE NEW       ",
												"CREATE DUPLICATE ",
												"MOVE             ",
												"DELETE           ",
												"CANCEL           "};				//EL list
uint8_t CurrentELPosition = 0;			//0....4

/* DELETE DIALOG ---------------------------------------------------------*/
uint8_t TOTAL_DD_POSITIONS = 2;			
char DD_BASE[2][4] = {"NO  ",
											"YES "};		//DD list
uint8_t CurrentDDPosition = 0;			//0....1												

/* Display UTILITY variables ---------------------------------------------------------*/
uint8_t TOTAL_U_POSITIONS = 15;						
uint32_t UTILITY_SETTINGS[10]; 
uint8_t UTILITY_SETTINGS_MAX[10] = {63, 1, 4, 1, 0xFF, 1, 4, 0xFF, 0xFF, 0xFF}; 
char UTILITY_BASE[15][20] = {"AUTO LOAD           ",
														 "LOAD LOCK           ",
														 "EFFECT TYPE         ",
														 "SYNC MODE           ",
														 "INTERNAL BPM        ",
														 "SYNC OUT TYPE       ",
														 "LCD BRIGHTNESS      ",
														 "CDJ 1 IP ADDR.      ",
														 "CDJ 2 IP ADDR.      ",
														 "SAMPLER IP ADDR.    ",
														 "SAMPLER MAC ADDR.   ",
														 "SD CARD INFO        ",
														 "DEVICE UID          ",
														 "VERSION No.         ",
														 "DEVELOPER           "};				//UTILITY list
uint32_t DEVICE_UID = 0;
uint8_t UCurrentCursorPosition = 0;			//0...12 position
uint8_t CurrentUPosition = 1;						//1....TOTAL_UTILITY_POSITIONS-12
uint8_t edit_parameter = 0;							//flag in settings menu - entering to edit parameter										
uint8_t ip_decade = 0;									//nubmer decade for edit IP adress			
					
/* EDIT UTILITY variables ---------------------------------------------------------*/
uint8_t TOTAL_EU_POSITIONS = 4;			
char EU_BASE[4][15] = {"SET TO DEFAULT ",
											 "REBOOT         ",
									  	 "TURN OFF       ",
											 "CANCEL         "};				//EU list
uint8_t CurrentEUPosition = 0;																 

/* Display EDIT PAD_X variables ---------------------------------------------------------*/
uint8_t EPD_Position = 0;   //0...10
uint8_t TOTAL_EPD_POSITIONS = 11;						
uint8_t EPD_MAX[8] = {63, 1, 4, 1, 0xFF, 1, 4, 0xFF};
char EPD_BASE[8][9] = {"TYPE     ",
											 "QUANTIZE ",
											 "SYNC     ",
											 "TRIGGER  ",
											 "TEMPO    ",
											 "GAIN     ",
											 "BARS     ",
											 "COLOR    "};													
uint8_t edit_epd_parameter = 0;			//flag in edit pad display - entering to edit parameter														
uint8_t wzoom = 6;
uint32_t new_all_data;						//all data for sdram space in audio samples				
uint8_t previous_pad_type;				//for edit type and reload data or start analyzing waveform	
uint8_t need_analyzing_wfm = 0;		//flag for analyzing waveform
uint8_t seq_epos = 0;							//position sequencer for edit sequence 0...63
uint8_t previous_seq_epos = 0;		//previous position sequencer for edit sequence											 
											 											 
/* Display EDIT PRESET variables ---------------------------------------------------------*/									 
uint8_t EPRD_Position = 0;   //0...3
uint8_t TOTAL_EPRD_POSITIONS = 4;
uint8_t EPRD_MAX[4] = {0xFF, 7, 5, ICONS_MAX-1};												
uint8_t edit_eprd_parameter = 0;			//flag in edit preset display - entering to edit parameter		

/* KEYBOARD variables ---------------------------------------------------------*/
uint8_t rnm_buff[33];
const uint16_t letter_offs[2][37] = {	3,	17,	29,	42,	55,	68,	81,	94,	107,	120,	134,	146,	159,	174,	186,	198,	213,	222,	237,	250,	263,	276,	290,	302,	316,	328,	341,	352,	367,	380,	393,	405,	419,	434,	447,	459,	466,
																			3,	16,	29,	42,	55,	67,	80,	93,	106,	119,	132,	145,	158,	174,	186,	197,	210,	222,	236,	249,	262,	275,	288,	301,	314,	327,	340,	352,	366,	378,	393,	407,	421,	433,	447,	459,	466
																		};																
const uint8_t lttrs[2][37] = {	48,	49,	50,	51,	52,	97,	98,	99,	100,	101,	102,	103,	104,	105,	106,	107,	108,	109,	110,	111,	112,	113,	114,	115,	116,	117,	118,	119,	120,	121,	122,	43,	95,	58,	46,	40,	128,
																53,	54,	55,	56,	57,	65,	66,	67,	 68,	 69,	 70,	 71,	 72,	 73,	 74,	 75,	 76,	 77,	 78,	 79,	 80,	 81,	 82,	 83,	 84,	 85,	 86,	 87,	 88,	 89,	 90,	45,	33,	34,	44,	41,	129
																};

uint8_t KBRD_Position = 0;   //0...73															
#define KBRD_UP					0																	
#define KBRD_DOWN				1
#define KBRD_SH_UP			2																
#define KBRD_SH_DOWN		3																
uint8_t blink_cursor = 0;    //status blink			
uint32_t cursor_tim;				
							
/* BROWSER variables ---------------------------------------------------------*/
uint16_t CurrentBRPosition = 1;			//1....total_elements-12
uint8_t total_elements = 0;				//total elements (files and dirs in folder)
uint8_t BRCCP = 0;			//0...12 position
uint8_t TRACKLIST[256][66];			//TRACKLIST[x][65] = 1 folder; 0 file; TRACKLIST[x][64] = strlen folder; 
uint16_t TOTAL_TRACKS = 0;				//total tracks in folder 0 - empty folder 1...256
char path_opened[128] = {0};							// /MUSIC/loud (for example)

/* FL LIST variables ---------------------------------------------------------*/
uint8_t need_fastload_preset = 0xFF;        //flag for fast loading preset					
uint8_t edit_fl_parameter = 0;			//flag in edit pad display - entering to edit parameter
uint8_t FLCurrentCursorPosition = 0;			//0...7 position

/* Move preset variables ---------------------------------------------------------*/
uint8_t CurrentMPRSTPosition = 1;			//1....TOTAL_PRESETS-12
uint8_t MPRSTCCP = 0;			//0...12 position
uint8_t moveable_preset = 0xFF;

/* SLIDE PADS variables ---------------------------------------------------------*/
uint8_t previous_frame = 0;
uint8_t need_slide_pads = 0;
uint8_t need_reslide_pads = 0;
uint32_t start_slide_time;
uint32_t current_slide_time;
uint8_t after_fl = 0;				//flag for SwitchInformationLayer after FL display



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
																																									