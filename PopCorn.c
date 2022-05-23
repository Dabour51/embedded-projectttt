void popcorn_cooking(){
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 while(1){
 LCD_String(" Popcorn");
 //button12_in = sw12_input();
 while(sw12_input() & 0x10 != 0x00);
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 delay(10);
 GPIO_PORTF_DATA_R |= 0x11;
 timer(100);
 break;
 }
 }
