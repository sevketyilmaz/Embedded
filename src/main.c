#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "delay.h"

BitAction LOW = Bit_RESET, HIGH = Bit_SET;

void solenoid_pin_init();

int main(void) {
	
	solenoid_pin_init();
	//Set Solenoid 
	GPIO_WriteBit(GPIOC,GPIO_Pin_7, HIGH);
	delay_ms(100);
	GPIO_WriteBit(GPIOC,GPIO_Pin_7, LOW);
	
	while(1);
}

void solenoid_pin_init() {
	  GPIO_InitTypeDef GPIO_InitStruct_Solenoid;
	
	  GPIO_InitStruct_Solenoid.GPIO_Pin = GPIO_Pin_7; // PC7
		GPIO_InitStruct_Solenoid.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct_Solenoid.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct_Solenoid.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct_Solenoid.GPIO_Speed = GPIO_Speed_100MHz;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		
	  GPIO_Init(GPIOC, &GPIO_InitStruct_Solenoid);
}