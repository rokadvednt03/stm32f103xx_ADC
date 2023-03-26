#include "stm32f103xx_adc.h"
#include "stm32f103xx_uart.h"
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	GPIO_Handle_t gpio;
	GPIO_Handle_t tx ;
	USART_Handle_t trans;
	uint32_t n ;
	int a;
	char data[] = "This is The ADC vaal = ";
	
	tx.pGPIOx = GPIOA ;
	tx.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_10MHZ ;
	tx.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP;
	tx.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9 ;
	
	gpio.pGPIOx = GPIOA;
	gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	gpio.GPIO_PinConfig.GPIO_ModeInOut = GPIO_IN;
	gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ANALOGIN;
	
	trans.pUSARTx = USART1;
	trans.USART_Config.USART_Baud = USART_STD_BAUD_9600 ;
	trans.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	trans.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1 ; 
	trans.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	trans.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;

	
	GPIO_PeriClockControl(GPIOA , ENABLE );
	USART_PeriClockControl(USART1 , ENABLE);
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	GPIO_PeriClockControl(GPIOA,ENABLE);
	
	GPIO_Init(&tx);
	tx.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10 ;
	GPIO_Init(&tx);
	GPIO_Init(&gpio);
	USART_Init(&trans);
	
	USART_Enable(USART1,ENABLE);	
	
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->SMPR2 |= (4<<15);
	ADC1->SQR3 |= (5<<0);
	
	ADC1->CR1 |= (ADC_CR1_SCAN);
	ADC1->CR2 |= (ADC_CR2_CONT);
	ADC1->CR2 |= (ADC_CR2_ADON);
	for(a=0 ; a<10000;a++);
	ADC1->CR2 |= (ADC_CR2_ADON);
	for(a=0 ; a<10000;a++);
	for(a=0 ; a<10000;a++);
	ADC1->CR2 |= ADC_CR2_CAL;
	for(a=0 ; a<10000;a++);
	for(a=0 ; a<10000;a++);
	
	
	n = 57;
	USART_SendData(&trans,(uint8_t*)n , 4);
	while(1)
	{
		n = ADC1->DR;
		//USART_SendData(&trans,(uint8_t*)data , sizeof(data));
		
	}
	
}
