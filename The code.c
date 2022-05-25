#include "tm4c123gh6pm.h"
#include "stdio.h"
#include "stdlib.h"
int FlagH=0;
int flag2=0;
void GPIOF_Handler(void);
void GPIOA_Handler(void);
void startMenu();
void delay_micro(int n)
{
 int i , j;
 for(i=0;i<n;i++)
 {
 for(j=0;j<3;j++)
 {}
 }
}
void delay_milli(int n)
{
 int i , j;
 for(i=0;i<n;i++)
 {
 for(j=0;j<3180;j++)
 {}
 }
}
void SysTick_wait(unsigned long delay){
NVIC_ST_CTRL_R = 0;
NVIC_ST_RELOAD_R = delay-1;
NVIC_ST_CURRENT_R =0;
NVIC_ST_CTRL_R = 0x00000005;
while ((NVIC_ST_CTRL_R &0x00010000)==0){
}
}
void delay(unsigned long time ){
int i;
for(i =0 ; i<time ;i++){
SysTick_wait(16000); // delay for 1msec
}
}
void lcd_data(unsigned char data)
 {
 GPIO_PORTA_DATA_R = 0x20 ;
 GPIO_PORTA_DATA_R |= 0x80; 
 GPIO_PORTB_DATA_R = data;
 delay_micro(10);
 GPIO_PORTA_DATA_R = 0x00;
 delay_micro(100);
 }
void lcd_write4bits (unsigned char data , unsigned char control)
{
 data &=0xf0;
 control &=0x0f;
 GPIO_PORTB_DATA_R = data|control;
 GPIO_PORTB_DATA_R = data|control| 4;
 delay_micro(0);
 GPIO_PORTB_DATA_R = data;
}
void lcd_4bits_cmd (unsigned char command)
{
 lcd_write4bits(command & 0xf0 , 0);
 lcd_write4bits(command << 4 , 0);
 if (command < 4)
 delay_milli(2);
 else
 delay_micro(40);
 }
void lcd_4bits_data (unsigned char data) // print 1 char
{
 lcd_write4bits(data & 0xf0 , 1);
 lcd_write4bits(data << 4 , 1);
 delay_micro(40);
}
void lcd_init ()
{
 SYSCTL_RCGCGPIO_R |= 0x2;
 while((SYSCTL_PRGPIO_R &= 0x2)==0) ;
 GPIO_PORTB_DIR_R |= 0xff;
 GPIO_PORTB_DEN_R |=0xff;
 GPIO_PORTB_PCTL_R &=~ 0xffffffff;
 GPIO_PORTB_LOCK_R=0x4C4F434B;
 lcd_4bits_cmd(0x28);
 lcd_4bits_cmd(0x06);
 lcd_4bits_cmd(0x01);
 lcd_4bits_cmd(0x0f);
}
void LCD_String (char *str)
{
 int i;
 for(i=0;str[i]!=0;i++) /* Send each char of string till the NULL */
 {
 if (i==16)
 {
 lcd_4bits_cmd(0xc0);
 }
 lcd_4bits_data(str[i]); /* Call LCD data write */
 }
}
void keypad_init ()
{
 SYSCTL_RCGCGPIO_R |= 0x4;
 while((SYSCTL_PRGPIO_R &= 0x4)==0) ; 
 SYSCTL_RCGCGPIO_R |= 0x10;
 while((SYSCTL_PRGPIO_R &= 0x10)==0) ; 
 GPIO_PORTE_DIR_R |=0xf;
 GPIO_PORTE_DEN_R |=0xf;
 GPIO_PORTE_ODR_R |=0XF;
 GPIO_PORTC_DIR_R &=~ 0xf0;
 GPIO_PORTC_DEN_R |= 0xf0;
 GPIO_PORTC_PUR_R |= 0xf0;
}
unsigned char get_key ()
{
 const unsigned char keypad [4][4]={ {'1','2','3','A'},
 
{'4','5','6','B'},
 
{'7','8','9','C'},
{'*','0','#','D'} };
unsigned int row , col ;
 GPIO_PORTE_DATA_R &=~ 0xf;
 col = GPIO_PORTC_DATA_R & 0xf0;
 if (col == 0xf0)
 return 0 ;
 while(1)
 {
 row=0 ;
 GPIO_PORTE_DATA_R = 0xe;
 delay_micro(10);
 col = GPIO_PORTC_DATA_R &0xf0;
 if(col != 0xf0)
 break;
 row=1 ;
 GPIO_PORTE_DATA_R = 0xd;
 delay_micro(10);
 col = GPIO_PORTC_DATA_R &0xf0;
 if(col != 0xf0)
 break;
 row=2 ;
 GPIO_PORTE_DATA_R = 0xb;
 delay_micro(10);
 col = GPIO_PORTC_DATA_R &0xf0;
 if(col != 0xf0)
 break;
 row=3 ;
 GPIO_PORTE_DATA_R = 0x7;
 delay_micro(10);
 col = GPIO_PORTC_DATA_R &0xf0;
 if(col != 0xf0)
 break;
 return 0;
 }
 if(col == 0xe0)
 return keypad[row][0];
 if(col == 0x0d0)
 return keypad[row][1];
 if(col == 0x0b0)
 return keypad[row][2];
 if(col == 0x070)
 return keypad[row][3];
 return 0 ;
}
void Buzzer_Init(){ //using port D7
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
void Buzzer_sound(){
GPIO_PORTD_DATA_R =GPIO_PORTD_DATA_R ^ 0x80;// buzzer on or off
}
void LedsInit () {
 SYSCTL_RCGCGPIO_R |= 0x20;
 while ((SYSCTL_PRGPIO_R & 0x20) == 0);
 GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
 GPIO_PORTF_CR_R |= 0x0E;
 GPIO_PORTF_AFSEL_R &= ~0x0E;
 GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
 GPIO_PORTF_AMSEL_R &= ~0x0E;
 GPIO_PORTF_DEN_R |= 0x0E;
 GPIO_PORTF_DIR_R |= 0x0E;
 GPIO_PORTF_DATA_R &= ~0x0E;
}
void blink_led(){
GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;// change the light on or off
}
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
 GPIO_PORTF_IS_R &= ~0x11;
 GPIO_PORTF_IBE_R &= ~0x11;
 GPIO_PORTF_IEV_R &= ~0x11;
 GPIO_PORTF_ICR_R &= ~0x11;
 GPIO_PORTF_IM_R |= 0x11;
 NVIC_EN0_R = (1 << 30);
 NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000 ;
}
void sw3_Init(){//using port A7
 SYSCTL_RCGCGPIO_R |= 0x01;
 while((SYSCTL_PRGPIO_R &0x01)==0) ;
 GPIO_PORTA_DIR_R &= ~0x80;
 GPIO_PORTA_DEN_R |=0x80;
 GPIO_PORTA_CR_R |=0x80;
 GPIO_PORTA_AMSEL_R &= ~0x80;
 GPIO_PORTA_PCTL_R &= ~0xF0000000;
 GPIO_PORTA_AFSEL_R &=~0x80;
 GPIO_PORTA_PDR_R |=0x80;
 GPIO_PORTA_IS_R &= ~0x80;
 GPIO_PORTA_IBE_R &= ~0x80;
 GPIO_PORTA_IEV_R &= ~0x80;
 GPIO_PORTA_ICR_R &= ~0x80;
 GPIO_PORTA_IM_R |= 0x80;
 NVIC_EN0_R = (1 << 0);
 NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF00)|0x00000040 ;
}
unsigned char sw12_input(void){
 return (GPIO_PORTF_DATA_R & 0x11);
}
void timer(int x){
 int i,minutes, minutes1, minutes2, seconds, seconds1, 
seconds2, maxSeconds;
  int res=0;
 minutes = x / 100;
 minutes1 = minutes / 10;
 minutes2 = minutes % 10;
 seconds = x % 100;
 seconds1 = seconds / 10;
 seconds2 = seconds % 10;
 maxSeconds = minutes*60+seconds;
 blink_led();
 for(i=0; i<maxSeconds+1; i++)
 {
 L1: if((FlagH==1)){
 flag2=1;
 FlagH=0;
	GPIO_PORTF_DATA_R&=~0x0E;
 while(1){
  blink_led();
	 delay(300);
 if(FlagH==2) {
 FlagH=0;
 flag2=0;
 GPIO_PORTF_DATA_R&=~0x0E;
 if((GPIO_PORTA_DATA_R&0x80)==0x80){
 while(FlagH==0 || ((GPIO_PORTA_DATA_R&0x80)==0x80)){
  blink_led();
 delay(300); 
 }
 res=1;
 }
 flag2=0;
 if(res != 1){
 GPIO_PORTF_DATA_R|=0x0E;
 }
 else{
 res=0;
 goto L1;
 }
 break;
 }
 if(FlagH==1){ FlagH=0;
 lcd_4bits_cmd(0x01);
 GPIO_PORTF_DATA_R&=~0x0E;
 flag2=0;
 startMenu();
 }
 }
 }
 LCD_String(" ");
 delay(10);
 lcd_4bits_data(minutes1+48);
 lcd_4bits_data(minutes2+48);
 lcd_4bits_data(':');
 lcd_4bits_data(seconds1+48);
 lcd_4bits_data(seconds2+48);
 delay(1000);
 lcd_4bits_cmd(0x80);
 seconds2--;
 if(seconds2==-1)
 {
 seconds1--;
 seconds2=9;
 }
 if(seconds1==-1)
 {
 minutes2--;
 seconds1=5;
 }
 if(minutes2==-1)
 {
 minutes1--;
 minutes2=9;
 }
 }
 blink_led(); 
 delay(1000);
 for(i=0 ; i<6 ; i++){
 Buzzer_sound();
 blink_led(); 
 delay(1000);
 }
 startMenu();
 }
void popcorn_cooking(){
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 while(1){
 LCD_String(" Popcorn");
 while(sw12_input() & 0x10 != 0x00);
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 delay(10);
 GPIO_PORTF_DATA_R |= 0x11;
 timer(100);
 break;
 }
 }
void beef_cooking(){
 char value,weight;
 int time,sw12;
LCD_String("Beef Weight? (1 to 9)");
 while(1){
 do{
 value = get_key();
}while(value==0);
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 if (value > '0' & (value <= '9')){
 lcd_4bits_data(value);
 delay(500);
 weight = value;
 }
 else if((value <= '0') | (value > '9')){
 lcd_4bits_cmd(0x1);
 delay(100);
 LCD_String(" Err");
 delay(2000);
 lcd_4bits_cmd(0x1);
 beef_cooking();
}
 do{
 sw12 = sw12_input();
}while((sw12 == 0x11));
 if ((sw12 & 0x10) == 0x00 ){
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 beef_cooking();
 }
 else if ((sw12 & 0x01) == 0x00){
 lcd_4bits_cmd(0x1);
 delay(100);
 weight = weight -48;
 if((weight >0) && (weight <10) && (weight %2 ==0)){
time = weight * 50;
 timer(time);
 }
 else if ((weight >0) && (weight <10) && (weight %2 !=0)){
 time = (weight-1) * 50 + 30;
 timer(time);
}
}
 break;
}
 }
