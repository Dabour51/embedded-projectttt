void sw12_Init(){
 SYSCTL_RCGCGPIO_R |= 0x20;
 while ((SYSCTL_PRGPIO_R & 0x20) == 0);
 GPIO_PORTF_LOCK_R |= GPIO_LOCK_KEY;
 GPIO_PORTF_CR_R |= 0x11;
 GPIO_PORTF_AFSEL_R &= ~0x11;
 GPIO_PORTF_PCTL_R &= ~0x000F000F;
 GPIO_PORTF_AMSEL_R &= ~0x11;
 GPIO_PORTF_DEN_R |= 0x11;
 GPIO_PORTF_DIR_R &= ~0x11;
 GPIO_PORTF_PUR_R |= 0X11;
}

void sw3_Init(){
 SYSCTL_RCGCGPIO_R |= 0x01;
 while((SYSCTL_PRGPIO_R &0x01)==0) ;
 GPIO_PORTA_DIR_R &= ~0x80;
 GPIO_PORTA_DEN_R |=0x80;
 GPIO_PORTA_CR_R |=0x80;
 GPIO_PORTA_AMSEL_R &= ~0x80;
 GPIO_PORTA_PCTL_R &= ~0xF0000000;
 GPIO_PORTA_AFSEL_R &=~0x80;
 GPIO_PORTA_PDR_R |=0x80;
}