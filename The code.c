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
