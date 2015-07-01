#ifndef PADDLE_DRIVER
#define PADDLE_DRIVER
#include "stm32f4xx_hal.h"

typedef enum { false, true } bool;

typedef struct pin_struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} Pinx;

typedef struct paddle_struct
{
    Pinx in;
    Pinx out;
    bool state;
} Paddle;

//Prototypes
Pinx SetPinx(GPIO_TypeDef* _port, uint16_t _pin);
Paddle SetPaddle(Pinx _in, Pinx _out, bool _initState);
GPIO_PinState DebounceRead(Pinx pinx, int sampling_count, int threshold);
void WritePinx(Pinx pinx, bool state);
    
#endif
