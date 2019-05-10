//* adc.h *//

#ifndef ADC_H
#define ADC_H

// peripheral headers
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_adc.h>

#include <stdio.h>
#include <DMA.h>

#define U1					GPIO_Pin_1

void ADC_Init123(void);
void DMA2_Stream1_IRQHandler(void);

#endif
