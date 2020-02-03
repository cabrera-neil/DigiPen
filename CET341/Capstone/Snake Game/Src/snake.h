/*****************************************************************************
 @Project	: 
 @File 		: snake.h
 @Details  	:
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>

/*****************************************************************************
 Define
******************************************************************************/
#define SNAKE_GAME_TITLE	"Snake Game V1.0"

//Colors
#define ILI9341_COLOR_WHITE     0xFFFFFF
#define ILI9341_COLOR_BLACK	0x000000
#define ILI9341_COLOR_RED	0x0000FF
#define ILI9341_COLOR_GREEN	0x00FF00
#define ILI9341_COLOR_GREEN2	0x00FF00
#define ILI9341_COLOR_BLUE	0xFF0000
#define ILI9341_COLOR_BLUE2	0xFF0000
#define ILI9341_COLOR_YELLOW	0x00FFFF
#define ILI9341_COLOR_ORANGE	0x00A5FF
#define ILI9341_COLOR_CYAN	0xFFFF00
#define ILI9341_COLOR_MAGENTA	0xFF00FF
#define ILI9341_COLOR_GRAY	0x808080
#define ILI9341_COLOR_BROWN	0x2A2AA5
	
/* Colors for game */
#define SNAKE_COLOR_BORDER	ILI9341_COLOR_BLACK
#define SNAKE_COLOR_MAIN_BCK	ILI9341_COLOR_WHITE
#define SNAKE_COLOR_GAME_BCK	ILI9341_COLOR_GREEN
#define SNAKE_COLOR_PIXEL	ILI9341_COLOR_GRAY
#define SNAKE_COLOR_TARGET	ILI9341_COLOR_ORANGE
#define SNAKE_COLOR_HEAD	ILI9341_COLOR_RED

/* Number of NxN dimension for snake */
#define SNAKE_PIXELS		26
#define SNAKE_PIXELS_Y		19
#define SNAKE_PIXEL_SIZE	5	/* number for display's pixels for 1 snake section */
#define SNAKE_BACK_START_X	1	/* X coordinate where snake area starts */
#define SNAKE_BACK_START_Y	10	/* Y coordinate where snake area starts */

#define SNAKE_DEFAULT_LENGTH	8	/* Default snake length */

#define SNAKE_SPEED_MAX		15	/* 15Hz movement */
#define SNAKE_SPEED_MIN		1	/* 1Hz movement */
#define SNAKE_SPEED_DEFAULT	100	/* Default speed in Hz */

/* Directions for snake */
#define SNAKE_DIRECTION_LEFT    4
#define SNAKE_DIRECTION_RIGHT   2
#define SNAKE_DIRECTION_UP	3
#define SNAKE_DIRECTION_DOWN    0

/* Keyboard buttons */
#define SNAKE_KEY_LEFT		4
#define SNAKE_KEY_RIGHT		2
#define SNAKE_KEY_UP		3
#define SNAKE_KEY_DOWN		0

/* Text locations */
#define SNAKE_TEXT_LINE1	265		
#define SNAKE_TEXT_LINE2	285
#define SNAKE_TEXT_LINE3	305

typedef struct {
	int8_t Snake[SNAKE_PIXELS * SNAKE_PIXELS][2];
	uint16_t Length;
	uint16_t LastIndex;
	uint8_t Direction;
	uint16_t Hits;
} SNAKE_t;

typedef struct {
	uint8_t Overflow;
	uint8_t Speed;
	uint32_t Micros;
	uint8_t Pause;
} SNAKE_Settings_t;

typedef enum {
	USB_HIDHOST_Button_Pressed = 0,
	USB_HIDHOST_Button_Released
} USB_HIDHOST_Button_t;

typedef struct {
	USB_HIDHOST_Button_t ButtonStatus;
	uint8_t Button;
} USB_HIDHOST_Keyboard_t;

typedef enum {
	USB_HIDHOST_Result_Error,
	USB_HIDHOST_Result_KeyboardConnected,
	USB_HIDHOST_Result_MouseConnected,
	USB_HIDHOST_Result_Disconnected,
	USB_HIDHOST_Result_DeviceNotSupported,
	USB_HIDHOST_Result_LibraryNotInitialized
} USB_HIDHOST_Result_t;

/*****************************************************************************
 Functions
******************************************************************************/
extern void RNG_Init(void);
extern uint32_t RNG_Get(void);


