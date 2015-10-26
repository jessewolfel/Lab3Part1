/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include<string.h>
#include "lcd.h"
#include "timer.h"

#define LCD_DATA7 LATEbits.LATE7
#define LCD_DATA6 LATEbits.LATE5
#define LCD_DATA5 LATEbits.LATE3
#define LCD_DATA4 LATEbits.LATE1
#define LCD_RS LATDbits.LATD5
#define LCD_E LATDbits.LATD11

#define TRIS_D7 TRISEbits.TRISE7
#define TRIS_D6 TRISEbits.TRISE5
#define TRIS_D5 TRISEbits.TRISE3
#define TRIS_D4 TRISEbits.TRISE1
#define TRIS_RS TRISDbits.TRISD5
#define TRIS_E  TRISDbits.TRISD11

#define OUTPUT 0
#define INPUT 1
#define ENABLED 1
#define DISABLED 0
/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    LCD_DATA7 = word >> 3;
    LCD_DATA6 = (word << 5) >> 7;
    LCD_DATA5 = (word << 6) >> 7;
    LCD_DATA4 = (word << 7) >> 7;
    LCD_RS = commandType;
    
    LCD_E = ENABLED; //Enable write
    delayUs(1);
    LCD_E = DISABLED;
    delayUs(delayAfter); //Execution Time delay
    

    
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //Writes MSB
    writeFourBits(word >> 4, commandType, 1);
    //Writes LSB
    writeFourBits((word << 4) >> 4, commandType, delayAfter);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    writeLCD(c, ENABLED, 51);
}
/*Initialize the LCD
 */
void initLCD(void) {
    
    //set data bus to output
    TRIS_D7 = OUTPUT;
    TRIS_D6 = OUTPUT;
    TRIS_D5 = OUTPUT;
    TRIS_D4 = OUTPUT;
    
    //set command pins to output
    TRIS_RS = OUTPUT;
    TRIS_E = OUTPUT;
    
    //ensure at least 16ms has passed since the device has turned on
    delayUs(4000);
    delayUs(4000);
    delayUs(4000);
    delayUs(4000);
    //4-bit Initialization Process
    writeFourBits(0x03, 0, 4500);
    writeFourBits(0x03, 0, 110);
    writeFourBits(0x03, 0, 50);
    writeFourBits(0x02, 0, 50);

    // Function Set
    writeLCD(0x28, 0, 50);
    //Display Off
    writeLCD(0x08, 0, 50);
    //Clear Display
    clearLCD();
    // Set Increment Display, No Shift (i.e. cursor move)
    writeLCD(0x06, 0, 50);
    // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    writeLCD(0x0C, 0, 50);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    int i;
    for(i = 0; i < strlen(s); i++) {
        printCharLCD(s[i]); //unsure if pointers are correct
    }
}

/*
 * Clear the display.
 */
void clearLCD(){
    unsigned char word = 0x01;
    writeLCD(word, 0, 1400);
    moveCursorLCD('1','1');
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    unsigned char address;
    address = (y-1)*0x40+(x-1);
    address = address + 0x80;
    writeLCD(address, 0, 44);
}
/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    //initLCD();
    clearLCD();
    moveCursorLCD(1,1);
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    moveCursorLCD(1,1);
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}