/**
  ******************************************************************************
  * @file    Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
/*void NMI_Handler(void)*/
/*{*/
/*}*/

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
/*void HardFault_Handler(void)*/
/*{*/
  /*[> Go to infinite loop when Hard Fault exception occurs <]*/
  /*while (1)*/
  /*{*/
  /*}*/
/*}*/

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
/*void MemManage_Handler(void)*/
/*{*/
  /*[> Go to infinite loop when Memory Manage exception occurs <]*/
  /*while (1)*/
  /*{*/
  /*}*/
/*}*/

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
/*void BusFault_Handler(void)*/
/*{*/
  /*[> Go to infinite loop when Bus Fault exception occurs <]*/
  /*while (1)*/
  /*{*/
  /*}*/
/*}*/

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
/*void UsageFault_Handler(void)*/
/*{*/
  /*[> Go to infinite loop when Usage Fault exception occurs <]*/
  /*while (1)*/
  /*{*/
  /*}*/
/*}*/

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
/*void SVC_Handler(void)*/
/*{*/
/*}*/

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
/*void DebugMon_Handler(void)*/
/*{*/
/*}*/

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
/*void PendSV_Handler(void)*/
/*{*/
/*}*/

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*void SysTick_Handler(void)*/
/*{*/
	/*STM_EVAL_LEDOn( LED4 );*/
/*}*/
 /*extern uint32_t iii;*/

/*
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
*/

extern uint32_t i;

void EXTI0_IRQHandler(void)
{

	if( EXTI_GetITStatus( EXTI_Line0 ) != RESET ){
		STM_EVAL_LEDToggle( LED4 );

		int j,k;
		for(j=0;j<10000;j++){
			for(k=0;k<1000;k++){}
		}

//		itoa( i, 10 );
	}
	EXTI_ClearITPendingBit( EXTI_Line0 );
}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 


/************************ (C) COPY(EXTI_Line15)IGHT STMicroelectronics *****END OF FILE****/
