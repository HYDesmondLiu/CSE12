/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        Februrary 4, 2015
                                                        cs12xbo
                                Assignment Five

File Name:      stack.c
Description:    An array-based stack of longs that the user can create, store
		certain numbers in, and delete. The program not only allows
		the user to check if the current stack is empty or full, but 
		also empty out the current stack by the certain key letter that
		the user types in. The user would also be allowed to check how
		many storage one put numbers in, what the top number is in the
		stack, and able to pop the top number in the stack.
****************************************************************************/

#include <stdio.h>
#include "list.h"
#include "stack.h"

/*--------------------------------------------------------------------------
Function Name:         delete_Stack
Purpose:	       This destructor function deallocates all memory 
		       associated with the Stack, including the memory 
		       associated in the stack. 
Description:	       Calls the delete_List stack pointer pointer
		       to get rid of any memory associated with it. 
Input:                 Stack ** spp: A pointer to a pointer of the stack. 
Result:                Nothing is returned and frees up memeory. 
--------------------------------------------------------------------------*/
void delete_Stack (Stack ** spp) {
        delete_List (spp);
}


/*--------------------------------------------------------------------------
Function Name:         isempty_Stack
Purpose:               Returns true if this_Stack is empty, and false if it is
		       not.
Description:	       If the occupancy of the stack is zero, which 
		       means that no numbers are stored in it, then returns 
		       TRUE or false by calling the isempty_List method. 
Input:                 List * this_stack: Calls/points to the current stack 
		       that the user is operating on. 
Result:                Returns the value that is receiving from the 
		       isempty_List function. 
--------------------------------------------------------------------------*/
long isempty_Stack (Stack * this_stack) {
        return isempty_List (this_stack);
}


/*--------------------------------------------------------------------------
Function Name:	       new_Stack
Purpose:	       This constructor function allocates and initializes a 
		       new Stack object. It initializes the stack data fields, 
		       and returns a pointer to the stack. All new stack should
		       be empty.
Description:	       Creates a new stack that has copy_func, delete_func, 
		       is_greater_than_func, and write_func with it. 
Input:		       void *(*copy_func) (void *): A pointer to the copy_func
		       that points to a void pointer that takes in void. 
		       void (*delete_func) (void *): A pointer to the 
		       delete_func that points to a void pointer that takes
		       in void. 
		       long (*is_greater_than_func) (void *, void *): A 
		       pointer to the is_greater_than_func that takes in
		       two void pointer of long. 
		       FILE *(*write_func) (void *, FILE *): A pointer to the
		       write_func method that points to a void pointer and 
		       FILE pointer while taking in FILE. 
Result:                Returns the List created in the new_List method.  
--------------------------------------------------------------------------*/
Stack * new_Stack (void *(*copy_func) (void *),
        void (*delete_func) (void *),
        long (*is_greater_than_func) (void *, void *),
        FILE *(*write_func) (void *, FILE *)) {

        return new_List (copy_func, delete_func, is_greater_than_func, 
	write_func);
}


/*--------------------------------------------------------------------------
Function Name:         pop
Purpose:               Removes an item from the top of the stack, and sends it 
		       back through the output parameter item. Returns true 
		       upon success and false upon failure by calling the 
		       remove_List method. 
Description:	       Returns the values called from the remove_List function.
		       Removes the Node that is on the end of the list. 
Input:                 Stack * this_Stack: Pointer to the current stack 
		       that has been created. 
Result:                Returns the result of whatever happens in the 
		       remove_List function. 
--------------------------------------------------------------------------*/
void * pop (Stack * this_stack) {
        return remove_List (this_stack, END);
}

/*--------------------------------------------------------------------------
Function Name:         push
Purpose:               Adds item to the top of this_Stack.
Description:	       Stores a number that the user has typed into the system
		       into the bottom of the list. Then the program goes
		       to the next avaiable space in the list that 
		       the user can store a number into.
Input:                 Stack * this_Stack: A pointer to the current stack that
		       the user has created. 
		       void * element: Any input that the user has inputted 
		       into the program.
Result:                Returns the result of whatever happens in the insert
		       function in the list.c file. 
--------------------------------------------------------------------------*/
long push (Stack * this_stack, void * element) {
        return insert (this_stack, element, END);
}

/*--------------------------------------------------------------------------
Function Name:         top
Purpose:               Sends back the item on the top of the stack through the 
		       output parameter item, but does not remove it from the 
		       stack. Returns true upon success and false upon failure.
Description:	       Calls out the top number in the stack array of that 
		       current stack by calling the view method in list.c
Input:                 Stack * this_Stack: A pointer to the current stack that
		       the user has created. 
Result:                Returns the result of the view method that is in list.c
		       file. 
--------------------------------------------------------------------------*/
void * top (Stack * this_stack) {
        return view (this_stack, END);
}


/*--------------------------------------------------------------------------
Function Name:         write_Stack:  
Purpose:	       Writes the element in the stack. The list is printed to
		       filestream stream.
Description:	       Prints out the return result/statement that is 
		       receiving from the write_List method.
Input:                 List * this_stack: A pointer to the current stack 
		       File * stream: A pointer to the output of the File. 
Result:                Result will change depending on what numbers and how
		       many nodes are in the list. Returns the output of the
		       write_List method in list.c file. . 
--------------------------------------------------------------------------*/
FILE * write_Stack (Stack * this_stack, FILE * stream) {
        return write_List (this_stack, stream);
}
