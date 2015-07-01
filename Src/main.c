#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "paddle.h"

#define SHIFT_TIME_MS 1000
//WARNING: Don't set sampling count more than 30000, integer overflow.
#define DEBOUNCE_SAMPLING_N 500
#define DEBOUNCE_THRESHOLD 400

void SystemClock_Config(void);
void InitButton(void);
void InitLed(void);
GPIO_PinState ReadPinD(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    InitLed();
    InitButton();

    //Initialization done separately
    //TODO: Add Clock and GPIO_Init to structure definitions
    Pinx Out_Pin_1 = SetPinx(GPIOD, GPIO_PIN_12);
    Pinx Out_Pin_2 = SetPinx(GPIOD, GPIO_PIN_13);
    Pinx In_Pin_1 = SetPinx(GPIOC, GPIO_PIN_2);
    Pinx In_Pin_2 = SetPinx(GPIOC, GPIO_PIN_3);

    Paddle paddle_1 = SetPaddle(In_Pin_1, Out_Pin_1, false);
    Paddle paddle_2 = SetPaddle(In_Pin_2, Out_Pin_2, false);

    while (1)
    {
        if ((DebounceRead(paddle_1.in,DEBOUNCE_SAMPLING_N,DEBOUNCE_THRESHOLD) == GPIO_PIN_SET) && (paddle_1.state == false))	
        {	
            WritePinx(paddle_1.out,true);
            paddle_1.state = true;
            HAL_Delay(SHIFT_TIME_MS);
            WritePinx(paddle_1.out,false);
        }
        else if (DebounceRead(paddle_1.in,DEBOUNCE_SAMPLING_N,DEBOUNCE_THRESHOLD) == GPIO_PIN_SET)
        {
            paddle_1.state = false;
        }
            
        if ((DebounceRead(paddle_2.in,DEBOUNCE_SAMPLING_N,DEBOUNCE_THRESHOLD) == GPIO_PIN_SET) && (paddle_2.state == false))	
        {	
            WritePinx(paddle_2.out,true);
            paddle_2.state = true;
            HAL_Delay(SHIFT_TIME_MS);
            WritePinx(paddle_2.out,false);
        }
        else if (DebounceRead(paddle_2.in,DEBOUNCE_SAMPLING_N,DEBOUNCE_THRESHOLD) == GPIO_PIN_SET)
        {
            paddle_2.state = false;
        }
    }
}


void InitLed(void)
{
    __GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef g;
    g.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    g.Speed = GPIO_SPEED_HIGH;
    g.Pull = GPIO_NOPULL;
    g.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOD,&g);
}


void InitButton(void)
{
    __GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef g;
    g.Pin = GPIO_PIN_2|GPIO_PIN_3;
    g.Speed = GPIO_SPEED_HIGH;
    g.Pull = GPIO_NOPULL;
    g.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOC,&g);
}



/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
