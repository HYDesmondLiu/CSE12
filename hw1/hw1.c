/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        Janurary 8, 2015
                                                        cs12xbo
                                Assignment One

File Name:      hw1.c
Description:    This program tests functions to display output strings and 
                numbers. 
****************************************************************************/
#include <stdio.h>

#define COUNT 8		/* number of hex digits to display */
#define DECIMAL 10	/* to indicate base 10 */
#define HEX 16		/* to indicate base 16 */
#define BUFSIZE 32      
/* array used for ASCII conversion */
const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int SEVEN = 7; /*So that the array will have seven empty spaces */
const int HEXCOUNTER = 0; /*counter for the number hex digits */

/*--------------------------------------------------------------------------
Function Name:         writeline
Purpose:               Prints out a string.
Description:           Each character of the message/string is stored into 
											 an array and increments until the function hits the 
											 NULL character. 
Input:                 message: A string to print out.
		                   stream: Where to display, likely stdout or stderr. 
Result:                returns 0
--------------------------------------------------------------------------*/
int writeline (const char * message, FILE * stream) {
  int index = 0; /*initializing index to zero. */
	/*a while loop that prints out the character in the stored array
	if the message index does not equal zero. */
  while (message[index] != 0) {
    fputc (message[index], stream); /*prints out the character that is stored
		in the array. */
    index++; /*incrementing the index every time the while condition is met. */
  }
  return 0; 
}

/*--------------------------------------------------------------------------
Function Name:         baseout
Purpose:               Takes in a positive number and displays in a given base.
Description:           Continually modes the number with the base, that's passed
                       through, so that a single digit will be created, which 
											 then will be stored into the character array, and  
											 the number is also continually divided by the base 
											 creating a new number until the do while condition is 
											 met. Since, each character is stored into the character
											 array backwards, I decremented the array so that  
											 the characters will print out the correct way. 
Input:                 int number: Numeric value to be displayed.
		                   int base: Base to used to display number.
		                   FILE * stream: Where to display, likely stdout or stderr
Result:                Nothing is returned. 
--------------------------------------------------------------------------*/
void baseout (int number, int base, FILE * stream) {
  int index = 0; /*initializing index to zero. */
  int remainder = 0; /*initializing remainder to zero. */
  char array[] = {0,0,0,0,0,0,0,0}; /*initializing the character array to have 
	eight spaces.*/
	/*If the base is a HEX, the array will start off by having
  zeros. */
  if(base == HEX) {
    array[SEVEN] = digits[HEXCOUNTER];
  }
  /*Will run this while loop at least once. */
	do {
    remainder = number % base; /*Remainder = the single digit, created by 
		moding number with the base. */
    array[index] = digits[remainder]; /*Storing that single digit character
		into the character array replacing the zeros if base equals hex. */
    number = number / base; /*A new number will be created by dividing the 
		old number by the base. */
    index++; /*Increase the index storing the single digit character
  	into a new number. */
  }   while(number > 0);/* A while loop that runs the function continually if 
	the number is bigger than zero. */
  while(index >= 0) {
    fputc(array[index], stream); /*Prints out the single digit characters*/
    index--; /* decrement the index. */
  }
}


/*--------------------------------------------------------------------------
Function Name:         decount
Purpose:               Takes in a positive number and displays it in decimal.
Description:           Calls the baseout function with new parameters being 
                       passed to it. 
Input:                 number: positive numeric value to be displayed. 
		                   stream: Where to display, likely stdout or stderr.
Result:                Nothing is returned.
--------------------------------------------------------------------------*/
void decout (unsigned int number, FILE * stream) {
  baseout(number, DECIMAL, stream); /* Calls the baseout function 
	placing a number and a base of decimal */
}


/*--------------------------------------------------------------------------
Function Name:         hexout
Purpose:               Prints a number in base 16 to the parameter FILE stream
Description:           Goal is achieved via delegating to the baseout function.
Input:                 number:  the number to display.
                       stream:  where to display, likely stdout or stderr.
Result:                Number in base 16 is displayed.
                       No return value.
--------------------------------------------------------------------------*/
void hexout (unsigned int number, FILE * stream) {
  /* Output "0x" for hexidecimal. */
  writeline ("0x", stream);
  baseout (number, HEX, stream);
}


/*--------------------------------------------------------------------------
Function Name:         newLine
Purpose:               Prints out a newline character
Description:           A new line character is created. 
Input:                 stream: where to display, likely stdout or stderr. 
Result:                No return value. 
--------------------------------------------------------------------------*/
void newline (FILE * stream) {
  /* prints out a new line. */
	fputc('\n', stream);
}

int main (int argc, char *const* argv) {
  writeline ("Hello World", stdout);
  fprintf (stderr, "Zdravei Sviat\n");
  newline(stdout);
  decout (123, stdout);
  newline(stdout); 
  decout (0, stdout);
  newline(stdout);
  hexout (0xFEEDDAD, stdout);
  newline(stdout);
  return 0;
}
