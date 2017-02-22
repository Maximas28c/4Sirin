#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId sendHelloHandle;
osThreadId sendWorldHandle;
osMutexId mtxUartHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void SendHelloTask(void const * argument);
void SendWorldTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Create the mutex(es) */
	/* definition and creation of mtxUart */
	osMutexDef(mtxUart);
	mtxUartHandle = osMutexCreate(osMutex(mtxUart));

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the thread(s) */
	/* definition and creation of sendHello */
	osThreadDef(sendHello, SendHelloTask, osPriorityHigh, 0, 128);
	sendHelloHandle = osThreadCreate(osThread(sendHello), NULL);

	/* definition and creation of sendWorld */
	osThreadDef(sendWorld, SendWorldTask, osPriorityLow, 0, 128);
	sendWorldHandle = osThreadCreate(osThread(sendWorld), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */
}

/* SendHelloTask function */
void SendHelloTask(void const * argument) {

	/* USER CODE BEGIN SendHelloTask */

	osStatus lastOsStatus;
	char * s = "Hello \r\n";

	/* Infinite loop */
	for (;;) {

		lastOsStatus = osMutexWait(mtxUartHandle, osWaitForever);

		if (lastOsStatus == osOK) {
			// we took Mutex
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			HAL_UART_Transmit(&huart1, s, strlen(s), 1000);
			osDelay(1000);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			osMutexRelease(mtxUartHandle);
		}

		osDelay(1);
	}
	/* USER CODE END SendHelloTask */
}

/* SendWorldTask function */
void SendWorldTask(void const * argument) {

	/* USER CODE BEGIN SendWorldTask */

	osStatus lastOsStatus;
	char * s = "World \r\n";

	/* Infinite loop */
	for (;;) {

		lastOsStatus = osMutexWait(mtxUartHandle, osWaitForever);

		if (lastOsStatus == osOK) {
			// we took Mutex
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			HAL_UART_Transmit(&huart1, s, strlen(s), 1000);
			osDelay(731);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			osMutexRelease(mtxUartHandle);
		}

		osDelay(1);
	}
	/* USER CODE END SendWorldTask */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
