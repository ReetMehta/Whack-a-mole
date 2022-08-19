#include <at89c5131.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions

//sbit LED=P1^7;


unsigned char display_line1[9]={'*','*','*','*','*','*','*','*','\0'};		//string array for saving mole to present
unsigned char display_line2[9]={'*','*','*','*','*','*','*','*','\0'};		//string array for saving mole to present

char high_sc[3]={0,0,'\0'};							//string array for saving high score
char sc[3]={0,0,'\0'};									//string array for saving score of a game
bit time_up = 0;												//set to 1 when 10s have passed
unsigned int high_score=0;							//stores high score
unsigned int score=0;										//stores score
unsigned int count=0;										//Counts number of Timer 0 interrupts to make a 10s delay							
unsigned int num=3;										//stores state of LSFR
unsigned int m=3;											//stores position of m of mole



void lcd_mole(void)											//displays the stars and mole n lcd
{
	lcd_cmd(0x01);
	
	lcd_cmd(0x80);		
	lcd_write_string(display_line1);
	
	lcd_cmd(0xC0);
	lcd_write_string(display_line2);
	
	
}

void change(void)												//calcuates the new state of LSFR and new value of m
{
	unsigned int b0,b3;
	m=num;
	b0 = num%2;
	b3 = num/8;
	num=num/2;
	num= num+8*(b0^b3);
	
	m=(num+m)%16;
}

void newmole(void){											//replaces old m by *, calculates new m and prints the new m
	if(m<8)
	{
		display_line1[m]='*';
	}
	else
	{
		display_line2[(m-8)]='*';
	}
	
	change();
	
	
	if(m<8)
	{
		display_line1[m]='m';
	}
	else
	{
		display_line2[(m-8)]='m';
	}
	
	
	lcd_mole();
}

void inter(void)															//Timer 0 interrupt function
{
	if(count==305)	
		{
			time_up=1;
			t_up=1;
			ET0=0;
			//lcd_cmd(0xC0);		
			//lcd_write_string("0");
			
		}
	else{count++; TF0=0;}
}

void counter(void) interrupt 1											//Timer 0 Interrupt
{
	inter();
}


void lcd_score(void)																//Displays score and high score
{
	lcd_cmd(0x01);
	
	lcd_cmd(0x80);		
	lcd_write_string("Score:        ");
	int_to_string(score,sc);
	lcd_write_string(sc);
	
	
	lcd_cmd(0xC0);
	lcd_write_string("High Score:   ");
	int_to_string(high_score,high_sc);
	lcd_write_string(high_sc);
}

void start_timer()																		//Starts the timer 0 for 10s
{
	TMOD|= 0x01;
	TMOD&= 0xF1;

	TH0= 0x00;
	TL0= 0x00;
	
	count=0;
	
	TR0=1;
	
	EA=1;
	ET0=1;
}


//Main function
void main(void)
{

	
	unsigned char ch=0;
	

	
	//Call initialization functions
	lcd_init();
	uart_init();
	
	high_score=0;
	
	if(m<8)
	{
		display_line1[m]='m';
	}
else
	{
		display_line2[(m-8)]='m';
	}
	
	
	
	while(1)
	{
		//Print Get Ready msg
		 lcd_cmd(0x01);
		lcd_cmd(0x80);		
		lcd_write_string("Get Ready");
		msdelay(2000);
		
		//Print all *s
		lcd_cmd(0x01);
		lcd_cmd(0x80);		
		lcd_write_string("********");
		lcd_cmd(0xC0);
		lcd_write_string("********");
		transmit_string("*\r\n");
		msdelay(3000);
		
		
		//initialise variables
		score=0;
		
		time_up=0; //set to 1 when the 10s timer is up
		t_up=0;
		
		//start 10s timer
		start_timer();
		
		//shows the mole on lcd
		lcd_mole();
		
		
		rx_complete=0; //set to 0 to avoid any previous key press state stored in the SBUF to interfere
		
		while(!time_up)
		
		{
				
				//transmit_string("ch\r\n");
				//Receive a character
				ch = receive_char();
				
				//Decide which test function to run based on character sent
				
				switch(ch)
				{
					case 'q':if(m==0){
										newmole();									//new mole appears if the correct key is pressed
										score+=1;
						//transmit_string("q\r\n");
									}
									 break;
					
					case 'w':if(m==1){
										newmole();
										score+=1;
						//transmit_string("w\r\n");
									}
									 break;
					
					case 'e':if(m==2){
										newmole();
										score+=1;
						//transmit_string("e\r\n");
									}
									 break;
						
					case 'r':if(m==3){
										newmole();
										score+=1;
						//transmit_string("r\r\n");
									}
									 break;
						
					case 't':if(m==4){
										newmole();
										score+=1;
						//transmit_string("t\r\n");
									}
									 break; 
						
					case 'y':if(m==5){
										newmole();
										score+=1;
						//transmit_string("y\r\n");
									}
									 break;
						
					case 'u':if(m==6){
										newmole();
										score+=1;
						//transmit_string("u\r\n");
									}
									 break;
						
					case 'i':if(m==7){
										newmole();
										score+=1;
						//transmit_string("i\r\n");
									}
									 break;
						
					case 'a':if(m==8){
										newmole();
										score+=1;
						//transmit_string("a\r\n");
									}
									 break;
						
					case 's':if(m==9){
										newmole();
										score+=1;
						//transmit_string("s\r\n");
									}
									 break;
						
					case 'd':if(m==10){
										newmole();
										score+=1;
						//transmit_string("d\r\n");
									}
									 break;
						
					case 'f':if(m==11){
										newmole();
										score+=1;
						//transmit_string("f\r\n");
									}
									 break;
						
					case 'g':if(m==12){
										newmole();
										score+=1;
						//transmit_string("g\r\n");
									}
									 break;
						
					case 'h':if(m==13){
										newmole();
										score+=1;
						//transmit_string("h\r\n");
									}
									 break;
						
					case 'j':if(m==14){
										newmole();
										score+=1;
						//transmit_string("j\r\n");
									}
									 break;
						
					case 'k':if(m==15){
										newmole();
										score+=1;
						//transmit_string("k\r\n");
									}
									 break;
						
					
								
					default: //transmit_string("z\r\n");
						break;
					
				}
				rx_complete=0;
				msdelay(2);
				//Testing lines:
				//if(a==1){transmit_string("1\r\n");}
				//if(b==1){transmit_string("2\r\n");}
				//if(c==1){transmit_string("3\r\n");}
				//if(d==1){transmit_string("4\r\n");}
				//a=0;b=0;c=0;d=0;
				
		}
		
		msdelay(10);
		if(high_score<score){ high_score=score;}							//Update high score if required
		
		time_up = 0;
		t_up=0;
		
		
		lcd_score();																					//Display score and highscore
		msdelay(3000);
	}
}
