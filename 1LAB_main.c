/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "main.h"
#include "stm32f3xx.h"

#define BIT0 0x01

int main(void)
{
	RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOE -> MODER |= GPIO_MODER_MODER15_0;
	GPIOE -> MODER &=~ GPIO_MODER_MODER15_1;

	GPIOE -> MODER |= GPIO_MODER_MODER15_0;
	GPIOE -> MODER &=~ GPIO_MODER_MODER15_1;

	GPIOA -> MODER &=~ GPIO_MODER_MODER0_0;
	GPIOA -> MODER &=~ GPIO_MODER_MODER0_1;

	GPIOE -> BSRR |= GPIO_BSRR_BS_15;

  while (1)
  {
	  if(GPIOA -> IDR & BIT0)
		  GPIOE -> BSRR |= GPIO_BSRR_BS_15;
	  else
		  GPIOE -> BSRR |= GPIO_BSRR_BR_15;
  }
}
