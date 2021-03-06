/*
Example for TouchClamp Click

    Date          : Oct 2018.
    Author        : Nenad Filipovic

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.2.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C, GPIO and LOG structures, set INT pin as input.
- Application Initialization - Initialization driver enable's - I2C,
     soft reset register, set default configuration and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of TouchClamp Click board.
     TouchClamp Click communicates with MPR121 chip via I2C
     by write and read from register and get touch data.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart when the sensor is triggered.

Additional Functions :

- UART


*/

#include "Click_TouchClamp_types.h"
#include "Click_TouchClamp_config.h"


uint16_t touchData;
uint16_t touchDataOld = 0;

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_TOUCHCLAMP_I2C_CFG[0] );

    mikrobus_logInit( _MIKROBUS2, 9600 );

    Delay_100ms();
}

void applicationInit()
{
    touchclamp_i2cDriverInit( (T_TOUCHCLAMP_P)&_MIKROBUS1_GPIO, (T_TOUCHCLAMP_P)&_MIKROBUS1_I2C, _TOUCHCLAMP_I2C_ADDRESS );

    mikrobus_logWrite( "-------------------", _LOG_LINE );
    mikrobus_logWrite( " Touch Clamp Click ", _LOG_LINE );
    mikrobus_logWrite( "-------------------", _LOG_LINE );
    
    touchclamp_softReset();
    Delay_10ms();
    
    touchclamp_defaultConfiguration();
    Delay_10ms();
}

void applicationTask()
{
    touchData = touchclamp_getTouchData();
    
    if ( touchDataOld != touchData )
    {
        if ( touchData == 0x10 )
            mikrobus_logWrite( "  - - - - - - - H ", _LOG_LINE );
            
        if ( touchData == 0x01 )
            mikrobus_logWrite( "  - - - - - - G - ", _LOG_LINE );
            
        if ( touchData == 0x02 )
            mikrobus_logWrite( "  - - - - - F - - ", _LOG_LINE );
            
        if ( touchData == 0x04 )
            mikrobus_logWrite( "  - - - - E - - - ", _LOG_LINE );
            
        if ( touchData == 0x08 )
            mikrobus_logWrite( "  - - - D - - - - ", _LOG_LINE );
            
        if ( touchData == 0x20 )
            mikrobus_logWrite( "  - - C - - - - - ", _LOG_LINE );
            
        if ( touchData == 0x40 )
            mikrobus_logWrite( "  - B - - - - - - ", _LOG_LINE );
            
        if ( touchData == 0x80 )
            mikrobus_logWrite( "  A - - - - - - - ", _LOG_LINE );
      
        touchDataOld = touchData;
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}