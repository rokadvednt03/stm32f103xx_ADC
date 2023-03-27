#include "stm32f10x.h"
#include "stm32f103xx_adc.h"

void ADC_PeriClockControl(ADC_TypeDef *pADCx , uint8_t EnorDI)
{
	if(EnorDI == ENABLE)
	{
		if(pADCx == ADC1)
			RCC->APB2ENR |= (RCC_APB2ENR_ADC1EN);
		else 
			RCC->APB2ENR |= (RCC_APB2ENR_ADC1EN);
	}
	else
	{
		if(pADCx == ADC1)
			RCC->APB2ENR &= ~(RCC_APB2ENR_ADC1EN);
		else 
			RCC->APB2ENR &= ~(RCC_APB2ENR_ADC1EN);
	}
}


void ADC_OneChannel(ADC_Handle_t *pHandleADC , uint8_t channel_name)
{
		if(pHandleADC->Config.Data_Align == ADC_Data_Align_RIGHT)
			pHandleADC->pADCx->CR2 &= ~ADC_CR2_ALIGN;
		else
			pHandleADC->pADCx->CR2 |= ADC_CR2_ALIGN;
		
		
		//config sampling rate
		if(channel_name < ADC_Channel_10)
		{
			//config in ADC_SMPR2
			pHandleADC->pADCx->SMPR2 |= (pHandleADC->Config.SamplingRate << (channel_name)*3);
		}
		else
		{
			//config in ADC_SMPR1
			pHandleADC->pADCx->SMPR2 |= (pHandleADC->Config.SamplingRate << (channel_name*3) - 30);
		}
		
		//config sequence
		pHandleADC->pADCx->SQR3 |= (channel_name);
	
}

void ADC_StartConv(ADC_TypeDef *pADCx)
{
	int a ;
	pADCx->CR1 |= (ADC_CR1_SCAN);
	pADCx->CR2 |= (ADC_CR2_CONT);
	pADCx->CR2 |= (ADC_CR2_ADON);
	for(a=0 ; a<10000;a++);
	pADCx->CR2 |= (ADC_CR2_ADON);
	for(a=0 ; a<10000;a++);
	for(a=0 ; a<10000;a++);
	pADCx->CR2 |= ADC_CR2_CAL;
	for(a=0 ; a<10000;a++);
	for(a=0 ; a<10000;a++);
}


void ADC_Init(ADC_Handle_t *pHandleADC)
{
	if(pHandleADC->Config.Data_Align == ADC_Data_Align_RIGHT)
		pHandleADC->pADCx->CR2 &= ~ADC_CR2_ALIGN;
	else
		pHandleADC->pADCx->CR2 |= ADC_CR2_ALIGN;
	
	pHandleADC->pADCx->SQR1 |= (pHandleADC->Config.NoOFConvMode-1 << 20);
}
	
void ADC_ChConf(ADC_Handle_t *pHandleADC , uint8_t channel_name,uint8_t channel_sequence)
{
		
		//config sampling rate
		if(channel_name < ADC_Channel_10)
		{
			//config in ADC_SMPR2
			pHandleADC->pADCx->SMPR2 |= (pHandleADC->Config.SamplingRate << (channel_name)*3);
		}
		else
		{
			//config in ADC_SMPR1
			pHandleADC->pADCx->SMPR2 |= (pHandleADC->Config.SamplingRate << (channel_name*3) - 30);
		}
		
		//config sequence
		if(channel_sequence < ADC_Ch_sqn_7)
		{
			pHandleADC->pADCx->SQR3 |= (channel_name << (channel_sequence*5));
		}
		else if((channel_sequence < ADC_Ch_sqn_13) & (channel_sequence > ADC_Ch_sqn_6))
		{
			pHandleADC->pADCx->SQR3 |= (channel_name << ((channel_sequence*5)-35));
		}
		else if((channel_sequence > ADC_Ch_sqn_12))
		{
			pHandleADC->pADCx->SQR3 |= (channel_name << ((channel_sequence*5)-65));
		}
	
}
	
