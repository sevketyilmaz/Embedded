#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "delay.h"

int Direction = 0, Start=0, Steps = 0;
BitAction LOW = Bit_RESET, HIGH = Bit_SET;

void motor_pin_init();
void SetDirection();
void stepper();
void stopMotor();

int main(void) {
	
	motor_pin_init();
	
	while(1){
		stepper();
		delay_ms(8);
	}
}

void motor_pin_init() {
	  GPIO_InitTypeDef GPIO_InitStruct_Motor;
	
	  GPIO_InitStruct_Motor.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 ;
		GPIO_InitStruct_Motor.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct_Motor.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct_Motor.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct_Motor.GPIO_Speed = GPIO_Speed_100MHz;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		
	  GPIO_Init(GPIOE, &GPIO_InitStruct_Motor);
}

void stepper() {
	
		switch(Steps){
			case 0:
			GPIO_WriteBit(GPIOE,GPIO_Pin_7, LOW); 
			GPIO_WriteBit(GPIOE,GPIO_Pin_8, HIGH);
			GPIO_WriteBit(GPIOE,GPIO_Pin_9, HIGH);
			GPIO_WriteBit(GPIOE,GPIO_Pin_10, LOW);
			break; 
			case 1:
			GPIO_WriteBit(GPIOE,GPIO_Pin_7, LOW); 
			GPIO_WriteBit(GPIOE,GPIO_Pin_8, HIGH);
			GPIO_WriteBit(GPIOE,GPIO_Pin_9, LOW);
			GPIO_WriteBit(GPIOE,GPIO_Pin_10, HIGH);
			break; 
			case 2:
			GPIO_WriteBit(GPIOE,GPIO_Pin_7, HIGH); 
			GPIO_WriteBit(GPIOE,GPIO_Pin_8, LOW);
			GPIO_WriteBit(GPIOE,GPIO_Pin_9, LOW);
			GPIO_WriteBit(GPIOE,GPIO_Pin_10, HIGH);
			break; 
			case 3:
			GPIO_WriteBit(GPIOE,GPIO_Pin_7, HIGH); 
			GPIO_WriteBit(GPIOE,GPIO_Pin_8, LOW);
			GPIO_WriteBit(GPIOE,GPIO_Pin_9, HIGH);
			GPIO_WriteBit(GPIOE,GPIO_Pin_10, LOW);
			break; 
			default:
			GPIO_WriteBit(GPIOE,GPIO_Pin_7, LOW); 
			GPIO_WriteBit(GPIOE,GPIO_Pin_8, LOW);
			GPIO_WriteBit(GPIOE,GPIO_Pin_9, LOW);
			GPIO_WriteBit(GPIOE,GPIO_Pin_10, LOW);
			break; 
		}
		SetDirection();
} 

void stopMotor() {
	
	GPIO_WriteBit(GPIOE,GPIO_Pin_7, LOW); 
	GPIO_WriteBit(GPIOE,GPIO_Pin_8, LOW);
	GPIO_WriteBit(GPIOE,GPIO_Pin_9, LOW);
	GPIO_WriteBit(GPIOE,GPIO_Pin_10, LOW);
}

void SetDirection(){
	if(Direction==1){ Steps++;}
	if(Direction==0){ Steps--;}
	if(Steps>3){Steps=0;}
	if(Steps<0){Steps=3;}
}