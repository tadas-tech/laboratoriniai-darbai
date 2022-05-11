/* USER CODE BEGIN Header */
/**
  ****************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ****************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ****************************************************************************
  */

#include "main.h"
#include "stm32f3xx.h"

#define BIT0 0x01

void SystemClock_Config(void);

void timerInit()
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1 -> CR1 |= TIM_CR1_ARPE;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1FE;

	TIM1 -> CCMR1 &=~ TIM_CCMR1_OC1M_0;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM1 -> CCMR1 &=~ TIM_CCMR1_OC1M_3;

	TIM1 -> ARR = 99;
	TIM1 -> CCR1 = 0;

	TIM1 -> BDTR |= TIM_BDTR_MOE;

	TIM1 -> CCER &=~ TIM_CCER_CC1NP;
	TIM1 -> CCER |= TIM_CCER_CC1E;

	TIM1 -> PSC |= 0x0A;
	TIM1 -> PSC |= TIM_CCMR1_IC1PSC;

	TIM1 -> CR1 |= TIM_CR1_CEN;

}

int main(void)
{
		RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;
		RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

		GPIOE -> MODER |= GPIO_MODER_MODER9_1;
		GPIOE -> MODER &=~ GPIO_MODER_MODER9_0;

		GPIOA -> MODER &=~ GPIO_MODER_MODER0_0;
		GPIOA -> MODER &=~ GPIO_MODER_MODER0_1;

		GPIOE -> BSRR |= GPIO_BSRR_BS_9;

		GPIOE -> AFR[1] |=0x20;

		timerInit(10);

		int i = 0;

	  while (1)
	  {
		  for(i; i < 100; i++)
		  {
			  TIM1 -> CCR1 = i;
			  for(int j = 0; j < 2000; j++);
		  }
		  for(i; i != 0; i--)
		  {
			  TIM1 -> CCR1 = i;
			  for(int j = 0; j < 2000; j++);
		  }
	  }
