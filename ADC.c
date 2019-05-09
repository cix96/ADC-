//* adc.h *//

#include <adc.h>
  

void ADC_Init123(void)
{
	
			GPIO_InitTypeDef				GPIO_InitStruct;
			ADC_InitTypeDef					ADC_InitStruct;
			ADC_CommonInitTypeDef		ADC_CommonInitStruct;

			// enable the ADC interface and GPIO clock
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); 		// ADC3 interface clock
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	// ADC GPIOs clock
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 		// DMA clock
		
			// Configure ADC pins in analog mode
			GPIO_InitStruct.GPIO_Pin = U1; 													// port A ADC inputs
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; 							// analog mode
			GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
			// Select the Independent mode ADC regular channels features
			ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;							
			ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2; 							// pclk2/2 (60MHz?/2)
			ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 	// 3 half-words one by one
			
			//ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	// for interleaved mode
			ADC_CommonInit(&ADC_CommonInitStruct);
		
		
			// Configure the ADC3
			ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b; 													// 12 bit
			ADC_InitStruct.ADC_ScanConvMode = ENABLE;																			// DMA cares for results 
			ADC_InitStruct.ADC_ContinuousConvMode = DISABLE; 															// Continuous mode disabled
			ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; 
			ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; 													// Right alignement
			ADC_InitStruct.ADC_NbrOfConversion = 4;								
			ADC_Init(ADC3, &ADC_InitStruct);
			
		
			// Configure regular channel group
			ADC_RegularChannelConfig(	ADC3,																// ADC peripheral
																ADC_Channel_0,											// ADC channel to configure U1
																1,																	// rank, first in order
																ADC_SampleTime_28Cycles);						// 28 sampling cycles
		
			// enable DMA for ADCs
			ADC_DMACmd(ADC3, ENABLE);
			
			ADC_ITConfig(ADC3, ADC_IT_EOC, ENABLE);
					
			// Set ADC ON
			ADC_Cmd(ADC3, ENABLE);																				// enable ADC3
			
}
