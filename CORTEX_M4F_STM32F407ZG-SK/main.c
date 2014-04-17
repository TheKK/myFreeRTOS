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
#include "queue.h"
/** @addtogroup Template
  * @{
  */ 

/*extern uint32_t iii;*/
EXTI_InitTypeDef   EXTI_InitStructure;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

xQueueHandle MsgQueue;
uint32_t iii = 0;

void USART1_puts(char* s)
{
	while(*s) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, *s);
		s++;
	}
}

void itoa(uint32_t n, uint32_t base) {
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

void Init()
{
	/*STM_EVAL_PBInit( BUTTON_USER, BUTTON_MODE_GPIO );*/
	RCC_ClocksTypeDef RCC_Clocks;
	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000); 

	/* Initialize LEDs mounted on EVAL board */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);

	/* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
	EXTILine0_Config();
}

void EXTILine0_Config(void)
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0xFF;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0xFF;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART(void)
{
	/* USART1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

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

	USART_InitTypeDef USART_InitStructure;

	/* USARTx configuration ------------------------------------------------------*/
	/* USARTx configured as follow:
	 *      *  - BaudRate = 9600 baud
	 *           *  - Word Length = 8 Bits
	 *                *  - One Stop Bit
	 *                     *  - No parity
	 *                          *  - Hardware flow control disabled (RTS and CTS signals)
	 *                               *  - Receive and transmit enabled
	 *                                    */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

}






void Task1( void* pvParameters )
{
	while( 1 ){
		iii++;
		while( STM_EVAL_PBGetState( BUTTON_USER ) ){
			iii++;
			STM_EVAL_LEDOn(LED4);
		}
	}
}


void Task2( void* pvParameters )
{
	while( 1 ){
		vTaskDelay( 1000 );
		itoa(iii, 10);
		iii = 0;
	}
}

void Task3( void* pvParameters )
{
	vTaskDelay( 300000 );
	while(1){
		itoa(iii, 10);
		iii = 100;
		itoa(iii, 10);
		while(1){}
	}
}





void QTask1( void* pvParameters )
{
	uint32_t snd = 100;

	while( 1 ){
		xQueueSend( MsgQueue, ( uint32_t* )&snd, 0 );  
		vTaskDelay(1000);
	}
}

void QTask2( void* pvParameters )
{
	uint32_t rcv = 0;
	while( 1 ){
		if( xQueueReceive( MsgQueue, &rcv, 100/portTICK_RATE_MS ) == pdPASS  &&  rcv == 100)
		{  
			STM_EVAL_LEDToggle( LED3 );
		}
	}
}


int
main( void )
{
	Init();
	EXTILine0_Config();
	USART();

	MsgQueue = xQueueCreate( 5 , sizeof( uint32_t ) ); 

//	xTaskCreate( Task1, (signed char*)"Task1", 128, NULL, tskIDLE_PRIORITY+1, NULL );
//	xTaskCreate( Task2, (signed char*)"Task2", 128, NULL, tskIDLE_PRIORITY+2, NULL );
//	xTaskCreate( Task3, (signed char*)"Task3", 128, NULL, tskIDLE_PRIORITY+3, NULL );
	xTaskCreate( QTask1, (signed char*)"Task1", 128, NULL, tskIDLE_PRIORITY+1, NULL );
	xTaskCreate( QTask2, (signed char*)"Task2", 128, NULL, tskIDLE_PRIORITY+1, NULL );

	vTaskStartScheduler();
}


