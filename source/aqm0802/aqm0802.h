#ifndef __AQM0802_H__
#define __AQM0802_H__

#include "st7032.h"

#define I2C_SLAVE_BUF_SIZE       6
#define I2C_SLAVE_AQM0802_ADDR   0x7c

extern void AQM0802_Config_Request(void);
extern int AQM0802_cleardisplay(void);
extern int AQM0802_setcursor(int , int);
extern int AQM0802_putc( char c );
extern int AQM0802_puts( char * );
extern int AQM0802_init( int );
extern int AQM0802_deinit(void);


#endif // __AQM0802_H__
