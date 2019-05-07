//* main.c *//

#include <main.h>

int main(void){

			ADC_Init123();
			DMA_init();
			USART1_Init();
			timer2_init();
			ADC_SoftwareStartConv(ADC3);
	
			while(1){
			}
}
