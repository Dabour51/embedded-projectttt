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
