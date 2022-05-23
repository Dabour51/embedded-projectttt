void Buzzer_Init(){ 
 SYSCTL_RCGCGPIO_R |= 0x08;
 while ((SYSCTL_PRGPIO_R & 0x08) == 0);
 GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
 GPIO_PORTD_CR_R |= 0x80;
 GPIO_PORTD_AFSEL_R &= ~0x80;
 GPIO_PORTD_PCTL_R &= ~0xF0000000;
 GPIO_PORTD_AMSEL_R &= ~0x80;
 GPIO_PORTD_DEN_R |= 0x80;
 GPIO_PORTD_DIR_R |= 0x80;
 GPIO_PORTD_DATA_R &= ~0x80;
}