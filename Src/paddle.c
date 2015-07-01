#include "stm32f4xx_hal.h"
#include "paddle.h"

Pinx SetPinx(GPIO_TypeDef* _port, uint16_t _pin)
{
    Pinx _pinx;
    _pinx.pin = _pin;
    _pinx.port = _port;
    return _pinx;
}

Paddle SetPaddle(Pinx _in, Pinx _out, bool _initState)
{
    Paddle _paddle;
    _paddle.in = _in;
    _paddle.out = _out;
    _paddle.state = _initState;
    return _paddle;
}

GPIO_PinState DebounceRead(Pinx pinx, int sampling_count, int threshold)
{
    int currentState;
    for (int i = 0; i < sampling_count; ++i)
    {
        if (HAL_GPIO_ReadPin(pinx.port, pinx.pin) == GPIO_PIN_SET)
            ++currentState;
    }
    return (currentState > threshold)? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void WritePinx(Pinx pinx, bool state)
{
    HAL_GPIO_WritePin(pinx.port, pinx.pin, (state == true) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
