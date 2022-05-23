int FlagH=0;
int flag2=0;
void GPIOF_Handler(void);
void GPIOA_Handler(void);

void GPIOF_Handler(void){
 if(GPIO_PORTF_MIS_R&&0x10 == 0x10){
 GPIO_PORTF_ICR_R = 0x10;
 FlagH=1;
}
 if(GPIO_PORTF_MIS_R&&0x10 == 0x10){
 GPIO_PORTF_ICR_R = 0x01;
 FlagH=2;
}
}

void GPIOA_Handler(void){
 GPIO_PORTF_DATA_R&=~0x0E;
 GPIO_PORTA_ICR_R = 0x80;
if(flag2!=1){
 FlagH=1;
}
}
