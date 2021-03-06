/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/20/2009
  * @brief   Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_eth.h"
#include "main.h"
#include "ethernetif.h"
#include "netconfig.h"
#include "lwip/tcp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f107.h"
#include "TCP_CLIENT.h"
#include "mqtt_client.h"
#include "tcpip.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

TaskHandle_t led1_tsk_handle;
TaskHandle_t led2_tsk_handle;
TaskHandle_t check_tsk_handle;
void led1_task(void){

	while(1){
//		GPIO_ResetBits(GPIOC,GPIO_Pin_8);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
//		 vTaskDelay(100);
//	GPIO_SetBits(GPIOC,GPIO_Pin_7);
//	GPIO_SetBits(GPIOC,GPIO_Pin_8);
		//printf("11111/n");
		// vTaskDelay(100);
	}
}
void led2_task(void){

	while(1){
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
		 vTaskDelay(100);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
		 vTaskDelay(100);
	}
}
void check_tcp_server_connection(void){
	while(1){
		Check_TCP_Connect();
		vTaskDelay(100);
	}
}


int main(void)
{

  	System_Setup();
		LWIP_INIT();

	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
//	 xTaskCreate((TaskFunction_t)led1_task,
//							(const char*)		"startled1",
//							(uint16_t)			50,
//							(void*)					NULL,
//							(UBaseType_t)   2,
//							(TaskHandle_t*) &led1_tsk_handle);
							
//		 xTaskCreate((TaskFunction_t)led2_task,
//							(const char*)		"startled2",
//							(uint16_t)			50,
//							(void*)					NULL,
//							(UBaseType_t)   3,
//							(TaskHandle_t*) &led2_tsk_handle);

	#if LWIP_DHCP
	 create_dhcp_task();
		#else			
		TCP_Client_Init(TCP_LOCAL_PORT,TCP_SERVER_PORT,TCP_SERVER_IP); 
		start_mqtt(MQTT_SERVER_IP);		
	#endif
			 xTaskCreate((TaskFunction_t)check_tcp_server_connection,
							(const char*)		"check_connection",
							(uint16_t)			50,
							(void*)					NULL,
							(UBaseType_t)   3,
							(TaskHandle_t*) &check_tsk_handle);

	vTaskStartScheduler();  
   while(1){
	 }
}
