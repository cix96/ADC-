//* dma.h *//

#ifndef DMA_H
#define DMA_H

// peripheral headers
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_adc.h>

#include <ADC.h>
#include <stdio.h>

#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C) 

void voltage_measure(void);
void DMA_init(void);
void DMA2_Stream1_IRQHandler(void);

#endif
