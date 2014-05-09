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

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Init()
{
	/*Must enable the clock of pin group G*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	/*Not sure what this clock do*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef GPIO_Structure;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_9;		/*Pin number*/
	GPIO_Structure.GPIO_Mode = GPIO_Mode_OUT;	/*Input or output*/
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;	/*Operating ouput type*/
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_UP;	/*Pull-up or Pull-down*/
	GPIO_Structure.GPIO_Speed = GPIO_Speed_2MHz;	/*Speed, not sure what this for*/
	GPIO_Init(GPIOG, &GPIO_Structure);

	/*Reset bits means to down the voltage*/
	GPIO_ResetBits(GPIOG, GPIO_Pin_9);
}

void bitTask(void* pvParameters)
{
	while (1) {
		vTaskDelay(10000);
		GPIO_ResetBits(GPIOG, GPIO_Pin_9);
		vTaskDelay(10000);
		GPIO_SetBits(GPIOG, GPIO_Pin_9);
	}
}

int main( void )
{
	Init();

	xTaskCreate(bitTask, (signed char*)"bit", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();
}


