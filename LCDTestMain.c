#include "../inc/tm4c123gh6pm.h"
#include "SSD2119.h"
#include "PLL.h"
#include "stdint.h"
#include "random.h"
#include "LCDTests.h"
#include "art.h"







int main(void){unsigned long i=0;
  // Set the clocking to run at 80MHz from the PLL.
  PLL_Init(Bus80MHz);

    // Initialize LCD
  LCD_Init();
    
 
    // Initialize RNG
    Random_Init(121213);

    // Initialize touchscreen GPIO
    Touch_Init();
		//LCD_DrawBMP(Background, 0, 0);
    LCD_DrawBMP(0, 0, Background, 320, 240);
		LCD_DrawBMP(10, 10, bird, 19, 15);
		//LCD_DrawRect(0, 0, 50, 60, 0x0504);
    for(;;) {
        
        // TO PLAY WITH THESE, EMPTY THE SYSTICK OF TIMED
        // STUFF AND UNCOMMENT ONE TEST AT A TIME
        // - SOME MAY BE BROKEN NOW
        
        //This file was modified to make a short animated
        //demonstration of the LCD driver.  Each test is
        //shown at least briefly, then the best footage
        //will be selected in post-production.
        //NOTE: To return this file to its previous
        //condition, un-comment the following lines in the
        //SysTick_Handler:
        //touchDebug();
        //LCD_DrawBMP(0, 0, Background, 320, 240);
        //Beginning of animated demonstration
				/*
        for(i=0; i<1000; i=i+1){
          RandomRectangles();
        }
        LCD_ColorFill(convertColor(0, 0, 255));
				*/
				/*
        for(i=0; i<1250; i=i+1){
          MovingColorBars();
        }
				*/
				/*
        for(i=0; i<15; i=i+1){
          LineSpin();
        }
				
        LCD_ColorFill(convertColor(0, 0, 0));
        for(i=0; i<2000; i=i+1){
          printfTest();
        }
        for(i=0; i<250; i=i+1){
          RandomCircle();
        }
        for(i=0; i<6500; i=i+1){
          Random4BPPTestSprite();
        }
				*/
        //End of animated demonstration
        //PrintAsciiChars();
        //BlastChars();
        //TestStringOutput();
        //RandomRectangles();
        //MovingColorBars();
        //RandomColorFill();
        //BWWaitFill();
        //LineSpin();
        //printfTest();
        //charTest();
        //RandomCircle();
        //Random4BPPTestSprite();

    }
    
}


