/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "trace.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for task500ms */
osThreadId_t task500msHandle;
const osThreadAttr_t task500ms_attributes = {
  .name = "task500ms",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for task1000ms */
osThreadId_t task1000msHandle;
const osThreadAttr_t task1000ms_attributes = {
  .name = "task1000ms",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for stopTask */
osThreadId_t stopTaskHandle;
const osThreadAttr_t stopTask_attributes = {
  .name = "stopTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask500ms(void *argument);
void StartTask1000ms(void *argument);
void StartStopTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  MX_TRACE_Init();
  SDK_TRACE_Start();

  SDK_TRACE_Timestamp(PRINT, 1);
  SDK_TRACE_Print("%s","LEDs Blink test with FreeRTOS");
  SDK_TRACE_Timestamp(PRINT, 0);
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of task500ms */
  task500msHandle = osThreadNew(StartTask500ms, NULL, &task500ms_attributes);

  /* creation of task1000ms */
  task1000msHandle = osThreadNew(StartTask1000ms, NULL, &task1000ms_attributes);

  /* creation of stopTask */
  stopTaskHandle = osThreadNew(StartStopTask, NULL, &stopTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTask500ms */
/**
  * @brief  Function implementing the task500ms thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask500ms */
void StartTask500ms(void *argument)
{
  /* USER CODE BEGIN StartTask500ms */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
	SDK_TRACE_Timestamp(LED3, HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15));
    osDelay(500);
  }
  /* USER CODE END StartTask500ms */
}

/* USER CODE BEGIN Header_StartTask1000ms */
/**
* @brief Function implementing the task1000ms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask1000ms */
void StartTask1000ms(void *argument)
{
  /* USER CODE BEGIN StartTask1000ms */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	SDK_TRACE_Timestamp(LED1, HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13));
    osDelay(1100);
  }
  /* USER CODE END StartTask1000ms */
}

/* USER CODE BEGIN Header_StartStopTask */
/**
* @brief Function implementing the stopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStopTask */
void StartStopTask(void *argument)
{
  /* USER CODE BEGIN StartStopTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(5000);
    /* Finish led test */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    SDK_TRACE_Timestamp(LED1, HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13));
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
    SDK_TRACE_Timestamp(LED3, HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15));
    SDK_TRACE_Timestamp(PRINT, 1);
    SDK_TRACE_Print("%s","Test passed");
    SDK_TRACE_Timestamp(PRINT, 0);

    /* Example of sending debug messages */
    SDK_TRACE_Print("%s%d%s%X", "Decimal value: ", 255, " Hex value: ", 255);

    /* Example of writing dump */
    uint8_t data[4] = { 0xDE, 0xAD, 0xBE, 0xEF };
    SDK_TRACE_Dump(&data, 4);

    /* Stop system */
    SDK_TRACE_Stop();
    vTaskEndScheduler();
  }
  /* USER CODE END StartStopTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
