#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include "main.h"
#include "delay.h"
#include "keypad.h"

/* Pins configuration, columns are outputs */
#define COLUMN_1_HIGH		GPIO_SetBits(COLUMN_1_PORT, COLUMN_1_PIN)
#define COLUMN_1_LOW		GPIO_ResetBits(COLUMN_1_PORT, COLUMN_1_PIN)
#define COLUMN_2_HIGH		GPIO_SetBits(COLUMN_2_PORT, COLUMN_2_PIN)
#define COLUMN_2_LOW		GPIO_ResetBits(COLUMN_2_PORT, COLUMN_2_PIN)
//#define COLUMN_3_HIGH		GPIO_SetBits(COLUMN_3_PORT, COLUMN_3_PIN)
//#define COLUMN_3_LOW		GPIO_ResetBits(COLUMN_3_PORT, COLUMN_3_PIN)
//#define COLUMN_4_HIGH		GPIO_SetBits(COLUMN_4_PORT, COLUMN_4_PIN)
//#define COLUMN_4_LOW		GPIO_ResetBits(COLUMN_4_PORT, COLUMN_4_PIN)

/* Read input pins */
#define ROW_1_CHECK			(!GPIO_ReadInputDataBit(ROW_1_PORT, ROW_1_PIN))
#define ROW_2_CHECK			(!GPIO_ReadInputDataBit(ROW_2_PORT, ROW_2_PIN))
#define ROW_3_CHECK			(!GPIO_ReadInputDataBit(ROW_3_PORT, ROW_3_PIN))
//#define ROW_4_CHECK			(!GPIO_ReadInputDataBit(ROW_4_PORT, ROW_4_PIN))

uint8_t Buttons[4][2] = {
	{1, 2},
	{3, 4},
	{5, 6},
};

uint8_t status;

void keypad_init(void);
uint8_t Read_Status(void);
void SetColumn(uint8_t column);
uint8_t CheckRow(uint8_t column);

int main(void) {
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	keypad_init();
	
	while (1) {

		status = Read_Status();
		if(status == 2)
				STM_EVAL_LEDToggle(LED3);
		if(status == 4)
				STM_EVAL_LEDToggle(LED4);
		if(status == 6)
				STM_EVAL_LEDToggle(LED5);
		delay_ms(15);
	}
}

void keypad_init() {
	
		GPIO_InitTypeDef GPIO_InitStruct_Keypad_Column;
		GPIO_InitTypeDef GPIO_InitStruct_Keypad_Row;

	  GPIO_InitStruct_Keypad_Column.GPIO_Pin = COLUMN_1_PIN | COLUMN_2_PIN; //| COLUMN_3_PIN | COLUMN_4_PIN;
		GPIO_InitStruct_Keypad_Column.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct_Keypad_Column.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct_Keypad_Column.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct_Keypad_Column.GPIO_Speed = GPIO_Speed_100MHz;
	 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		
	  GPIO_Init(GPIOD, &GPIO_InitStruct_Keypad_Column);
	
		GPIO_InitStruct_Keypad_Row.GPIO_Pin = ROW_1_PIN | ROW_2_PIN | ROW_3_PIN;// | ROW_4_PIN;
		GPIO_InitStruct_Keypad_Row.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct_Keypad_Row.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct_Keypad_Row.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct_Keypad_Row.GPIO_Speed = GPIO_Speed_100MHz;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		
	  GPIO_Init(GPIOC, &GPIO_InitStruct_Keypad_Row);
}



void SetColumn(uint8_t column) {
	/* Set rows high */
	COLUMN_1_HIGH;
	COLUMN_2_HIGH;
	//COLUMN_3_HIGH;
  //COLUMN_4_HIGH;
	
	/* Set column low */
	if (column == 1) {
		COLUMN_1_LOW;
	}
	if (column == 2) {
		COLUMN_2_LOW;
	}
	//if (column == 3) {
	//	COLUMN_3_LOW;
	//}
	//if (column == 4) {
	//	COLUMN_4_LOW;
	//}
}

uint8_t CheckRow(uint8_t column) {
	/* Read rows */
	
	/* Scan row 1 */
	if (ROW_1_CHECK) {
		return Buttons[0][column - 1];	
	}
	/* Scan row 2 */
	if (ROW_2_CHECK) {
		return Buttons[1][column - 1];
	}
	/* Scan row 3 */
	if (ROW_3_CHECK) {
		return Buttons[2][column - 1];
	}
	/* Scan row 4 */
	//if (ROW_4_CHECK) {
	//	return Buttons[3][column - 1];
	//}
	
	/* Not pressed */
	return NO_PRESSED;
}

uint8_t Read_Status(void) {
	uint8_t check;
	/* Set row 1 to LOW */
	SetColumn(1);
	/* Check rows */
	check = CheckRow(1);
	if (check != NO_PRESSED) {
		return check;
	}
	
	/* Set row 2 to LOW */
	SetColumn(2);
	/* Check columns */
	check = CheckRow(2);
	if (check != NO_PRESSED) {
		return check;
	}
	
	/* Set row 3 to LOW */
	SetColumn(3);
	/* Check columns */
	check = CheckRow(3);
	if (check != NO_PRESSED) {
		return check;
	}

	/* Set column 4 to LOW */
	SetColumn(4);
	/* Check rows */
	check = CheckRow(4);
	if (check != NO_PRESSED) {
		return check;
	}
	
	/* Not pressed */
	return NO_PRESSED;
}

