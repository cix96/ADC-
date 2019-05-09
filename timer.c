//* timer.c *//

#include <timer.h>
#include <dma.h>
#include <usart.h>

void timer2_init(void) { 
	
			TIM_TimeBaseInitTypeDef 		TIM_TimeBaseStructure; 	// init def struct for timer
			NVIC_InitTypeDef 						NVIC_InitStructure; 		// init def struct for NVIC
			
			RCC_ClocksTypeDef 					RCC_Clocks; 						// for reading current clock setting - useful
			
			//	uint32_t APB1_CLK; // APB1 clock - max. 42 MHz!
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 		// enable TIM2 peripheral clock
			TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE); 						// ensure that interrupt is disabled
			
			RCC_GetClocksFreq(&RCC_Clocks); 												// fill query struct
			
			//	APB1_CLK = RCC_Clocks.PCLK1_Frequency; // WARNING: APB1 is "slow" peripheral interface that with
			
			// Time Base configuration
			TIM_TimeBaseStructure.TIM_Prescaler = 2499;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // counts from 0 to autoreload, and then back to 0
			TIM_TimeBaseStructure.TIM_Period = 16799;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
			
			// set TIM2 IRQ
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
			
			// Enable the TIM2 global Interrupt
			NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //lower priority than USART3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			
			
			// TIM2 counter enable
			TIM_Cmd(TIM2, ENABLE);

}


void TIM2_IRQHandler(void){
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){	
			voltage_measure();
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
