void other_cooking(){
 int i,sw12;
 char value;
 char time[30];
char cmds[4] ={0xc4,0xc3,0xc1,0xc0};
 int countdown;
 L3: LCD_String("Cooking time? ");
 lcd_4bits_cmd(0xC0);
 LCD_String("00:00");
 while(1){
 for(i=0;i<4;i++){
 do{
 delay(200);
 value = get_key();
 sw12 = sw12_input();
}while(value==0 & (sw12 == 0x11));
 if ((value >='0') && (value <= '9')){
 lcd_4bits_cmd(cmds[0]);
 lcd_4bits_data(value);
 time[i] = value;
 if(i==1){
 lcd_4bits_cmd(cmds[i]);
 lcd_4bits_data(time[i-1]);
 }
 if(i==2){
 lcd_4bits_cmd(cmds[i]);
 lcd_4bits_data(time[i-2]);
lcd_4bits_cmd(cmds[i-1]);
 lcd_4bits_data(time[i-1]);
 }
 if(i==3){
 lcd_4bits_cmd(cmds[i]);
 lcd_4bits_data(time[i-3]);
 lcd_4bits_cmd(cmds[i-1]);
 lcd_4bits_data(time[i-2]);
lcd_4bits_cmd(cmds[i-2]);
lcd_4bits_data(time[i-1]);
 }
 }
 else if ((sw12 & 0x10) == 0x00 ){
 lcd_4bits_cmd(0x1);
 lcd_4bits_cmd(0x80);
 goto L3;
 }
 else if ((sw12 & 0x01) == 0x00){
 lcd_4bits_cmd(0x1);
 delay(100);
if(countdown > 3000){
	lcd_4bits_cmd(0x1);
 delay(100);
 LCD_String(" Err");
	lcd_4bits_cmd(0xc0);
	LCD_String("more than 30mins");
 delay(2000);
 lcd_4bits_cmd(0x1);
 goto L3;
	}
	else{
 timer(countdown);
 return;
	}
}
 else if((value < '0') | (value > '9')){
 lcd_4bits_cmd(0x1);
 delay(100);
 LCD_String(" Err");
 delay(2000);
 lcd_4bits_cmd(0x1);
 goto L3;
}
}
 }
}
