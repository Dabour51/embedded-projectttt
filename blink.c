void blink_led(){
GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;// change the light on or off
}
