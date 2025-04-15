#include<lpc17xx.h>

unsigned int v1,x,i;
unsigned char row, var, flag;
unsigned long int i, var1, temp, temp1, temp2, temp3, key,time;
unsigned char SCAN_CODE[16] = {0x11,0x21,0x41,0x81,
			       0x12,0x22,0x42,0x82,
			       0x14,0x24,0x44,0x84,
			       0x18,0x28,0x48,0x88};
unsigned char ASCII_CODE[16] = {'B','T','L','\0',
				'0','1','2','3',
				'4','5','6','7',
				'8','9','\0','='};

void inittime0(){
		LPC_TIM0->CTCR = 0x0;
		LPC_TIM0->TCR = 0x2;
		LPC_TIM0->PR = 2999;
}

void delay(int milliseconds){
		LPC_TIM0->TCR = 0x2;
		LPC_TIM0->TCR = 0x1;
		while(LPC_TIM0->TC < milliseconds);
		LPC_TIM0->TCR = 0x0;
}

void clockwise(){
	v1=0x8;
	for(i=0;i<4;i++){
		v1=v1<<1;
		LPC_GPIO0->FIOPIN=v1;
		delay(10000);
	}
}

void anti_clockwise(){
	v1=0x100;
	for(i=0;i<4;i++){
		v1=v1>>1;
		LPC_GPIO0->FIOPIN=v1;
		delay(10000);
	}
}

void Match(int milliseconds)
{
    LPC_TIM0->MR0=milliseconds;
    LPC_TIM0->MCR=2;
    LPC_TIM0->EMR=0x20;
    LPC_TIM0->TCR=0x2;
    LPC_TIM0->TCR=0x1;
    while(!(LPC_TIM0->EMR&1));
    LPC_TIM0->TCR=0x0;
    for(i=0;i<400;i++)
      clockwise();
}


void switch()
{
	while(1){
		x = LPC_GPIO2->FIOPIN>>12;
		x&=1;
		if (x==1)
			clockwise();
		else if (x==0)
			anti_clockwise();
	}
}

void scan(void){
		temp3 = LPC_GPIO0->FIOPIN;
		temp3 &= (0XF<<15); 
		if(temp3 != 0x00000000)
		{
				flag = 1;
				temp3 >>= 11; //15-4
				temp >>= 19; 
				key = temp3|temp; 
		}
}

void settime()
{
       LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28; //LCD
       clear_ports();
		delay(3200);
		lcd_init();
		lcd_comdata(0x80, 0); //point to first line of LCD
		delay(800);
		lcd_puts(&Msg1[0]); //display the message
		while(1)
				{
						for(row=2;row<5;row++)
						{
								if(row == 2)
										var1 = 1<<20;
								else if(row == 3)
										var1 = 1<<21;
								else if(row == 4)
										var1 = 1<<22;
								temp = var1;
								LPC_GPIO2->FIOCLR = 0x00003C00; //first clear the
								LPC_GPIO2->FIOSET = var1; //enabling the row
								flag = 0;
								scan(); //scan if any key pressed in the enabled row
								if(flag == 1)
										break;
						} //end for
						if(flag == 1)
						break;
				} //2nd while(1)
				for(i=0;i<16;i++) //get the ascii code for display
				{
						if(key == SCAN_CODE[i])
						{
								key = ASCII_CODE[i];
								break;
						} //end if(key == SCAN_CODE[i])
				}//end for(i=0;i<16;i++)
		lcd_puts(&key);
                key=key-48;
                time=key*3600*1000;
                Match(time);
		
}
				
								
int main(void){
                LPC_PINCON->PINSEL0=0X0;  //p0.4 to p0.7
	        LPC_PINCON->PINSEL4=0X0;  //SWITCH P2.12
	        LPC_GPIO2->FIODIR=0<<12;
		LPC_GPIO0->FIODIR |= 0xf<<4|0xf<<19|0x0<<15; 					//made output P0.19 to P0.22 (rows)
                                                                                       //made input P0.15 to P0.18(cols)
		while(1){
				while(1){
						var1 = 1<<19;
						temp = var1;
						LPC_GPIO0->FIOCLR = 0xF<<19; 
						LPC_GPIO0->FIOSET = var1; 			
						flag = 0;
						scan(); 													
						if(flag == 1)		break;
				        } 					
				for(i=0;i<4;i++){
						if(key == SCAN_CODE[i])
                                                   {
								key = ASCII_CODE[i];
								break;
					       	   }
				                }										
			}
              switch(key)
              {
                 case 'B': delay(1000);
                           switch();
                           break;
                 
                 case 'T': delay(1000);
                           settime();
                           break;
             }
}