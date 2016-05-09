/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        January 16, 2015
                                                        cs12xbo
                                Assignment Three

File Name:      stack.c
Description:    An array-based stack of longs that the user can create, store
		certain numbers in, and delete. The program not only allows
		the user to check if the current stack is empty or full, but 
		also empty out the current stack by the certain key letter that 
		the user types in. The user would also be allowed to check how 
		many storage one put numbers in, what the top number is in the
		stack, and able to pop the top number in the stack. 

Answers:
1. The address returned by malloc() is 0x804b008
2. The address returned by new_Stack is 0x804b014
3. This address is in the stack and heap.
4. The value of spp is 0xbfffeccc and it is in stack and heap. 
5. The value of *spp is 0x804b014 and it is in data. 
6. The value of the parameter being passed to free() is 0x803b008.
7. Yes this parameter to free is the same address that was returned from
malloc. 

****************************************************************************/

#include <malloc.h>
#include <stdio.h>
#include "mylib.h"
#include "stack.h"

#define STACK_POINTER_INDEX (-1)        /* Index of next available space */
#define STACK_SIZE_INDEX (-2)           /* Index of size of the stack */
#define STACK_COUNT_INDEX (-3)          /* Index of which stack allocated */
#define STACK_OFFSET 3  /* offset from allocation to where user info begins */

/* catastrophic error messages */
static const char DELETE_NONEXIST[] = "Deleting a non-existent stack!!!\n";
static const char EMPTY_NONEXIST[] = "Emptying a non-existent stack!!!\n";
static const char INCOMING_NONEXIST[] = 
                        "Incoming parameter does not exist!!!\n";
static const char ISEMPTY_NONEXIST[] = 
                        "Isempty check from a non-existent stack!!!\n";
static const char ISFULL_NONEXIST[] = 
                        "Isfull check from a non-existent stack!!!\n";
static const char NUM_NONEXIST[] = 
                        "Num_elements check from a non-existent stack!!!\n";
static const char POP_NONEXIST[] = "Popping from a non-existent stack!!!\n";
static const char POP_EMPTY[] = "Popping from an empty stack!!!\n"; 
static const char PUSH_NONEXIST[] = "Pushing to a non-existent stack!!!\n";
static const char PUSH_FULL[] = "Pushing to a full stack!!!\n";
static const char TOP_NONEXIST[] = "Topping from a non-existent stack!!!\n";
static const char TOP_EMPTY[] = "Topping from an empty stack!!!\n";
static const char WRITE_NONEXIST_FILE[] = 
                "Attempt to write using non-existent file pointer!!!\n";
static const char WRITE_NONEXIST_STACK[] = 
                        "Attempt to write to a non-existent stack!!!\n";

/* Debug messages */
static const char ALLOCATED[] = "[Stack %ld has been allocated]\n";
static const char DEALLOCATE[] = "[Stack %ld has been deallocated]\n";
static const char HEXPOP[] = "[Stack %ld - Popping 0x%lx]\n";
static const char HEXPUSH[] = "[Stack %ld - Pushing 0x%lx]\n";
static const char HEXTOP[] = "[Stack %ld - Topping 0x%lx]\n";
static const char POP[] = "[Stack %ld - Popping %ld]\n";
static const char PUSH[] = "[Stack %ld - Pushing %ld]\n";
static const char TOP[] = "[Stack %ld - Topping %ld]\n";

/* static variable allocation */
static int debug = FALSE; /* allocation of debug flag */
static int stack_counter = 0; /* number of stacks allocated so far */

/* Debug state methods */
void debug_off (void) {
        debug = FALSE;
}

void debug_on (void) {
        debug = TRUE;
}

/*--------------------------------------------------------------------------
Function Name:         delete_Stack
Purpose:               This destructor function deallocates all memory 
		       associated with the stack and sets its pointer in the 
		       calling function to NULL.
Description:	       Able to clearly deallocate all memory that was 
		       created with stack and allows the user to decrement
		       a stack. 
Input:                 Stack ** spp: (stack pointer pointer) Points to the 
		       entire stack that has been created. 
Result:                The stack has nothing and different statements prints
		       out depending on what the user types and the status
		       of the stack. Returns nothing.  
--------------------------------------------------------------------------*/
void delete_Stack (Stack ** spp) {
	/* if the stack has not been created or there is no stack */
	if ((*spp == NULL && spp == NULL) || stack_counter == 0) {
		/* print out the debug message that the user is 
		 * deleting a stack that has not been created */
		fprintf(stderr, DELETE_NONEXIST);
		/*returns nothing so escapes the method */
		return;
	}
	/* if the user types in -x */
	if (debug == TRUE) { 
		/* print out what stack has been deallocated */
		fprintf(stderr, DEALLOCATE, (long)stack_counter);
	}
	/* emptying the memory, since *spp(this_Stack) is memory + 
	 * STACK_OFFSET. */
	free( *spp - STACK_OFFSET);
	/* initialize this_Stack to null */
	*spp = NULL;
	/* decrement the number of stack created */
	stack_counter--;
}

/*--------------------------------------------------------------------------
Function Name:         empty_Stack
Purpose:               Effectively empties the stack of all its elements.
Description:	       Goes back to the start(0) of the STACK_POINTER_INDEX to
		       overwrite and rewrite the storage. 
Input:                 Stack * this_Stack: Pointer to the current stack. 
Result:                Initializes the STACK_POINTER_INDEX of that stack 
		       to zero if the user has created a stack. Nothing is 
		       returned. 
--------------------------------------------------------------------------*/
void empty_Stack (Stack * this_Stack) {
	if (stack_counter == 0) { /* if a stack has not been created */
		/* prints out the error message that says cannot empty 
		 * a nonexisting stack */
		fprintf(stderr, EMPTY_NONEXIST);
	}
	/* else, initialize the STACK_POINTER_INDEX to zero
	 * to remove and overwrite the past stored numbers in the
	 * array. */
	else
		this_Stack[STACK_POINTER_INDEX] = 0;
}

/*--------------------------------------------------------------------------
Function Name:         isempty_Stack
Purpose:               Returns true if this_Stack is empty, and false if it is
		       not.
Description:	       If the STACK_POINTER_INDEX of that stack is zero, which 
		       means that no number is stored in it, then returns TRUE.
		       Otherwise, this method returns false. 
Input:                 Stack * this_Stack: Calls/points to the current stack 
		       that the user is operating on. 
Result:                Returns true if the current stack is empty else returns
		       false to notifiy that it has a number in it. 
--------------------------------------------------------------------------*/
long isempty_Stack (Stack * this_Stack) {
	if (stack_counter == 0) { /* if a stack has not been created */
		/* print out the error message that says cannot check 
		 * a nonexisting stack if it is empty or not. */
		fprintf(stderr, ISEMPTY_NONEXIST);
		return TRUE;
	}
	/* if the stack has been created and the next avaiable storage 
	 * in the stack is zero */
	if (this_Stack[STACK_POINTER_INDEX] == 0) {
		/*return that the stack is currently empty */
		return TRUE;
	}
	/* if not return FALSE, that it is not empty */
	return FALSE;
}

/*--------------------------------------------------------------------------
Function Name:         isfull_Stack
Purpose:               Returns true if this_Stack is full, and false if it is 
		       not.
Description:	       If the STACK_POINTER_INDEX is bigger or equal to the 
		       storage size of the stack that the user have initially
		       created then returns TRUE, that the stack is full;
		       otherwise, returns false, that the current stack is not
		       full. 
Input:                 Stack * this_Stack: Calls/points to the current stack 
		       that the user is on. 
Result:                Returns true if the next avaiable space is bigger or 
		       equal to the storage size that the user has first 
		       initialized as. Returns false if the next aviable space
		       is smaller than the size that the user has initialized
		       the stack array with. 
--------------------------------------------------------------------------*/
long isfull_Stack (Stack * this_Stack) {
	/* if a stack has not been created. */
	if (stack_counter == 0) {
		/* prints out an error message that says it cannot
		 * check a nonexisting stack if it is full or not */
		fprintf(stderr, ISFULL_NONEXIST);
		return TRUE;
	}
	/* if the next avaiable space in the current stack is bigger or equal
	 * to the original size of the stack that the user has initialized 
	 *  with */
	if (this_Stack[STACK_POINTER_INDEX] >= this_Stack[STACK_SIZE_INDEX]) {
		return TRUE; /* Returns true, that the current stack is full */
	}
	/* else it returns FALSE, that the current stack  is not full. */
	return FALSE;
}

/*--------------------------------------------------------------------------
Function Name:         Stack * new_Stack
Purpose:               This constructor function allocates and initializes a 
		       new Stack object. It allocates memory to hold stacksize 
		       number of longs, initializes the stack infrastructure, 
		       and returns a pointer to the first storage space in the 
		       stack.
Description:	       Creating a memory that takes in a stacksize that the 
		       user has inputted into the system and add the 
		       STACK_OFFSET, which is three, to have 
		       STACK_POINTER_INDEX, STACK_SIZE_INDEX, and STACK_COUNT.
		       Every time the user creates a new stack the 
		       stack_counter will increase.
Input:                 unsigned long stacksize: A long number that will be
		       the size of the stack. 
Result:                Returns the current stack. If the user creates another
		       stack, then the program will be on that new stack. 
--------------------------------------------------------------------------*/
Stack * new_Stack (unsigned long stacksize) {
	Stack * this_Stack; /*the stack for the caller*/
	void * memory; /*to hold to memory from malloc */
	/*allocate*/
	memory = malloc((stacksize + STACK_OFFSET) * sizeof(Stack));
	this_Stack = (Stack *)memory + STACK_OFFSET;
	/*initialize*/
	/* initializing that the current storage is at 0. */
	this_Stack[STACK_POINTER_INDEX] = 0;
	/* initializing that this stack size will have the stacksize that the 
	 * user has inputted */
	this_Stack[STACK_SIZE_INDEX] = stacksize;
	/* stack will increment every time the user creates a new stack. */
	stack_counter++;
	/*placing the stack count to individiual stack */
	this_Stack[STACK_COUNT_INDEX] = stack_counter; 
	/* if the user has typed in -x, then the debug message will appear */
	if (debug == TRUE) {
		/*prints out the debug message with the number of stack the 
		 * user has created */
		fprintf(stderr, ALLOCATED, 
		(long)this_Stack[STACK_COUNT_INDEX]);
	}
	/*returns the current stack */ 
	return this_Stack;
}

/*--------------------------------------------------------------------------
Function Name:         num_elements
Purpose:               Returns the number of elements in this_Stack.
Description:	       Returns the total number of storages that the user has 
		       pushed numbers into by using the STACK_POINTER_INDEX.
Input:                 Stack * this_Stack:
Result:                Returns the next avaiable space in the array. 
--------------------------------------------------------------------------*/
long num_elements (Stack * this_Stack) {
	/* if the user has not created any array stack */
	if (stack_counter == 0 ) {
		/* prints out an error message that states this method 
		 * cannot check an nonexisting stack */
		fprintf(stderr, NUM_NONEXIST);
		return FALSE;
	}
	/* returns the total storages, in the stack, that the user have 
	 * pushed the numbers into. */
	return this_Stack[STACK_POINTER_INDEX];
}

/*--------------------------------------------------------------------------
Function Name:         pop
Purpose:               Removes an item from the top of the stack, and sends it 
		       back through the output parameter item. Returns true 
		       upon success and false upon failure.
Description:	       If a stack has been created and if there is a number
		       stored in the stack, then the number at the very top 
		       of the array stack will pop out and go back one array 
		       in the stack. 
Input:                 Stack * this_Stack: Pointer to the current stack 
		       that has been created. 
		       long * item: A long number that the user has inputted
		       into the system. 
Result:                Returns false if the stack has not been created or 
		       if the stack has no numbers stored in it. Returns 
		       true if this method successfully happens. Pops 
		       out the top number in the stack until there is no 
		       number in the stack array. 
--------------------------------------------------------------------------*/
long pop (Stack * this_Stack, long * item) {
	long sp = 0; /*initialzing sp to zero */
	/* if the stack array has not been created by the user */ 
	if (stack_counter == 0) {
		/* prints out an error message that states this method 
		 * cannot pop a number in a nonexisting stack */
		fprintf(stderr, POP_NONEXIST);
		/* also returns false, to print out a warning */
		return FALSE;
	}
	/* if the stack is empty */ 
	if (isempty_Stack(this_Stack) == TRUE) {
		/* prints out an error message that the stack is empty;
		 * therefore, cannot pop any number */
		fprintf(stderr, POP_EMPTY);
		/* also returns false, to print out a warning */ 
		return FALSE;
	}
	/*sp will be intiailized to the current storage space */
	sp = this_Stack[STACK_POINTER_INDEX] - 1;
	/* the item will now be the number that was stored in the stack 
	 * array */
	* item = this_Stack[sp];  
	/* if the user has typed in '-x' then the debug message will turn 
	 * on */ 
	if (debug == TRUE) {
		/* prints the debug message with the current stack and the 
		 * number that the was stored in the top space of the stack */
		if (*item > 0) {
			fprintf(stderr, POP, 
			(long)this_Stack[STACK_COUNT_INDEX], *item);
		}
		else
			fprintf(stderr, HEXPOP, 
			(long)this_Stack[STACK_COUNT_INDEX], *item);
	}
	/* decrements so that the array space goes back one everytime 
	 * this function is run */ 
	this_Stack[STACK_POINTER_INDEX]--;
	/* returns true if the function successfully runs */ 
	return TRUE;
}

/*--------------------------------------------------------------------------
Function Name:         push
Purpose:               Adds item to the top of this_Stack.
Description:	       Stores a number that the user has typed into the system
		       into the top of the stack array. Then the program goes
		       to the next avaiable space in the stack array that 
		       the user can store a number into. 
Input:                 Stack * this_Stack: A pointer to the current stack that
		       the user has created. 
		       long item: A long number that the user has inputted into
		       the program.
Result:                Returns false if a stack has not been created by the 
		       user or if the stack is full, which causes the user to
		       not be able to push any numbers into the stack array. 
		       However, if this method runs successfully, this method
		       returns the next avaiable space in the stack. 
--------------------------------------------------------------------------*/
long push (Stack * this_Stack, long item) {
	long sp = 0; /*initializing sp to zero */ 
	/* if the stack array has not been created by the user */ 
	if (stack_counter == 0) {
		/* prints out an error message that states this method 
		 * cannot push a number into the stack that does not
		 * exist */
		fprintf(stderr, PUSH_NONEXIST);
		return FALSE;
	}
	/* if the user has typed in '-x' then the debug message will turn on */
	if (debug == TRUE) {
		/* print the debug message with the current stack and the 
		 * number that the user has pushed into the stack array */
		if (item > 0 ) {
			fprintf(stderr, PUSH, 
			(long)this_Stack[STACK_COUNT_INDEX], item);
		}
		else 
		fprintf(stderr, HEXPUSH, 
		(long)this_Stack[STACK_COUNT_INDEX], item); 
	}
	/* if the stack is full, by going the isfull_Stack method */
	if (isfull_Stack(this_Stack) == TRUE) {
		/* prints out the error message that the stack is full and 
		 * returns FALSE, which pops out a warning */
		fprintf(stderr, PUSH_FULL);
		return FALSE;
	}
	/* sp will be intiailized to the current storage number and 
	 * then will increment */
	sp = this_Stack[STACK_POINTER_INDEX]++;
	/* the stack will store in the item */
	this_Stack[sp] = item;
	/*returns the next empty storage that the user can push a number
	 * into */ 
	return this_Stack[STACK_POINTER_INDEX];
}


/*--------------------------------------------------------------------------
Function Name:         top
Purpose:               Sends back the item on the top of the stack through the 
		       output parameter item, but does not remove it from the 
		       stack. Returns true upon success and false upon failure.
Description:	       Calls out the top number in the stack array of that 
		       current stack. 
Input:                 Stack * this_Stack: A pointer to the current stack that
		       the user has created. 
		       long * item: A long number that the user has typed into
		       the system. 
Result:                If the function actually runs and the criteria to run
		       this method is met, then this function returns TRUE.
		       However, returns false if a stack has not been created, 
		       if the stack is empty, or does not run successfully. 
--------------------------------------------------------------------------*/
long top (Stack * this_Stack, long * item) {
	/*initializing sp to zero */ 
	long sp = 0;
	/* if the stack array has not been created by the user */ 
	if (stack_counter == 0) {
		/* prints out an error message that states this method 
		 * cannot call out a number at the top of the stack that 
		 * does not exist */
		fprintf(stderr, TOP_NONEXIST);
		/* returns false, which pops out a warning and to know
		 * that this function did not work */
		return FALSE;
	}
	/* if the current stack does not have any numbers stored in it */
	if (isempty_Stack(this_Stack) == TRUE) {
		/* prints out an error message that states cannot 
		 * top a number that does not have any number in it */
		fprintf(stderr, TOP_EMPTY);
		/* returns false, which pops out a warning and to know
		 * that this function did not work */
		return FALSE;
	}
	/*sp will be intiailized to the current storage number */
	sp = this_Stack[STACK_POINTER_INDEX] - 1;
	/* the item will take in the value in that current array */
	* item = this_Stack[sp]; 
	/* if the user has typed in '-x' then the debug message will turn on */
	if (debug == TRUE) {
		/* print the debug message with the current stack and the 
		 * top number */
		if (*item > 0) {
			fprintf(stderr, TOP, 
			(long)this_Stack[STACK_COUNT_INDEX], *item);
		}
		else 
			fprintf(stderr, HEXTOP, 
			(long)this_Stack[STACK_COUNT_INDEX], *item);
	}
	/* if the function successfully runs then returns TRUE */
	return TRUE;
}

FILE * write_Stack (Stack * this_Stack, FILE * stream) {

        long index = 0;         /* index into the stack */

        if (this_Stack == NULL) {
                fprintf (stderr, WRITE_NONEXIST_STACK);
                return stream;
        }

        if (stream == NULL) {
                fprintf (stderr, WRITE_NONEXIST_FILE);
                return stream;
        }
                
        if (stream == stderr)
                fprintf (stream, "Stack has %ld items in it.\n",
                        num_elements (this_Stack));

        for (index = STACK_COUNT_INDEX + STACK_OFFSET;
                index < num_elements (this_Stack); index++) {

                if (stream == stderr)
                        fprintf (stream, "Value on stack is |0x%lx|\n",
                                this_Stack[index]);
                else {
                        if (this_Stack[index] < 0)
                                fprintf (stream, "%c ",
                                        (char) this_Stack[index]);
                        else
                                fprintf (stream, "%ld ", this_Stack[index]);
                }
        }

        return stream;
}
