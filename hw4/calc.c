/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        January 24, 2015
                                                        cs12xbo
                                Assignment Four

File Name:      calc.c
Description:    In this assignment, I have developed a program that will 
		simulate a top-of-the-line calculator that will perform such 
		advanced commands as addition, subtractions, multiplication, 
		division, exponentiation, and factorial! The program will 
		accept mathematical expressions in "infix" notation 
		convert it to its "postfix" equivalent and then evaluate this 
		expression
****************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include "calc.h"
#include "mylib.h"
#include "stack.h"

#define CHARACTER(word) ((char) ((word) & 0x000000FF))
#define INDEX(word) (((word) & 0x0000FF00) >> 8)
#define PRIORITY(word) ((word) & 0x0000FE00)
#define BYTE 8
#define SIGN_BIT 0x80000000

static char operators[] = "()+-*/^ !";

static long add (long, long);
static long divide (long, long);
static long exponent (long, long);
static long fact (long, long);
static long mult (long, long);
static long setupword (int);
static long sub (long, long);

static long (*functions[]) (long, long) =
    { NULL, NULL, add, sub, mult, divide, exponent, NULL, fact };

/*--------------------------------------------------------------------------
Function Name:         eval
Purpose:	       Utilizing 2 Stacks, evaluate mathematical expressions 
		       from "postfix" notation. 
Description:	       Creating a new local stack, stack2, that will take in 
		       the values from stack1, which has values from intopost,
		       until stack1 is empty. Then, until stack2 is empty, 
		       values from stack2 will pop and then push the values 
		       into the empty stack1. However, if that value is an 
		       operator, the program will call a specific operator 
		       functions that will use the two top numbers in stack1 
		       as operands. After the operator function runs, it will 
		       return a value and push it into stack1. Continues until
		       stack2 is empty and finally pops out the answer in 
		       stack1.
Input:                 Stack * stack1: A pointer to the first stack.  
Result:                Returns the mathematical answer depending on what 
		       operator the user has inputted into the program. 
--------------------------------------------------------------------------*/
long eval (Stack * stack1) {
	/* initializing operands, item, and operator answer to zero. */
	long op1 = 0, op2 = 0, word = 0, item = 0; 
	/* creating a new local stack, stack2 */
	Stack * stack2 = new_Stack(CALCSTACKSIZE);
	/* until stack1 is empty and does not have any values
	 * that it has stored from intopost */
	while (!isempty_Stack(stack1)) {
		/* keep popping item that was stored in stack1 
		 * and push it to stack2, reversing stack1
		 * onto stack2 */
		pop(stack1, &item);
		push(stack2, item);
	}
	/* until stack2 is empty*/
	while (!isempty_Stack(stack2)) {
		/* pop the first top item in stack2 */
		pop(stack2, &item);
		/* if that item is a number */
		if (item >= 0) {
			/* push it to stack1 */
			push(stack1, item);
		}
		/* if that popped item is an operator */
		else {
			/* if that operator is a factorial */
			if (INDEX(item) == BYTE) {
				/* only pop one item from stack1
				 * and initialize it to be the first operand */
				pop(stack1, &op1);
			}
			else {
				/* pop the top item in stack 1 and initialize
				 * it to be the first operand */
				pop(stack1, &op1);
				/* now pop the new top item in stack1 and
				 * initialize it to be the second operand */
				pop(stack1, &op2);
			}
			/* word will become the return value, which was 
			 * returned from a specific operator method, 
			 * that took one operand or two operands depending
			 * on the operator called. */
			word = functions[INDEX(item)](op1, op2);
			/* then push that return value to stack1 */
			push(stack1, word);
		}
	}
	delete_Stack (&stack2);
	/* pops the the last number in stack1 so stack1 can be empty */
	pop(stack1, &word);
	/* return the final answer */
	return word;
}



/*--------------------------------------------------------------------------
Function Name:         intopost
Purpose:               Utilizing 2 Stacks, convert "infix" mathematical 
		       expressions entered by the user into their "postfix" 
		       equivalents.
Description:	       This method calls in stack1 and creates a local stack, 
		       stack2. Whenever the user inputs Cntrl D, the program
		       terminates and deletes the both stacks created. If 
		       there is a blank space in between the user's input,
		       then the program disregards and continues to read
		       the digits that the user has inputted. If the character
		       that the user has inputted is not a number, then the
		       character is stored into stack2. If the operator 
		       that the character has put in has a lower priority 
		       than the operators in stack2, keep popping the operators
		       in stack2 and push it to stack1.  
Input:                 Stack * stack1: The pointer to a stack   
Result:                Returns true so that the user can know that the
		       method has worked perfectly. 
--------------------------------------------------------------------------*/
long intopost (Stack * stack1) {
	Stack * stack2 = new_Stack(CALCSTACKSIZE);
	long item = 0;
	int character = 0;
	/* gets the first character that the user has inputted */
	character = fgetc(stdin);
	/* while the user has not pressed the Enter key */
	while (character != '\n') {
		/* if the user has pressed ctrl ^D then end the program 
		 * and deletes stack2 */
		if (character == EOF) {
			delete_Stack(&stack2);
			return EOF;
		}
		/* if there is a space in the statement that the user has 
		 * inputted, then just keep reading all the statement 
		 * and disregard the empty space(s). */
		if (character == ' ') {
			character = fgetc(stdin);
			continue;
		}
		/* if the character that the user has inputted is a number */
		if (isdigit(character)) {
			/* first, unget the first character that the
			 * user has typed, so that the program can read and
			 * take the entire input correctly */
			ungetc(character, stdin);
			/* initialize the first character and the
			 * entire number that the user has wrote 
			 * into item .*/
			item = decin();
			/* push that item into stack1 */
			push (stack1, item); 
		}
		/* else, if the character that the program is reading
		 * is an open parenthesis from the user's input */
		else if (character == '(') {
			/* push that character into stack2 */
			push(stack2, character);
		}
		/* else, if the character that the program is reading 
		 * is a close parenthesis from what the user has inputted */
		else if (character == ')') {
			/* pop the top item in stack2 */
			pop(stack2, &item);
			/* while that item is not the open parenthesis */
			while (item != '(') {
				/* push that item into stack1 */
				push(stack1, item);
				/* pop the next item in stack2 so that
				 * it can be seen if it is an open parenthesis
				 * or not. */
				pop(stack2, &item);
			}
		}
		/* if all these statement has been checked, but there are stuff
		 * in stack2, then keep popping items that's in stack2 and 
		 * push it into stack1. */
		else {
			/* if stack2 is not empty */
			if(!isempty_Stack(stack2)) {
				/* top the item in stack2 so that it can 
				 * be compared to operator/character that the
				 * user has inputted. */
				top(stack2, &item);
			}
			/* until stack2 is empty and until the priority of 
			 * operator that the user has inputted is higher or 
			 * equal to the operator stored in stack */
			while (!isempty_Stack(stack2) &&
			PRIORITY(item) >= PRIORITY(setupword(character))) {
				/* pop the operator in stack2 and push it into
				 * stack1 */
				pop(stack2, &item);
				push(stack1, item);
				if(!isempty_Stack(stack2)) {
					top(stack2, &item);
				}
			}
			/* push the operator into stack2 */
			push(stack2, setupword(character));
		}
	/*get the next character that the user has inputted */
	character = fgetc(stdin);
	}
	/* popping and pushing the remaining operators in stack2
	 * to stack1 until stack2 is empty*/
	while (!isempty_Stack(stack2)) {
		pop(stack2, &item);
		push(stack1, item);
	}
	delete_Stack (&stack2);
	return TRUE;
}

static long add (long augend, long addend) {
	return augend + addend;
}

static long divide (long divisor, long dividend) {
	return dividend / divisor;
}

/*--------------------------------------------------------------------------
Function Name:         exponent
Purpose:               Raising base to the power exponent.
Description:	       Will take in the operands that will be receiving from 
		       eval and then will continually multiply itself until 
		       i is less than power. 
Input:                 long power: a long number that is telling it to 
		       continually multiply itself. Passed from eval 
		       long base: a long number that will multiply itself by.
		       Passed from eval. 
Result:                Returns the mathematical answer of an exponental math
		       problem given the two longs passed from eval.  
--------------------------------------------------------------------------*/
static long exponent (long power, long base) {
	/* result equals 1, so that if base is zero, the method will 
	 * return 1 */
	int i, result = 1;
	/* will keep multiplying itself until i is less than the power
	 * passed by eval. */
	for (i = 0; i < power; i++) {
		/* result will become the base times result */
		result *= base;
	}
	return result;
}

/*--------------------------------------------------------------------------
Function Name:         fact 
Purpose:               Calculating xxx factorial.
Description:	       If the long value passed from eval is less than or
		       equal to 1, return 1. Else, the value passed from 
		       eval will keep multiplying and calling fact method,
		       while decreasing by 1 until xxx is 1. 
Input:                 long xxx: a long number being passed. 
		       long ignored: a long that is not being used. 
Result:                Returns the factorial of a number being passed
		       from eval. 
--------------------------------------------------------------------------*/
static long fact (long xxx, long ignored) {
	long result = 0;
	if (xxx <= 1) {
		return 1;
	}
	/* result will be the original xxx, that was passed from eval, and 
	 * will continually call the fact method while decrementing by 1 until
	 * xxx = 1. */
	result = xxx*fact(xxx-1, ignored);
	return result;
}


static long mult (long factorx, long factory) {
	return factorx * factory;
}


/*--------------------------------------------------------------------------
Function Name:         setupword
Purpose:               Constructor funtion for longs representing operators to 
		       be stored on your Stacks. The representation for the 
		       operators should have everything associated with that 
		       operator: a distinction from numbers, the index in the 
		       functions array corresponding to that operator, and the 
		       priority of the operator and the ASCII code.
Description:	       Will take in the character that is not a number and then
		       convert it into an operator by shifting left by eight 
		       to get the right operator. 
Input:                 int character: int value that takes in only 
		       one character. 
Result:		       Returns the operator by masking the character that is 
		       being passed in through intopost. 	
-------------------------------------------------------------------------*/
static long setupword (int character) {
	int index = 0; /*to track placement in operators array */
	/* search for match to user input of operator */
	while(operators[index]) {
		/* if the character equals the operator in the array */
		if (character == operators[index]) {
			break;
		}
	/* keeps incrementing to find the operator in the array */	
	index++;
	}
	return SIGN_BIT | (index << BYTE) | character;
}


static long sub (long subtrahend, long minuend) {
	return minuend - subtrahend;
}
