void timer(int x){
	int i,minutes, minutes1, minutes2, seconds, seconds1, seconds2, maxSeconds;
	
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
			LCD_String("     ");
			delay(10);
			lcd_4bits_data(minutes1+48);
		  delay(10);
			lcd_4bits_data(minutes2+48);
		  delay(10);
			lcd_4bits_data(':');
		  delay(10);
			lcd_4bits_data(seconds1+48);
		  delay(10);
			lcd_4bits_data(seconds2+48);
		  delay(10);
			 //while(switchoff=0);
			 // delay_milli(1000);
			  delay(1000);
		  	lcd_4bits_cmd(0x1);
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
			
		}