int main()
{
	char choice;
	lcd_init();
  keypad_init ();
	lcd_4bits_cmd(0x1);
	lcd_4bits_cmd(0x80);
  
	
L1:	LCD_String("Enter a choice  to begin cooking");
 delay(3000);
do{
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 choice = get_key();
		 delay(10);
	}
	while (choice == 0);
	while(1){	
switch(choice){
case 'A':
	delay(500);
popcorn_cooking();
delay(2000);
break;
case 'B':
	delay(500);
beef_cooking();
delay(2000);
break;
case 'C':
	delay(500);
chicken_cooking();
delay(2000);
break;
case 'D':
other_cooking();
delay(3000);
break;
default:
{
 LCD_String("Invalid input");
delay(2000);
lcd_4bits_cmd(0x1);
lcd_4bits_cmd(0x80);
goto L1; 
}
}
break;
}
	}

