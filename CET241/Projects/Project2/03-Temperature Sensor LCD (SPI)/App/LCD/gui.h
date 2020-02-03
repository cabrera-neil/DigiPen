/*****************************************************************************
 @Project	: 
 @File 		: gui.h
 @Details : 
 @Author	: 
 @Hardware: Generic
   
******************************************************************************/

#include <stdint.h>
typedef int BOOL;

#ifndef __GUI_DOT_H__
#define __GUI_DOT_H__


/*****************************************************************************
 Define
******************************************************************************/
#define B_BITS 					5U
#define G_BITS 					6U
#define R_BITS 					5U

#define R_MASK 					((1 << R_BITS) -1)
#define G_MASK 					((1 << G_BITS) -1)
#define B_MASK 					((1 << B_BITS) -1)

#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8)   |  \
                                ((((c) & 0x0000fc00) >> 5) ) | 	\
                                ((((c) & 0x000000f8) >>3 ) ))

/* Color code */
#define ClrAliceBlue            0x00F0F8FF
#define ClrAntiqueWhite         0x00FAEBD7
#define ClrAqua                 0x0000FFFF
#define ClrAquamarine           0x007FFFD4
#define ClrAzure                0x00F0FFFF
#define ClrBeige                0x00F5F5DC
#define ClrBisque               0x00FFE4C4
#define ClrBlack                0x00000000
#define ClrBlanchedAlmond       0x00FFEBCD
#define ClrBlue                 0x000000FF
#define ClrBlueViolet           0x008A2BE2
#define ClrBrown                0x00A52A2A
#define ClrBurlyWood            0x00DEB887
#define ClrCadetBlue            0x005F9EA0
#define ClrChartreuse           0x007FFF00
#define ClrChocolate            0x00D2691E
#define ClrCoral                0x00FF7F50
#define ClrCornflowerBlue       0x006495ED
#define ClrCornsilk             0x00FFF8DC
#define ClrCrimson              0x00DC143C
#define ClrCyan                 0x0000FFFF
#define ClrDarkBlue             0x0000008B
#define ClrDarkCyan             0x00008B8B
#define ClrDarkGoldenrod        0x00B8860B
#define ClrDarkGray             0x00A9A9A9
#define ClrDarkGreen            0x00006400
#define ClrDarkKhaki            0x00BDB76B
#define ClrDarkMagenta          0x008B008B
#define ClrDarkOliveGreen       0x00556B2F
#define ClrDarkOrange           0x00FF8C00
#define ClrDarkOrchid           0x009932CC
#define ClrDarkRed              0x008B0000
#define ClrDarkSalmon           0x00E9967A
#define ClrDarkSeaGreen         0x008FBC8F
#define ClrDarkSlateBlue        0x00483D8B
#define ClrDarkSlateGray        0x002F4F4F
#define ClrDarkTurquoise        0x0000CED1
#define ClrDarkViolet           0x009400D3
#define ClrDeepPink             0x00FF1493
#define ClrDeepSkyBlue          0x0000BFFF
#define ClrDimGray              0x00696969
#define ClrDodgerBlue           0x001E90FF
#define ClrFireBrick            0x00B22222
#define ClrFloralWhite          0x00FFFAF0
#define ClrForestGreen          0x00228B22
#define ClrFuchsia              0x00FF00FF
#define ClrGainsboro            0x00DCDCDC
#define ClrGhostWhite           0x00F8F8FF
#define ClrGold                 0x00FFD700
#define ClrGoldenrod            0x00DAA520
#define ClrGray                 0x00808080
#define ClrGreen                0x00008000
#define ClrGreenYellow          0x00ADFF2F
#define ClrHoneydew             0x00F0FFF0
#define ClrHotPink              0x00FF69B4
#define ClrIndianRed            0x00CD5C5C
#define ClrIndigo               0x004B0082
#define ClrIvory                0x00FFFFF0
#define ClrKhaki                0x00F0E68C
#define ClrLavender             0x00E6E6FA
#define ClrLavenderBlush        0x00FFF0F5
#define ClrLawnGreen            0x007CFC00
#define ClrLemonChiffon         0x00FFFACD
#define ClrLightBlue            0x00ADD8E6
#define ClrLightCoral           0x00F08080
#define ClrLightCyan            0x00E0FFFF
#define ClrLightGoldenrodYellow 0x00FAFAD2
#define ClrLightGreen           0x0090EE90
#define ClrLightGrey            0x00D3D3D3
#define ClrLightPink            0x00FFB6C1
#define ClrLightSalmon          0x00FFA07A
#define ClrLightSeaGreen        0x0020B2AA
#define ClrLightSkyBlue         0x0087CEFA
#define ClrLightSlateGray       0x00778899
#define ClrLightSteelBlue       0x00B0C4DE
#define ClrLightYellow          0x00FFFFE0
#define ClrLime                 0x0000FF00
#define ClrLimeGreen            0x0032CD32
#define ClrLinen                0x00FAF0E6
#define ClrMagenta              0x00FF00FF
#define ClrMaroon               0x00800000
#define ClrMediumAquamarine     0x0066CDAA
#define ClrMediumBlue           0x000000CD
#define ClrMediumOrchid         0x00BA55D3
#define ClrMediumPurple         0x009370DB
#define ClrMediumSeaGreen       0x003CB371
#define ClrMediumSlateBlue      0x007B68EE
#define ClrMediumSpringGreen    0x0000FA9A
#define ClrMediumTurquoise      0x0048D1CC
#define ClrMediumVioletRed      0x00C71585
#define ClrMidnightBlue         0x00191970
#define ClrMintCream            0x00F5FFFA
#define ClrMistyRose            0x00FFE4E1
#define ClrMoccasin             0x00FFE4B5
#define ClrNavajoWhite          0x00FFDEAD
#define ClrNavy                 0x00000080
#define ClrOldLace              0x00FDF5E6
#define ClrOlive                0x00808000
#define ClrOliveDrab            0x006B8E23
#define ClrOrange               0x00FFA500
#define ClrOrangeRed            0x00FF4500
#define ClrOrchid               0x00DA70D6
#define ClrPaleGoldenrod        0x00EEE8AA
#define ClrPaleGreen            0x0098FB98
#define ClrPaleTurquoise        0x00AFEEEE
#define ClrPaleVioletRed        0x00DB7093
#define ClrPapayaWhip           0x00FFEFD5
#define ClrPeachPuff            0x00FFDAB9
#define ClrPeru                 0x00CD853F
#define ClrPink                 0x00FFC0CB
#define ClrPlum                 0x00DDA0DD
#define ClrPowderBlue           0x00B0E0E6
#define ClrPurple               0x00800080
#define ClrRed                  0x00FF0000
#define ClrRosyBrown            0x00BC8F8F
#define ClrRoyalBlue            0x004169E1
#define ClrSaddleBrown          0x008B4513
#define ClrSalmon               0x00FA8072
#define ClrSandyBrown           0x00F4A460
#define ClrSeaGreen             0x002E8B57
#define ClrSeashell             0x00FFF5EE
#define ClrSienna               0x00A0522D
#define ClrSilver               0x00C0C0C0
#define ClrSkyBlue              0x0087CEEB
#define ClrSlateBlue            0x006A5ACD
#define ClrSlateGray            0x00708090
#define ClrSnow                 0x00FFFAFA
#define ClrSpringGreen          0x0000FF7F
#define ClrSteelBlue            0x004682B4
#define ClrTan                  0x00D2B48C
#define ClrTeal                 0x00008080
#define ClrThistle              0x00D8BFD8
#define ClrTomato               0x00FF6347
#define ClrTurquoise            0x0040E0D0
#define ClrViolet               0x00EE82EE
#define ClrWheat                0x00F5DEB3
#define ClrWhite                0x00FFFFFF
#define ClrWhiteSmoke           0x00F5F5F5
#define ClrYellow               0x00FFFF00
#define ClrYellowGreen          0x009ACD32
		 

#define FONT_FMT_UNCOMPRESSED   0x00
#define FONT_FMT_PIXEL_RLE      0x01


/*****************************************************************************
 Type definition
******************************************************************************/
typedef uint16_t          GUI_DATA;		/* Support 16bits per pixel */

typedef void GUI_CB_FRAME_END( void );

 typedef struct s_tagRect				/* Window in rectangle at any moment */
 {
	 int H1;
	 int H2;
	 int V1;
	 int V2;
 }GUI_RECT, *PGUI_RECT;
 
 
typedef struct _tagGUI_Font
{
    /*! The format of the font.  Can be one of FONT_FMT_UNCOMPRESSED or
    ! FONT_FMT_PIXEL_RLE. */
    unsigned char ucFormat;

    /*! The maximum width of a character; this is the width of the widest
    ! character in the font, though any individual character may be narrower
    ! than this width. */
    unsigned char ucMaxWidth;

    //! The height of the character cell; this may be taller than the font data
    //! for the characters (to provide inter-line spacing).
    unsigned char ucHeight;


    //! The offset between the top of the character cell and the baseline of
    //! the glyph.  The baseline is the bottom row of a capital letter, below
    //! which only the descenders of the lower case letters occur.
    unsigned char ucBaseline;

    //! The offset within pucData to the data for each character in the font.
    unsigned short pusOffset[96];

    //! A pointer to the data for the font.
    const unsigned char *pucData;
}GUI_FONT, *PGUI_FONT;
 
#pragma pack( push, 1)
typedef struct _tagGUI_Bmp_Header
 {
	 uint16_t Signiture;
	 uint32_t nFileSize;
	 uint16_t Reserved1;
	 uint16_t Reserved2;	
	 uint32_t nOffset;	  
	 uint32_t nDIBSize;	 
	 int32_t nWidth;		 	 
	 int32_t nHeight;
 	 uint16_t nPlane;
 	 uint16_t nDepth;		 
	 uint32_t nOffsenCompress;	
	 uint32_t nImageSize;
 }GUI_BMP_HEADER, *PGUI_BMP_HEADER;
#pragma pack(pop)


typedef struct s_tagGUI_MemDev
{
	GUI_RECT		MemRect;
	GUI_RECT		CurRect;
	int         	nCurMemPixelCnt;
	int				nHozStart;
	int         	nHozStep;
	int				nBytePerBlock;
	int				nCurBlock;
	GUI_DATA       	*pBuf;
	int        		nNum;
	int				nSize;
	int				nMaxPhyX;
	int				nMaxPhyY;
	int				nTotalPhyPixels;

	uint8_t        bPaintWait 		:1;
	uint8_t        bFrameStart 		:1;
	uint8_t        bTextBackGround 	:1;
	uint8_t        RSVD 			:5;	
}GUI_MEMDEV, *PGUI_MEMDEV;


/******************************************************************************
 Fonts - List of selectable fonts Please use DP_FontGen.exe to generate more
******************************************************************************/
extern const GUI_FONT g_sFontCalibri10;
extern const GUI_FONT g_sFontCalibri24;

/******************************************************************************
 Global functions
******************************************************************************/


/******************************************************************************
 @Description 	: Intialization of GUI libary.  This is hardware independent.
									User need to intializes all LCD pins and Peripherals interface 
									at Hal.c

 @param			: pHandle  - Mempty handle from user. User are not allow to access
				             this handle. 
				  nMaxPhyX - Physical LCD Horizontal size in pixel
				  nMaxPhyY - Physical LCD Vertical size in pixel
				  pBuf     - Array to store pixels before send to LCD
				  nSize	   - arrary size in byte. Suggested to use 'sizeof()'

 @revision		: 1.0.0
 
******************************************************************************/
void GUI_Init(
		GUI_MEMDEV 	*pHandle,
		int 		nMaxPhyX,
		int 		nMaxPhyY,
		GUI_DATA 	*pBuf,
		int 		nSize );


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_AddCbFrameEnd( GUI_CB_FRAME_END *pFramEnd );
		

/******************************************************************************
 @Description 	: Transfer memory pixel in 16bits. User responsible to ensure 
				  that its interface support 16 per pixel transfer

 @param			: bEn - TRUE/FALSE - Enable/Disable
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_16BitPerPixel( BOOL bEn );
		

/******************************************************************************
 @Description 	: Transfer memory pixel data to LCD base on buffer size. It will 
				  callback to GUI_AppDraw() several time without waiting until
				  1 frame of LCD is painted. consume less time.

 @param			: None. But GUI_AppDraw() callback need to be prepared for 
				  this function
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_Draw_Exe( void );


/******************************************************************************
 @Description 	: Transfer memory pixel data to LCD base on buffer size. It will 
				  callback to GUI_AppDraw() several time and waiting until
				  1 frame of LCD is painted. consume more time but LCD is 
				  painted in oneshot

 @param			: None. But GUI_AppDraw() callback need to be prepared for 
				  this function
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawEx_Exe( void );


/******************************************************************************
 @Description 	: Callback for LCD painting. This function is to display user
				  Graphics

 @param			: bFrameStart - This flag indicate that when you can update your
								dynamic data. If data if updated before previous
								frame is complelely patined, a corrupted display 
								might observed withiin a short period
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_AppDraw( BOOL bFrameStart );


/******************************************************************************
 @Description 	: To clear the LCD to a specified color

 @param			: Color - color code such as ClrBlue
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_Clear( uint32_t Color );


/******************************************************************************
 @Description 	: Set color for geometry drawing

 @param			: Color - color code such as ClrBlue
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_SetColor( uint32_t Color );


/******************************************************************************
 @Description 	: Set pen line width for geometry drawing

 @param			: minimum is 1
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_SetPenWidth( int nWidth );


/******************************************************************************
 @Description 	: Draw a line

 @param			: Color - color code such as ClrBlue
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawLine(
        int x0,
        int y0,
        int x1,
        int y1 );


/******************************************************************************
 @Description 	: Draw a circle with its location, radius and color

 @param			: nPosX - Horizontal position in pixel
				  nPosY - Vertical position in pixel
				  nRadius - Radius in pixel
				  Color - color code
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawCircle( int nPosX, int nPosY, int nRadius, BOOL bFill ) ;



/******************************************************************************
 @Description 	: Draw a rectangle with its location, radius and color

 @param			: Left - Left position in pixel
				  Top - Top position in pixel
				  Right - Right position in pixel
				  Bottom - Bottom position in pixel
				  Color - color code
 @revision		: 1.0.0
 
******************************************************************************/
void
GUI_DrawRect(
    int 		Left,
    int 		Top,
    int 		Right,
    int 		Bottom );

/******************************************************************************
 @Description 	: Draw a Filled rectangle with its location, radius and color

 @param			: Left - Left position in pixel
				  Top - Top position in pixel
				  Right - Right position in pixel
				  Bottom - Bottom position in pixel
				  Color - color code
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawFilledRect(
			int 		Left,
			int 		Top,
			int 		Right,
			int 		Bottom );


/******************************************************************************
 @Description 	: Select Font from available font

 @param			: pFont - point to avaialble font. such as GUI_CONSOLE10_FONT
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_SetFont( const GUI_FONT *pFont );


/******************************************************************************
 @Description 	: Select font background color

 @param			: Color - color code
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_SetFontBackColor( uint32_t Color );


/******************************************************************************
 @Description 	: Print a charactor on screen with postion and color. Use 
				  "GUI_SetFontBackColor()" to set your font background color

 @param			: Charactor - ascii to print
				  Color - Color code
				  nPosX - Horizontal position in pixel
				  nPosY - Vertical position in pixel
				  
 @revision		: 1.0.0
 
******************************************************************************/
uint8_t GUI_PrintChar(
			char 		Charactor,
			uint32_t 	Color,
			int 		nPosX,
			int		 	nPosY );


/******************************************************************************
 @Description 	: Print a string on LCD with location and specified color

 @param			: pStr - string to print
				  Color - Color code
				  nPosX - Horizontal position in pixel
				  nPosY - Vertical position in pixel
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_PrintString(
			void const 	*pStr,
			uint32_t 	Color,
			int 		nPosX,
			int 		nPosY );


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawBitmap( void const *pBmp, int nPosX, int nPosY );
			
	
/******************************************************************************
 @Description 	: This function is using FF Chan system to access SD card to display
				  Bitmap. Only bitmap with 160x128 or less supported

			@param			: pPath - File path on Sd card.eg. "0://A.bmp"
 
 @revision		: 1.0.0
 
******************************************************************************/			
#ifdef __FF_EN
void GUI_DrawBitmapFile( char *pPath, int nPosX, int nPosY );
#endif
			
/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawVertLine( int nX, int Top, int Bottom );


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void GUI_DrawHortLine( int nY, int Left, int Right );


#endif /* __GUI_DOT_H__ */
















































