#include "stm32f10x.h"
#include "stm32f103xx_gpio.h"

#define ADC_Data_Align_RIGHT 0
#define ADC_Data_Align_LEFT 1

#define ADC_ScanConvMode_DI 0
#define ADC_ScanConvMode_En 1

#define ADC_RegularConvMode_SnglConv 0
#define ADC_RegularConvMode_SeqnceConv 0

#define ADC_ContConvMode_ContinuousMode 0
#define ADC_ContConvMode_DisContinuousMode 1

#define ADC_Channel_0		0
#define ADC_Channel_1		1
#define ADC_Channel_2		2
#define ADC_Channel_3		3
#define ADC_Channel_4		4
#define ADC_Channel_5		5
#define ADC_Channel_6		6
#define ADC_Channel_7		7
#define ADC_Channel_8		8
#define ADC_Channel_9		9
#define ADC_Channel_10		10
#define ADC_Channel_11		11
#define ADC_Channel_12		12
#define ADC_Channel_13		13
#define ADC_Channel_14		14
#define ADC_Channel_15		15


#define ADC_SmplRate_1_5_Cycle 0
#define ADC_SmplRate_7_5_Cycle 1
#define ADC_SmplRate_13_5_Cycle 2
#define ADC_SmplRate_28_5_Cycle 3
#define ADC_SmplRate_41_5_Cycle 4
#define ADC_SmplRate_55_5_Cycle 5
#define ADC_SmplRate_71_5_Cycle 6
#define ADC_SmplRate_239_5_Cycle 7

#define ADC_Ch_sqn_1 0
#define ADC_Ch_sqn_2 1
#define ADC_Ch_sqn_3 2
#define ADC_Ch_sqn_4 3
#define ADC_Ch_sqn_5 4
#define ADC_Ch_sqn_6 5
#define ADC_Ch_sqn_7 6
#define ADC_Ch_sqn_8 7
#define ADC_Ch_sqn_9 8
#define ADC_Ch_sqn_10 9
#define ADC_Ch_sqn_11 10
#define ADC_Ch_sqn_12 11
#define ADC_Ch_sqn_13 12
#define ADC_Ch_sqn_14 13
#define ADC_Ch_sqn_15 14
#define ADC_Ch_sqn_16 15
#define ADC_Ch_sqn_17 16
#define ADC_Ch_sqn_18 17


typedef struct
{
	uint32_t Data_Align ;
	uint32_t NoOFConvMode;
	uint32_t RegularConvMode;
	uint32_t SamplingRate;
	/*uint32_t ScanConvMode;
	uint32_t NoOFConvMode;
	uint32_t RegularConvMode;
	uint32_t ContConvMode;
	*/
}ADC_Config_t;


typedef struct
{
	ADC_Config_t Config;
	ADC_TypeDef *pADCx;
	
}ADC_Handle_t;


void ADC_Init(ADC_Handle_t *pHandleADC);
void ADC_PeriClockControl(ADC_TypeDef *pADCx , uint8_t EnorDI);
void ADC_OneChannel(ADC_Handle_t *pHandleADC , uint8_t channel_name);
void ADC_StartConv(ADC_TypeDef *pADCx);
void ADC_Data_Align(ADC_Handle_t *pHandleADC);
void ADC_ChConf(ADC_Handle_t *pHandleADC , uint8_t channel_name,uint8_t channel_sequence);
