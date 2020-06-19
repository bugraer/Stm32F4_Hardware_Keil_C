#include "stm32f4xx.h" 

unsigned int adc;
unsigned int ccr=10;    


void TIM3_IRQHandler(){
	TIM3->SR &= ~TIM_SR_UIF;
	
	if(ccr>985)
		ccr=10;
	
	ccr+=10;
	
	TIM3->CCR1 &= ~TIM_PSC_PSC;
	TIM3->CCR1 |= ccr;
}

int main ()  { 
   
    int i; 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1 | GPIO_MODER_MODER6_1; 
  	GPIOA->AFR[0] |= GPIO_AFRL_AFRL6_1;  
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
    ADC1->CR2 |= ADC_CR2_ADON; 
    ADC1->CR2 |=ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_SWSTART; 
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		
	TIM3->PSC &= ~TIM_PSC_PSC;
	TIM3->PSC |= 15U;
	
	TIM3->ARR &= ~TIM_PSC_PSC;
	TIM3->ARR |= 1000U;
	
	TIM3->CCR1 &= ~TIM_PSC_PSC;
	TIM3->CCR1 |= ccr;
	
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	
	TIM3->CCER |= TIM_CCER_CC1E;
	
	TIM3->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM3_IRQn);
	
	TIM3->CR1 |= TIM_CR1_CEN;

    while(1){
        for(i=0;i<5000;i++);
        adc=ADC1->DR;
        ccr= ((float)adc/4095)*3;   
    }
}