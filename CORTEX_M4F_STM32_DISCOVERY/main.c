#include "main.h"
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EXTI_InitTypeDef   EXTI_InitStructure;

void USART(void){
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

void USART1_puts(char* s){
	while(*s) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, *s);
		s++;
	}
}

void itoa(long n, long base) {
	volatile portCHAR buf[33] = {0};
	volatile portCHAR *p = &buf[32];

	if (n == 0){
		*--p = '\r';
		*--p = '\n';
		*--p = '0';
	}
	else {
		portCHAR *q;
		unsigned long num = (base == 10 && n < 0) ? -n : n;
		*--p = '\r';
		*--p = '\n';
		for (; num; num/=base)
			*--p = "0123456789ABCDEF" [num % base];

		if (base == 10 && n < 0)
			*--p = '-';
	}

	USART1_puts( p );
}

void Init(){
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);

	USART();
}


/*-------------------------- Task ----------------------------*/

SemaphoreHandle_t xMutex = NULL;
long i = 30;

void Task1( void* pvParameters ){
	if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE ){
		while( 1 ){
			i++;
			itoa(i, 10);

			vTaskDelay(100000);
		}
	}
}

void Task2( void* pvParameters ){
	while( 1 ){
		if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE ){

			i--;
			itoa(i, 10);

			xSemaphoreGive( xMutex );
		}

		vTaskDelay(100000);
	}
}

int main( void ){
	Init();
	xMutex = xSemaphoreCreateMutex();

	xTaskCreate( Task1, (signed char*)"Task1", 128, NULL, tskIDLE_PRIORITY+1, NULL );
	xTaskCreate( Task2, (signed char*)"Task2", 128, NULL, tskIDLE_PRIORITY+2, NULL );

	vTaskStartScheduler();
}


