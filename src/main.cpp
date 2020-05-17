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
#include "Timerconfiguration.h"
#include "ADC.h"
#include "PWM.h"

#define PRESCALER 640
#define ARR_VALUE 66

#define POTENTIOMETER_PIN 0


int value_ = 25;
int duty_cycle = 0;

custom_libraries::clock_config system_clock;
custom_libraries::Timer_configuration delay_timer(TIM3,PRESCALER,ARR_VALUE);
custom_libraries::_ADC potentiometer(ADC1,GPIOA,1,custom_libraries::ch1,custom_libraries::FAST);
custom_libraries::PWM LED(TIM1,custom_libraries::channel1,GPIOA,8,custom_libraries::AF1,1000,4095);



extern "C" void TIM3_IRQHandler(void){
	if(TIM3->SR & (TIM_SR_UIF)){
		TIM3->SR &= ~(TIM_SR_UIF);
		potentiometer.count++;
	}
}


extern "C" void ADC_IRQHandler(void){
	if(ADC1->SR & ADC_SR_EOC){
		ADC1->SR &= ~ADC_SR_EOC;
		value_ = ADC1->DR;
		ADC1->CR2 |= ADC_CR2_SWSTART;

	}
}



int main(void)
{
	system_clock.initialize();
	delay_timer.initialize();

	LED.set_duty_cycle(50);
	LED.begin();

	NVIC_SetPriority(TIM3_IRQn,0x03);
	NVIC_EnableIRQ(TIM3_IRQn);

	potentiometer.initialize();

	NVIC_SetPriority(ADC_IRQn,0x03);
	NVIC_EnableIRQ(ADC_IRQn);



	while(1){

		LED.set_duty_cycle(value_);
	}
}
