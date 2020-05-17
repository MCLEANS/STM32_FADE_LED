/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "clockconfig.h"
#include "ADC.h"
#include "Timerconfiguration.h"

#define PRESCALER 640
#define ARR_VALUE 66



custom_libraries::clock_config system_clock;
custom_libraries::Timer_configuration delay_timer(TIM3,PRESCALER,ARR_VALUE);

extern "C" void TIM3_IRQHandler(void){
	if(TIM3->SR & (TIM_SR_UIF)){
		TIM3->SR &= ~(TIM_SR_UIF);
	}
}

int main(void)
{
	system_clock.initialize();
	delay_timer.initialize();

	NVIC_SetPriority(TIM3_IRQn,0x03);
	NVIC_EnableIRQ(TIM3_IRQn);

	while(1){

	}
}
