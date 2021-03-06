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
	data     &=0xf0;
	control  &=0x0f;
	GPIO_PORTB_DATA_R = data|control;
	GPIO_PORTB_DATA_R = data|control| 4;
	delay_micro(0);
	GPIO_PORTB_DATA_R  = data;
}
void lcd_4bits_cmd (unsigned char command)
{
	lcd_write4bits(command & 0xf0 , 0);
	lcd_write4bits(command << 4   , 0);
	if (command < 4)
	
		delay_milli(2);
		else
		delay_micro(40);
	}
void lcd_4bits_data (unsigned char data) // print 1 char
{
	lcd_write4bits(data & 0xf0 , 1);
	lcd_write4bits(data << 4   , 1);
	delay_micro(40);
}
	


void lcd_init ()
{
	SYSCTL_RCGCGPIO_R |= 0x2;
  while((SYSCTL_PRGPIO_R &= 0x2)==0) ;
//	SYSCTL_RCGCGPIO_R |= 0x1;
//  while((SYSCTL_PRGPIO_R &= 0x1)==0) ;
//	GPIO_PORTA_DIR_R |= 0xe0;
//	GPIO_PORTA_DEN_R |=0xe0;
	GPIO_PORTB_DIR_R |= 0xff;
	GPIO_PORTB_DEN_R |=0xff;
//	GPIO_PORTA_PCTL_R &=~ 0xffffffff;
	GPIO_PORTB_PCTL_R &=~ 0xffffffff;
//	GPIO_PORTA_LOCK_R=0x4C4F434B;
	GPIO_PORTB_LOCK_R=0x4C4F434B;
	
	
	lcd_4bits_cmd(0x28);
	lcd_4bits_cmd(0x06);
	lcd_4bits_cmd(0x01);
	lcd_4bits_cmd(0x0f);
  
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		if (i==16)
		{
			lcd_4bits_cmd(0xc0);
		}
		lcd_4bits_data(str[i]);  /* Call LCD data write */
		
		}
				
}
