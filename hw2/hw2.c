/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 2015
                                                        January 10, 2015
                                                        cs12xbo
                                Assignment Two

File Name:      hw2.c
Description:    This program reads strings and integers from the user,
                processes them, and prints them back to the user.  Program
                terminates when user enters ^D.  At termination, program
                outputs sizes of various types of C/C++ pre defined types.

****************************************************************************/

/* declare fputc/fgetc */
#include <stdio.h>
#include <getopt.h>

/* define some program-wide constants */
#define ASCII_ZERO '0'
#define COUNT ((int) (sizeof (int) << 1))
#define ERROR -1
#define FALSE 0
#define MAXLENGTH 80
#define OFFSET ('a' - 'A')
#define SPACE ' '
#define TRUE 1

#define DECIMAL 10
#define HEX 16

/* define the keyword "NULL" as 0 */
#ifdef NULL
#undef NULL
#endif
#define NULL 0

/* declarations for functions defined in this file */
void baseout (int number, int base, FILE *stream);
void clrbuf (int);
int decin (void);
void decout (unsigned int, FILE *);
void digiterror (int, int *, const char *);
int getaline (char *, int);
void hexout (unsigned int, FILE *);
void newline (FILE *);
int writeline (const char *, FILE *);

/* array for input checking and for output */
const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int SEVEN = 7; /* to create an arry with 7 spaces. */
const int HEXCOUNTER = 0; /* counter for the number hex digits */
/* messages */
const char CAUSED_OVERFLOW[] =  " caused overflow!!!\n";
const char DIGIT_STRING[] = "digit ";
const char REENTER_NUMBER[] = "\nPlease reenter number: ";
const char OUT_OF_RANGE[] = " out of range!!!\n";

/* debug messages */
const char DEBUG_GETALINE[] =
        "[*DEBUG:  The length of the string just entered is ";
const char DEBUG_WRITELINE[] =
        "\n[*DEBUG:  The length of the string displayed is ";
static int debug_on = FALSE;

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
Result:                Nothing is returned. Will print out different character
		       depending on the paramenters passed. 
--------------------------------------------------------------------------*/
void baseout (int number, int base, FILE * stream) {
	int index = 0; /*initializing index to zero. */
	int remainder = 0; /*initializing remainder to zero. */
	char array[] = {0,0,0,0,0,0,0,0}; /*initializing the character array to 
	have eight spaces.*/
	/*If the base is a HEX, the array will start off by having
	zeros. */
	if (number < 0) {
		number = number * -1;
	}
	if(base == HEX) {
		array[SEVEN] = digits[HEXCOUNTER];
	}
	/*Since this is a do while loop this will run at least once. */
	do {
		remainder = number % base; /*Remainder = the single digit, 
		created by moding number with the base. */
		array[index] = digits[remainder]; /*Storing that single digit 
		character into the character array replacing the zeros 
		if base equals hex. */
		number = number / base; /*A new number will be created by 
		dividing the old number by the base. */
		index++; /*Increase the index storing the single digit character
		into a new storage in the array. */
	}   while(number > 0);/* A while loop that runs the function continually
	if the number is bigger than zero. */
	while(index > 0) { /* continually runs if the index number is bigger 
		than zero */
		index--; /* decrement the index so that the characters will 
		print out in the correct order. */
		fputc(array[index], stream); /*Prints out the single digit 
		characters*/
	}
}

/*-------------------------------------------------------------------------- 
Function Name:          clrbuf 
Purpose:                When called, this function will clear stdin. 
Description:            This function checks to see if the incoming 
                        parameter is already '\n' indicating that stdin 
                        is already clear.  If stdin is already clear, this 
                        function does nothing.  Otherwise, this function 
                        calls "fgetc" in a loop until stdin is clear. 
Input:                  character:  the most recent character received from a 
                                previous call to fgetc. 
Result:                 stdin cleared.  Nothing returned. 
--------------------------------------------------------------------------*/  
void clrbuf (int character) {  
	while (character != '\n') { /*continually runs until the <Enter> 
		character is hit */
		character = fgetc(stdin); /*the character takes in the remainin
		characters of the words that the user inputted, but does not 
		display them. */
	}
}


/*--------------------------------------------------------------------------
Function Name:          decin
Purpose:                This function accepts integer input from from the user.
Description:            This function processes user input in a loop that ends
                        when the user enters either a valid number or EOF.
                        If EOF is entered, EOF is returned.  Otherwise each
                        character entered is checked to verify that it is
                        numeric.  Non-numeric input is identified, the user
                        is notified, reprompted, and the loop begins again.
                        Once the input is verified to be valid, a series
                        of multiplication by 10 and addition can take
                        place to convert the ASCII characters entered into
                        a numeric quantity.
Input:                  None.
Result:                 The number entered or EOF.
--------------------------------------------------------------------------*/
int decin (void) {
	/*int sum = 0;
	int digit = 0;
	int index = 0;
	int old = 0; 
	int TEN = 10; 
	int character = fgetc(stdin);
	while (character != '\n') {
		if (character == EOF) {
			return EOF;
		}
		if (character < '0' || character > '9') {
			digiterror(character, sum, " out of range!!!\n");
			sum = decin();
			break;
		}
		old = sum;
		digit = character - '0';
		index++;
		sum = sum * TEN + digit;
		if ((sum - digit) / TEN != old) {
			digiterror(character, CAUSED_OVERFLOW);
			sum = decin();
			break;
		}
		else 
			old = sum; 
			character = fgetc(System.in); 
	}*/
	return 0;
}


/*--------------------------------------------------------------------------
    Copy your function header and code for decout() from hw1
--------------------------------------------------------------------------*/
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
Function Name:          digiterror
Purpose:                This function handles erroneous user input.
Description:            This function reinitializes sum, displays and
                        error message to the user, and asks for fresh
                        input.
Input:                  character: The character that began the problem.
                        sum: A pointer to the sum to reinitialize.
                        message: The message to display to the user.
Result:                 The message is displayed to the user.  sum is 0.
--------------------------------------------------------------------------*/
void digiterror (int character, int * sum, const char * message) {

	/* handle error */
	clrbuf (character);

	/* reset sum */
	*sum = 0;

	/* output error message */
	writeline (DIGIT_STRING, stderr);
	fputc (character, stderr);
	writeline (message, stderr);

	writeline (REENTER_NUMBER, stdout);
}


/*--------------------------------------------------------------------------
Function Name:          getaline
Purpose:                This function will read a string from the user.
Description:            This function gets input from the user via
                        calls to fgetc up to some maximum number of
                        characters.  Input is terminated when either the
                        maximum number of characters are entered, or
                        a newline character is detected.  If the user
                        enters more characters than the maximum, clrbuf
                        is called to remove extra characters which are
                        ignored.  Since this is routine accepts input,
                        if EOF is detected EOF is passed back to the main
                        program.
Input:                  message:  the destination array where input is stored.
                        maxlength:  the maximum number of non-NULL characters
                                allowed in the string + 1 for the NULL char.
Result:                 User input is stored in message.
                        EOF is returned when the user enters ^D.
                        Otherwise, the length of the message is returned.
--------------------------------------------------------------------------*/
int getaline (char * message, int maxlength) {
	int index = 0; /* initializing index to zero. */
	int character = 0; /* initializing integer character to zero */
	maxlength = MAXLENGTH; /* initializing maxlength to the global 
	MAXLENGTH. */
	character = fgetc(stdin); /*takes in the first character that 
	the user has inputted into the system. */
	/* A do while loop that reads in each character that the user has
	 * typed and stores the characters into an array. However, when the
	 * character runs into the enter character, the program stops storing
	 * in the characters into an array. */
	do{
		if (character == EOF) { /*if the user presses control D */
			return EOF; /* the functoin ends. */
		}
		message[index] = (char)character; /* storing each 
		character into an array. */
		character = fgetc(stdin); /* character will become 
		the character that the user has inputted. */
		index++;
	}  while (character != '\n' && index < maxlength-1); /*a do while 
	loop that keeps running until it hits the maximum length that the 
	system can store and hits the Enter character. */
	clrbuf(character); /*calls the clrbuf method so that the extra
	characters are not outputted */
	message[index] = NULL; /*storing null character into the array */
	if (debug_on == TRUE) { /*if the user types in -x at the beginning. */
		/*prints out the debug message witht the length size. */
		fprintf(stderr, 
		"[*DEBUG:  The length of the string just entered is ");
		decout(index, stderr);
		fprintf(stderr, "]");
	}
	return index; /*prints out the string's length. */
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
	while (message[index] != 0 && message[index] != NULL) {
		fputc (message[index], stream); /*prints out the character that 
		is stored in the array. */
		index++; /*incrementing the index every time the while 
		condition is met. */
	}
	/*if the user types in the -x, the debug message will appear */
	if (debug_on == TRUE) {
		fprintf(stderr, 
		"\n[*DEBUG:  The length of the string displayed is ");
		decout(index, stderr);
		fprintf(stderr, "]\n");
	}
	return index; /* returns the character length. */
}

/*--------------------------------------------------------------------------
Function Name:          main
Description:            This function asks for input and displays output
Purpose:                This program asks the user to enter a string
                        and a number.  Computations are performed on the 
                        strings and numbers, and the results are displayed.
Description:            This function asks for input and displays output
                        in an infinite loop until EOF is detected.  Once EOF
                        is detected, the lengths of the types are displayed.
Input:                  None.
--------------------------------------------------------------------------*/
int main (int argc, char *const* argv) {
	char buffer[MAXLENGTH];      /* to hold string */
	int number;                  /* to hold number entered */
	int strlen;                  /* length of string */

	int array[10];               /* to show user where memory is allocated 
	*/
	int * ap = array;		/* to show user about addresses in 
	memory */
	int ** app = &ap;		/* to show user about addresses in 
	memory */
	int * apx = &array[0];	/* to show user about addresses in memory */
	char option;                 /* the command line option */

	/* initialize debug states */
	debug_on = FALSE;

	/* check command line options for debug display */
	while ((option = getopt (argc, argv, "x")) != EOF) {
		switch (option) {
			case 'x': debug_on = TRUE; break;
		}
	}

	/* infinite loop until user enters ^D */
	while (1) {
		writeline ("\nPlease enter a string:  ", stdout);
		strlen = getaline (buffer, MAXLENGTH);
		newline (stdout);

		/* check for end of input */
		if (strlen == EOF)
			break;

		writeline ("The string is:  ", stdout);
		writeline (buffer, stdout);

		writeline ("\nIts length is ", stdout);
		decout (strlen, stdout);
		newline (stdout);

		writeline ("\nPlease enter a decimal number:  ", stdout);
		if ((number = decin ()) == EOF)
			break;

		writeline ("Number entered is:  ", stdout);
		decout (number, stdout);

		writeline ("\nAnd in hexidecimal is:  ", stdout);
		hexout (number, stdout);

		writeline ("\nNumber entered multiplied by 8 is:  ", stdout);
		decout (number << 3, stdout);
		writeline ("\nAnd in hexidecimal is:  ", stdout);
		hexout (number << 3, stdout);

		newline (stdout);
	}

	writeline ("\nThe value of ap is:  ", stdout);
	decout ((int) ap, stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((int) ap, stdout);
	newline (stdout);

	writeline ("The value of app is:  ", stdout);
	decout ((int) app, stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((int) app, stdout);
	newline (stdout);

	writeline ("The value of apx is:  ", stdout);
	decout ((int) apx, stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((int) apx, stdout);
	newline (stdout);

	writeline ("The value of ap + 1 is:  ", stdout);
	decout ((int) (ap+1), stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((int) (ap+1), stdout);
	newline (stdout);

	writeline ("The address of array[0] is:  ", stdout);
	decout ((int) &array[0], stdout);
	newline (stdout);

	writeline ("The address of array[1] is:  ", stdout);
	decout ((int) &array[1], stdout);
	newline (stdout);

	writeline ("The size of a float is:  ", stdout);
	decout (sizeof (float), stdout);
	newline (stdout);

	writeline ("The size of a double is:  ", stdout);
	decout (sizeof (double), stdout);
	newline (stdout);

	writeline ("The size of a long double is:  ", stdout);
	decout (sizeof (long double), stdout);
	newline (stdout);

	writeline ("The size of a char is:  ", stdout);
	decout (sizeof (char), stdout);
	newline (stdout);

	writeline ("The size of an int is:  ", stdout);
	decout (sizeof (int), stdout);
	newline (stdout);

	writeline ("The size of a short is:  ", stdout);
	decout (sizeof (short), stdout);
	newline (stdout);

	writeline ("The size of a short int is:  ", stdout);
	decout (sizeof (short int), stdout);
	newline (stdout);

	writeline ("The size of a long is:  ", stdout);
	decout (sizeof (long), stdout);
	newline (stdout);

	writeline ("The size of a long int is:  ", stdout);
	decout (sizeof (long int), stdout);
	newline (stdout);

	writeline ("The size of a long long is:  ", stdout);
	decout (sizeof (long long), stdout);
	newline (stdout);

	writeline ("The size of a signed is:  ", stdout);
	decout (sizeof (signed), stdout);
	newline (stdout);

	writeline ("The size of a signed char is:  ", stdout);
	decout (sizeof (signed char), stdout);
	newline (stdout);

	writeline ("The size of a signed short is:  ", stdout);
	decout (sizeof (signed short), stdout);
	newline (stdout);

	writeline ("The size of a signed short int is:  ", stdout);
	decout (sizeof (signed short int), stdout);
	newline (stdout);

	writeline ("The size of a signed int is:  ", stdout);
	decout (sizeof (signed int), stdout);
	newline (stdout);

	writeline ("The size of a signed long is:  ", stdout);
	decout (sizeof (signed long), stdout);
	newline (stdout);

	writeline ("The size of a signed long int is:  ", stdout);
	decout (sizeof (signed long int), stdout);
	newline (stdout);

	writeline ("The size of a signed long long is:  ", stdout);
	decout (sizeof (signed long long), stdout);
	newline (stdout);

	writeline ("The size of an unsigned is:  ", stdout);
	decout (sizeof (unsigned), stdout);
	newline (stdout);

	writeline ("The size of an unsigned char is:  ", stdout);
	decout (sizeof (unsigned char), stdout);
	newline (stdout);

	writeline ("The size of an unsigned short is:  ", stdout);
	decout (sizeof (unsigned short), stdout);
	newline (stdout);

	writeline ("The size of an unsigned short int is:  ", stdout);
	decout (sizeof (unsigned short int), stdout);
	newline (stdout);

	writeline ("The size of an unsigned int is:  ", stdout);
	decout (sizeof (unsigned int), stdout);
	newline (stdout);

	writeline ("The size of an unsigned long is:  ", stdout);
	decout (sizeof (unsigned long), stdout);
	newline (stdout);

	writeline ("The size of an unsigned long int is:  ", stdout);
	decout (sizeof (unsigned long int), stdout);
	newline (stdout);

	writeline ("The size of an unsigned long long is:  ", stdout);
	decout (sizeof (unsigned long long), stdout);
	newline (stdout);

	writeline ("The size of a void pointer is:  ", stdout);
	decout (sizeof (void *), stdout);
	newline (stdout);

	writeline ("The size of a character pointer is:  ", stdout);
	decout (sizeof (char *), stdout);
	newline (stdout);

	writeline ("The size of an int pointer is:  ", stdout);
	decout (sizeof (int *), stdout);
	newline (stdout);

	writeline ("The size of a long pointer is:  ", stdout);
	decout (sizeof (long *), stdout);
	newline (stdout);

	writeline ("The size of a float pointer is:  ", stdout);
	decout (sizeof (float *), stdout);
	newline (stdout);

	writeline ("The size of a double pointer is:  ", stdout);
	decout (sizeof (double *), stdout);
	newline (stdout);

	writeline ("The size of a long double pointer is:  ", stdout);
	decout (sizeof (long double *), stdout);
	newline (stdout);

	newline (stdout);

	return 0;
}
