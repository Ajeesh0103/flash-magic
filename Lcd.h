
#ifdef DELAY
/*************************************************************************************************************************
* Function    :  delay
*
* Description : command for delay
*               
* Parameter   : x
*************************************************************************************************************************/
int delay(unsigned int x)
 {
	x=x*12000;
	while(x!=0){
	x--;
	}
	return 0;
 }
#endif

#ifdef LCD
#define RS  0x00020000                 	/*   17th pin RS	 														*/
#define RW  0X00040000					/*   18th pin R/W    														*/
#define EN  0X00080000					/*   19th pin EN	   														*/
#define CLR	0X00FE0000


/*************************************************************************************************************************
* Function    :  LCD_Command
*
* Description : command for lcd
*               
* Parameter   : command
************************************************************************************************************************/

void lcd_command(char command)
 {
    int Temp;
    
	IO1CLR = CLR;		 				/* Clear ALL 16-23 Pins 													*/
 	IO1SET = EN;		 				/* SET   19th Pin [EN]  													*/
 	IO1CLR = RS;		 				/* Clear 17th Pin [RS] 														*/
 	IO1CLR = RW;		 				/* Clear 18th Pin [R/W] 													*/
 	Temp	= (command & 0xF0) << 16;   /* Higher Nibble Extracting 0X30 [3-High] & [4-7] Shifted To [20-23] 		*/
 	IO1SET = IO1SET | Temp;			   	/* 0X00080000 | 0X00300000[Shifted] = 0X00380000[Only '3' Is in [20-23]pins */
 	delay(2);						  	/* Minimum DelayTime   					 									*/
 	IO1CLR = EN;					 	/* ENABLE High-Low Transition												*/

 }

/*************************************************************************************************************************
* Function    :  LCD_Command1
*
* Description : command for lcd
*               
* Parameter   : command1
*************************************************************************************************************************/

void lcd_command1(char command1)
 {
    int Temp;
    IO1CLR = CLR;		 				/* Clear ALL 16-23 Pins 													*/
 	IO1SET = EN;		 				/* SET   19th Pin [EN]  													*/
 	IO1CLR = RS;		 				/* Clear 17th Pin [RS] 														*/
 	IO1CLR = RW;		 				/* Clear 18th Pin [R/W] 													*/
 	Temp	= (command1 & 0xF0) << 16;  /* Higher Nibble Extracting 0X30 [3-High] & [4-7] Shifted To [20-23] 		*/
 	IO1SET = IO1SET | Temp;			   	/* 0X00080000 | 0X00300000[Shifted] = 0X00380000[Only '3' Is in [20-23]pins */
 	delay(2);						  	/* Minimum DelayTime   					 									*/
 	IO1CLR = EN;					 	/* ENABLE High-Low Transition												*/
 	IO1CLR = CLR;		 				/* Clear ALL 16-23 Pins 													*/
 	IO1SET = EN;		 		   		/* SET   19th Pin [EN]  													*/
 	IO1CLR = RW;		 		  		/* Clear 17th Pin  [RS] 													*/
 	IO1CLR = RS;		 		 		/* Clear 18th Pin [R/W] 													*/
 	Temp    = (command1 & 0x0F) << 20;	/* Lower Nibble [0-3] Shifted To [20-23] & [0-3] Shifted To [20-23]  		*/
 	IO1SET = IO1SET | Temp;				/* 0X00080000 | 0X00800000[Shifted] = 0X00880000[Only '8' Is in [20-23]pins */
 	delay(2);     						/* Minimum DelayTime   					 									*/
 	IO1CLR = EN;   						/* ENABLE High-Low Transition												*/

 }
 /*************************************************************************************************************************
* Function    :  LCD_Data
*
* Description : display command for lcd   
*               
* Parameter   : data
*************************************************************************************************************************/
void lcd_data(char data)  
 {
    int Temp;
	IO1CLR = CLR;		 				/* Clear ALL 16-23 Pins 													*/
    IO1SET = EN;		 				/* SET   19th Pin [EN]  													*/
	IO1CLR = RW;		 				/* Clear 18th Pin [R/W] 													*/
	IO1SET = RS;		 				/* Clear 17th Pin [RS] 														*/
	Temp   = (data & 0xF0) << 16;  		/* Higher Nibble Extracting 0X30 [3-High] & [4-7] Shifted To [20-23] 		*/
	IO1SET = IO1SET | Temp;			   	/* 0X00080000 | 0X00300000[Shifted] = 0X00380000[Only '3' Is in [20-23]pins */
	delay(2);						  	/* Minimum DelayTime   					 									*/
	IO1CLR = EN;					 	/* ENABLE High-Low Transition												*/

	IO1CLR = CLR;		 				/* Clear ALL 16-23 Pins 													*/
  	IO1SET = EN;		 		   		/* SET   19th Pin [EN]  													*/
	IO1CLR = RW;		 				/* Clear 18th Pin [R/W] 													*/
	IO1SET = RS;		 		  		/* Clear 17th Pin  [RS] 													*/
	Temp	   = (data & 0x0F)<<20;		/* Lower Nibble [0-3] Shifted To [20-23] & [0-3] Shifted To [20-23]  		*/
	IO1SET = IO1SET | Temp;				/* 0X00080000 | 0X00800000[Shifted] = 0X00880000[Only '8' Is in [20-23]pins */
	delay(2);     						/* Minimum DelayTime   					 									*/
	IO1CLR = EN;   						/* ENABLE High-Low Transition												*/
 }
/*************************************************************************************************************************
* Function    :  lCD_string
*
* Description : display group of data    
*               
* Parameter   : dat
*************************************************************************************************************************/
void lCD_string(unsigned char *dat)
 {
  	while(*dat!='\0') 
    {
	       lcd_data(*dat);
		   dat++;
	}
 }

 /*************************************************************************************************************************
* Function    :  Lcd_init
*
* Description : Funtion for initialize LCD to display data    
*               
* Parameter   : None
*************************************************************************************************************************/

void Lcd_init(void)
 {
 	delay(15);							/* Delay (1.5ms) 			 												*/
	lcd_command(0x30);					/* Single line enable(2X16)													*/
	delay(10);							/* Delay (10us)			   													*/
	lcd_command(0x30);					/* Single line enable(2X16)  												*/
	delay(5);							/* Delay (0.5ms) 			 												*/
	lcd_command(0x30);				   	/* Single line enable(2X16) 												*/
	lcd_command(0x20); 				  	/* 4-bit Mode Enable		   												*/
	lcd_command1(0x28);				 	/* Double line enable (2X16) 												*/
	lcd_command1(0x01);					/* Clear LCD				 												*/
	lcd_command1(0x06);			   		/* Automatic increment 	    												*/
	lcd_command1(0x0C);		 	  		/* Cursor OFF /Display ON    												*/
 }
 #endif

