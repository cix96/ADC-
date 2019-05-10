//* dma.c *//

#include <DMA.h>
#include <usart.h>
#include <stdio.h>
#include <math.h>

DMA_InitTypeDef				DMA_InitStruct;
NVIC_InitTypeDef			NVIC_InitStruct;

uint16_t 							ADCConvertedValue;

//DMA init

void DMA_init(void)
{
		
	  //configure DMA - ADC3
		DMA_InitStruct.DMA_Channel = DMA_Channel_2;
		DMA_InitStruct.DMA_PeripheralBaseAddr = ADC3_DR_ADDRESS;
		DMA_InitStruct.DMA_Memory0BaseAddr =(uint32_t)&ADCConvertedValue;
		DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
		DMA_InitStruct.DMA_BufferSize = 1;
		DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStruct.DMA_Priority = DMA_Priority_High;
		DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;
		DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
		DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(DMA2_Stream1, &DMA_InitStruct);
		
		
		//* Enable DMA2 Stream1 */  Stream1 higher priority than Stream2...
		DMA_Cmd(DMA2_Stream1, ENABLE);
		DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE);
		
		// Configure priority bits
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);		// 4 bits preemptive,0 bits for subpriority
		
		// Configure NVIC(nested vectored interrupt controller) for ADC
		NVIC_InitStruct.NVIC_IRQChannel = DMA2_Stream1_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// highest priority
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;					// highest subpriority
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
						
		// enable requests after last transfer		
		//ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
		ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE);
}

struct{
		uint16_t U;
}Voltage;

void DMA2_Stream1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1) == SET)			
	{
		Voltage.U = ADCConvertedValue*4800/0xFFF; 
		DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);		// clear pending bit
		ADC_SoftwareStartConv(ADC3);
	}		
}	


void voltage_measure(void) {

			char buff[500];
			sprintf(buff, "Izlazni napon je : %d [mV]\r\n",Voltage.U);
			send_message(buff);
}
