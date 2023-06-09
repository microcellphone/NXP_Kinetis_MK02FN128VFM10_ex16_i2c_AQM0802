#include "aqm0802.h"
#include "common_string.h"
#include "my_delay.h"

#define LCD_OSC_FREQ		0x04
#define LCD_AMP_RATIO	0x02
#define CONTRAST	56

int AQM0802_cleardisplay(void)
{
	ST7032_i2c_send_command(ST7032_CLEARDISPLAY);
	SysTick_Delay(1);
	return 1;
}

int AQM0802_setcursor( int col, int row )
{
	int row_offs[] = { 0x00, 0x40, 0x14, 0x54 };
	
	ST7032_i2c_send_command(ST7032_SETDDRAMADDR | (col + row_offs[row]));
	SysTick_Delay(1);
	return 1;
}

int AQM0802_putc( char c )
{
	ST7032_i2c_send_data((uint32_t)c);
	SysTick_Delay(1);

	return 1;
}

int AQM0802_puts( char *str )
{
	uint8_t cnt;

	for(cnt = 0; cnt<common_strlen(str); cnt++){
//		ST7032_i2c_send_data((uint32_t)str[cnt]);
//		Delay(1);
		AQM0802_putc(str[cnt]);
	}
	
	return 1;
}

int AQM0802_init( int contrast )
{
	ST7032_i2c_send_command( ST7032_FUNCTIONSET | ST7032_FUNC_8BITMODE | ST7032_FUNC_2LINE );
	ST7032_i2c_send_command( ST7032_FUNCTIONSET | ST7032_FUNC_8BITMODE | ST7032_FUNC_2LINE | ST7032_FUNC_INSTABLE );
	ST7032_i2c_send_command( ST7032_IS_OSC | LCD_OSC_FREQ );
	ST7032_i2c_send_command( ST7032_IS_CONTSET1 | contrast_lower(contrast) );
	ST7032_i2c_send_command( ST7032_IS_CONTSET2 | contrast_upper(contrast) );
	ST7032_i2c_send_command( ST7032_IS_FOLLOWER | ST7032_IS_FOLLOWER_ON | LCD_AMP_RATIO );
	ST7032_i2c_send_command( ST7032_DISPLAYCONTROL | ST7032_DISP_ON );
	ST7032_i2c_send_command( ST7032_ENTRYMODESET | ST7032_ENTRYLEFT );

	AQM0802_cleardisplay();
	return 1;
}


void AQM0802_Config_Request(void)
{
	i2c_Config_Request(I2C0);
	if (AQM0802_init(CONTRAST) < 0 ) {while (1);}
}

