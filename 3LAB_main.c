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
  SET   |=
  RESET &=~
  */

#include "main.h"
#include "stm32f3xx.h"

#define BIT0 0x01

#define OFF 0
#define ON 1

#define wait 10750
#define prescaler 7200

void init_tim4(void)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4 -> PSC = prescaler;
	TIM4 -> ARR = 0xFFFF;
	TIM4 -> CR1 |= TIM_CR1_CEN;
}

void delay(int t)
{
	TIM4 -> CNT = 0;
	while(TIM4 -> CNT < t){;}
}

void IN1(int a)
{
	if(a == OFF)
		GPIOA -> BSRR |= GPIO_BSRR_BR_1;
	else if(a == ON)
		GPIOA -> BSRR |= GPIO_BSRR_BS_1;
}

void IN2(int a)
{
	if(a == OFF)
		GPIOA -> BSRR |= GPIO_BSRR_BR_2;
	else if(a == ON)
		GPIOA -> BSRR |= GPIO_BSRR_BS_2;
}

void IN3(int a)
{
	if(a == OFF)
		GPIOA -> BSRR |= GPIO_BSRR_BR_3;
	else if(a == ON)
		GPIOA -> BSRR |= GPIO_BSRR_BS_3;
}

void IN4(int a)
{
	if(a == OFF)
		GPIOA -> BSRR |= GPIO_BSRR_BR_4;
	else if(a == ON)
		GPIOA -> BSRR |= GPIO_BSRR_BS_4;
}

int main(void)
{
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA -> MODER |= GPIO_MODER_MODER1_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODER1_1;

	GPIOA -> MODER |= GPIO_MODER_MODER2_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODER2_1;

	GPIOA -> MODER |= GPIO_MODER_MODER3_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODER3_1;

	GPIOA -> MODER |= GPIO_MODER_MODER4_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODER4_1;

	init_tim4();

    for(int i = 0; i < 10000; i++)
    {
	    IN1(ON); IN2(OFF); IN3(OFF); IN4(OFF); delay(wait);
	    IN1(ON); IN2(ON); IN3(OFF); IN4(OFF); delay(wait);
	    IN1(OFF); IN2(ON); IN3(OFF); IN4(OFF); delay(wait);
	    IN1(OFF); IN2(ON); IN3(ON); IN4(OFF); delay(wait);
	    IN1(OFF); IN2(OFF); IN3(ON); IN4(OFF); delay(wait);
	    IN1(OFF); IN2(OFF); IN3(ON); IN4(ON); delay(wait);
	    IN1(OFF); IN2(OFF); IN3(OFF); IN4(ON); delay(wait);
    }

    IN1(OFF); IN2(OFF); IN3(OFF); IN4(OFF);
}
