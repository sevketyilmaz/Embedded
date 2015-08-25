#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_tim.h"

void TIM_Init();

int main(void) {
	
	TIM_Init();
	TIM10->CCR1 = 10000;
	while(1);
}

void TIM_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	uint16_t  _250Hz = 1279, _500Hz = 639, _1kHz = 319, _2kHz = 159, _4kHz = 79, _8kHz = 39;
	
	uint16_t CCR1_Val = 35000;
	uint16_t PrescalerValue = 0;
	
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);

		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);

  PrescalerValue = (uint16_t) (SystemCoreClock / 45000) - 1;

  TIM_TimeBaseStructure.TIM_Period = 65535;//ARR Value
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
  TIM_OCInitStructure.TIM_Pulse = 0;
  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM10, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM10, ENABLE);

  TIM_Cmd(TIM10, ENABLE);
}
