int other_cooking(){
	int i;
	char value; 
	char time[30];
	int countdown;
		LCD_String("Cooking time?   (1 to 30)");
		delay_milli(1000);
	 lcd_4bits_cmd(0x1);
	 lcd_4bits_cmd(0x80);
	 LCD_String("     ");
	 while(1){
	for(i=0;i<20;i++){
	do{
	
		 value = get_key();

}while(value==0);
	if (value != '*'){
		lcd_4bits_data(value);
		 delay_milli(500);
	  time[i] = value;
	}
	else {
		lcd_4bits_cmd(0x1);
	 delay_milli(100);
		break;

	}
}
	countdown = atoi(time);
	timer(countdown);
break;
}
	 return(0);
}
