int beef_cooking(){
	char value,weight;
	int time;
L2:	LCD_String("Beef Weight?    (1 to 9)");\\print beef weight
		delay(2000);
	 lcd_4bits_cmd(0x1);
	 lcd_4bits_cmd(0x80);
	 while(1){
		 do{
	
	 value = get_key();

}while(value==0);
	
    lcd_4bits_data(value);
		delay(1000);
    lcd_4bits_cmd(0x1);
		weight = value;
		 
	weight = weight -48;
	if((weight >0) && (weight <10) && (weight %2 ==0)){
time = weight * 50; \\calculating time  to be displayed 
	 timer(time);
	 }
	else if ((weight >0) && (weight <10) && (weight %2 !=0)){
		time = (weight-1) * 50 + 30;
			timer(time);
 }
	else {
			LCD_String("        Err");
		  delay(2000);
	   lcd_4bits_cmd(0x1);
	   lcd_4bits_cmd(0x80);
		goto L2;
	}
}
	 return(0);
}
