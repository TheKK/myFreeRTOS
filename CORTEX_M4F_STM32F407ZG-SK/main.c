/**
  ******************************************************************************
  * @file    Template/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** @addtogroup Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t demoMode;

void RCC_Configuration(void)
{
      /* --------------------------- System Clocks Configuration -----------------*/
      /* USART1 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
      /* GPIOA clock enable */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}
 
/**************************************************************************************/
 
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*-------------------------- GPIO Configuration ----------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect USART pins to AF */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);   // USART1_TX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);  // USART1_RX
}
 
/**************************************************************************************/
 
void USART1_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     *  - BaudRate = 9600 baud
     *  - Word Length = 8 Bits
     *  - One Stop Bit
     *  - No parity
     *  - Hardware flow control disabled (RTS and CTS signals)
     *  - Receive and transmit enabled
     */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void USART1_puts(char* s)
{
    while(*s) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, *s);
        s++;
    }
}

void itoa(uint32_t n, uint32_t base)                                                                                                                                                          {
	volatile portCHAR buf[33] = {0};
	volatile portCHAR *p = &buf[32];

	if (n == 0)
		*--p = '0';
	else {
		portCHAR *q;
		volatile uint32_t num = n;

		*--p = '\r';
		*--p = '\n';

		for (; num; num/=base)
			*--p = "0123456789ABCDEF" [num % base];
	}

	USART1_puts( p );
}


/**************************************************************************************/
volatile uint32_t* i = 0;

void add (uint8_t mode)
{
	static uint32_t num = 0;

		if(mode == 1)
			num = num + 1;
		else{
			itoa( num, 10 );
			num = 0;
		}

}

static void main1( void *pvParameters )
{
		while( 1 ){
		add( 1 );
		add( 0 );
		}
}

static void main2( void *pvParameters )
{

	while( 1 ){
		vTaskDelay( 1000 );


		STM_EVAL_LEDToggle( LED4 );
		add( 1 );
		add( 0 );

	}
}

static void main3( void *pvParameters )
{
		vTaskDelay( 60000 );

		STM_EVAL_LEDToggle( LED3 );
		while( 1 ){

		}
}

static void main4( void *pvParameters )
{
	while( 1 ){
	}
}


/*int main (void)*/
/*{*/
    /*RCC_Configuration();*/
    /*GPIO_Configuration();*/
    /*USART1_Configuration();*/

    /*STM_EVAL_PBInit( BUTTON_USER );*/
    /*STM_EVAL_LEDInit( LED3 );*/
    /*STM_EVAL_LEDInit( LED4 );*/
    /*SysTick_Config( configCPU_CLOCK_HZ/1000 );*/

	/*xTaskCreate( main1, (signed char*) "main1", 128, NULL, tskIDLE_PRIORITY + 1, NULL );*/
	/*xTaskCreate( main2, (signed char*) "main2", 128, NULL, tskIDLE_PRIORITY + 2, NULL );*/
	/*xTaskCreate( main3, (signed char*) "main3", 128, NULL, tskIDLE_PRIORITY + 3, NULL );*/
	/*vTaskStartScheduler();*/
/*}*/

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

EXTI_InitTypeDef   EXTI_InitStructure;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
__IO uint32_t TimingDelay;
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void EXTILine0_Config(void);
static void EXTILine13_Config(void);         

int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured, 
	 *   this is done through SystemInit() function which is called from startup
	 *     files (startup_stm32f429_439xx.s) before to branch to application main. 
	 *       To reconfigure the default setting of SystemInit() function, refer to
	 *         system_stm32f4xx.c file
	 *           */ 

	RCC_ClocksTypeDef RCC_Clocks;
	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	/* Initialize LEDs mounted on EVAL board */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);

	/* Put LED3 on */
	STM_EVAL_LEDOn(LED3);

	/* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
	EXTILine0_Config();

	/* Configure EXTI Line13 (connected to PC13 pin) in interrupt mode */
	EXTILine13_Config();

	STM_EVAL_PBInit( BUTTON_USER, BUTTON_MODE_GPIO );

	while (1)
	{
		/* Generate software interrupt: simulate a falling edge applied on EXTI0 line */
		if( STM_EVAL_PBGetState( BUTTON_USER ) ){
			EXTI_GenerateSWInterrupt(EXTI_Line13);
			while( STM_EVAL_PBGetState( BUTTON_USER ) );
		}

		/*Delay(500);*/
	}
}
static void EXTILine0_Config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable GPIOA clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
static void EXTILine13_Config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable GPIOC clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PC13 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Connect EXTI Line15 to PC13 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	/* Configure EXTI Line13 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI15_10 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

/**
 *   * @brief  Inserts a delay time.
 *     * @param  nTime: specifies the delay time length, in 10 ms.
 *       * @retval None
 *         */
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;

	while(TimingDelay != 0);
}
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

#ifdef  USE_FULL_ASSERT

/**
 *   * @brief  Reports the name of the source file and the source line number
 *     *         where the assert_param error has occurred.
 *       * @param  file: pointer to the source file name
 *         * @param  line: assert_param error line source number
 *           * @retval None
 *             */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 *      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

