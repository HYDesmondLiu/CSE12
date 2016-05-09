/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        January 31, 2015
                                                        cs12xbo
                                Assignment Five

File Name:      list.c
Description:    In this assignment, I have created a polymorphic generic 
		container based on a linked-list data structure. In list.c, 
		the List and Node structs are defined. The List object contains
		data fields such as occupancy and list_count, and also contains
		pointers to functions which manipulate the objects stored in 
		the list. The Node objects form a doubly-linked list, where 
		the pre pointer points to the previous item in the list and 
		the next pointer points to the next item in the list. The 
		list is circular, so the next pointer of the last item points
		to the first item of the list, and the pre pointer of the 
		first item points to the last item in the list. We keep 
		track of the front item in the list with the front data 
		field of List. 


1. front: 0x804c008
2. Node 1 data: 0x804c078 
3. Node 1 pre: 0x804c068
4. Node 1 next: 0x804c048
5. Node 2 data: 0x804c028
6. Node 2 pre: 0x804c088
7. Node 2 next: 0x804c068
8. Node 3 data: 0x804c058
9. Node 3 pre: 0x804c048
10. Node 3 next: 0x804c088
****************************************************************************/


#include <malloc.h>
#include <stdio.h>
#include "mylib.h"
#include "list.h"

typedef struct Node {
        struct Node * pre;      /* how to access the prior Node */
        struct Node * next;     /* how to access the next Node */
        void * data;            /* the data to store */
} Node;

typedef struct List {
        Node * front;             /* the front of the list */
        long list_count;        /* which list is it */
        long occupancy;
        void *(*copy_func) (void *);
        void (*delete_func) (void *);
        long (*is_greater_than_func) (void *, void *);
        FILE *(*write_func) (void *, FILE *);
} List;

/* private Node function declarations */
static void delete_Node (Node **, void (*delete_func) (void *));
static int find_location (List * this_list, void * element);
static Node * insert_Node (Node *, void *, void *(*copy_func) (void *)); 
static Node * new_Node (void *, void *(*copy_func) (void *));
static void * remove_Node (Node *);
static void * view_Node (Node *); 
static FILE * write_Node (Node *, FILE *, FILE *(*write_func) (void *, FILE *));

/* catastrophic error messages */
static const char ADNEXT_NONEXIST[] = 
                "Advance next from non-existent list!!!\n";
static const char ADNEXT_EMPTY[] = 
                "Advance next from empty list!!!\n";
static const char ADPRE_NONEXIST[] = 
                "Advance pre from non-existent list!!!\n";
static const char ADPRE_EMPTY[] = 
                "Advance pre from empty list!!!\n";
static const char DELETE_NONEXIST[] =
                "Deleting from non-existent list!!!\n";
static const char DELETE_NONEXISTNODE[] =
                "Deleting a non-existent node!!!\n";
static const char ISEMPTY_NONEXIST[] =
                "Is empty check from non-existent list!!!\n";
static const char INSERT_NONEXIST[] =
                "Inserting to a non-existent list!!!\n";
static const char REMOVE_NONEXIST[] =
                "Removing from non-existent list!!!\n";
static const char REMOVE_EMPTY[] =
                "Remove from empty list!!!\n";
static const char VIEW_NONEXIST[] = 
                "Viewing a non-existent list!!!\n";
static const char VIEW_NONEXISTNODE[] = 
                "Viewing a non-existent node!!!\n";
static const char VIEW_EMPTY[] =
                "Viewing an empty list!!!\n";
static const char WRITE_NONEXISTFILE[] =
                "Writing to a non-existent file!!!\n";
static const char WRITE_NONEXISTLIST[] =
                "Writing from a non-existent list!!!\n";
static const char WRITE_MISSINGFUNC[] =
                "Don't know how to write out elements!!!\n";
static const char WRITE_NONEXISTNODE[] =
                "Writing from a non-existent node!!!\n";

/* debug messages */
static const char ADNEXT[] = "[List %ld - Advancing next]\n";
static const char ADPRE[] = "[List %ld - Advancing pre]\n";
static const char INSERT[] = "[List %ld - Inserting node]\n";
static const char REMOVE[] = "[List %ld - Removing node]\n";
static const char VIEW[] = "[List %ld - Viewing node]\n";
static const char LIST_ALLOCATE[] = "[List %ld has been allocated]\n";
static const char LIST_DEALLOCATE[] = "[List %ld has been deallocated]\n";

static int debug_on = FALSE;    /* allocation of debug flag */
static long list_counter = 0;   /* the number of lists allocated so far */

/*--------------------------------------------------------------------------
Function Name:         set_debug_on
Purpose:	       Turns on debugging for this list.
Description:	       Initializes debug_on to be TRUE. 
Input:                 Nothing because the parameter is void. 
Result:                Debug state method. Nothing is returned because
		       this method is a void function. 
--------------------------------------------------------------------------*/
void set_debug_on (void) {
	/* switches debug_on to on.*/
	debug_on = TRUE;
}

/*--------------------------------------------------------------------------
Function Name:         set_debug_off
Purpose:	       Turns off debugging for this list.
Description:	       Initializes debug_on to be FALSE.
Input:                 Nothing because the parameter is void.
Result:                Debug state method. Nothing is returned because
		       this method is a void function.
--------------------------------------------------------------------------*/
void set_debug_off (void) {
	/* switches debug_on to off */
	debug_on = FALSE;
}

/*--------------------------------------------------------------------------
Function Name:         advance_next_List
Purpose:	       Calling this function causes the front pointer of 
		       this_list to move forward by one Node. This effectively
		       shifts the elements of the list forward by one.
Description:	       This method will keep incrementing the front pointer
		       so that the user can place a node/number into a 
		       specific place in the list. 
Input:                 List * this_list: A pointer to the current this_list.
Result:                Nothing is returned since this method is void; however,
		       the result of this method is that the front pointer
		       will keep advancing in the list by 1.
--------------------------------------------------------------------------*/
void advance_next_List (List * this_list) {
	/* if the list has not been created, the program will display an 
	 * error message. */
	if (this_list == NULL) {
		fprintf(stderr, ADNEXT_NONEXIST);
	}
	/* if the list does not have any number in the stack then the program
	 * will print out an error message that states it cannot advance next
	 * from an empty stack */
	if (this_list->occupancy == 0) {
		fprintf(stderr, ADNEXT_EMPTY);
	}
	/* prints the debug message with the number of list allocated */
	if (debug_on == TRUE) {
		fprintf(stderr, ADNEXT, this_list->list_count);
	}
	/* the front pointer will be the next Node of the current front
	 * pointer */
	this_list->front = this_list->front->next;
}

/*--------------------------------------------------------------------------
Function Name:         advance_pre_List
Purpose:	       Calling this function causes the front pointer of 
		       this_list to move backward by one Node. This effectively
		       shifts the elements of the list backwards by one.
Description:	       This method will keep decrementing the front pointer
		       so that the user can place a node/number into a 
		       specific place in the list. 
Input:                 List * this_list: A pointer to the current this_list
Result:                Nothing is returned since this method is void; however,
		       the result of this method is that the front pointer 
		       will keep going back in the list by 1. 
--------------------------------------------------------------------------*/
void advance_pre_List (List * this_list) {
	/* if the list has not been created, the program will display an 
	 * error message. */
	if (this_list == NULL) {
		fprintf(stderr, ADPRE_NONEXIST);
	}
	/* if the list does not have any number in the stack then the program
	 * will print out an error message that states it cannot advance pre
	 * from an empty stack */
	if (this_list->occupancy == 0) {
		fprintf(stderr, ADPRE_EMPTY);
	}

	/* prints the debug message with the number of list allocated */
	if (debug_on == TRUE) {
		fprintf(stderr, ADPRE, this_list->list_count);
	}
	/* the front pointer will be the next Node of the current front
	 * pointer */
	this_list->front = this_list->front->pre;
}

/*--------------------------------------------------------------------------
Function Name:         delete_List
Purpose:	       This destructor function deallocates all memory 
		       associated with the list, including the memory 
		       associated with all of the nodes in the list. It sets 
		       the list pointer in the calling function to NULL.
Description:	       Removes the list and whatever is in the list. Frees
		       up the memory that was with the list and nodes. 
Input:                 List ** lpp: A pointer to a pointer of the list. 
Result:                Frees up memory and sets everything to NULL. 
		       Nothing is returned. 
--------------------------------------------------------------------------*/
void delete_List (List ** lpp) {
	List * this_list;
	/* to store the data returned by remove_Node */
	void * data;
	Node * temp;
	/* if the stack has not been created or there is no stack */
	if ((!lpp || !*lpp)) {
		/* print out the debug message that the user is 
		 * deleting a stack that has not been created */
		fprintf(stderr, DELETE_NONEXIST);
		/*returns nothing so escapes the method */
		return;
	}
	this_list = *lpp;
	if (debug_on == TRUE) {
		fprintf(stderr, LIST_DEALLOCATE, this_list->list_count);
	}
	while (this_list->occupancy != 0) {
		temp = this_list->front->next;
		/* stores the return value from remove_Node */
		data = remove_Node(this_list->front);
		/* delete the data recivied from remove_Node */
		this_list->delete_func(&data);
		this_list->front = temp;
		this_list->occupancy--;
	}
	/* emptying the memory */
	free( *lpp);
	/* initialize this_list to null */
	*lpp = NULL;
	this_list->list_count--;
}

/*--------------------------------------------------------------------------
Function Name:         find_location
Purpose:	       find_location should be used to locate where the node 
		       should be in a sorted list. If your implementation of
		       find_location changes the front pointer of the list, be
		       sure to save that value before calling this function. 
		       Note: you have the flexibility to change the signature 
		       of this function to have a different return value or 
		       parameters.
Description:	       This function places the right element that the user
		       has typed in to a correct location in the stack by 
		       checking if the number that the user has typed in
		       has a higher value than the number that the front
		       pointer has. If the number has a higher value then
		       calls the advance_next_List method until it is 
		       smaller than the data number that the front pointer
		       is carrying. 
Input:                 List * this_list: A pointer to this current list. 
		       void * element: Anything that can be passed to this 
		       function by the user. 
Result:                Returns TRUE if this method has worked correctly. 
		       The results change depending on the element that 
		       the user has inputted. 
--------------------------------------------------------------------------*/
static int find_location (List * this_list, void * element) {
	int count = 0;
	/* a while loop that keep running until the number that the front
	 * pointer is holding is bigger than element being passed and 
	 * and until there is no more numbers to check */ 
	while (this_list->is_greater_than_func(element, this_list->front->data)
		&& count < this_list->occupancy ) {
		/* calls the advance_next_List method to check the next front
		 * pointer */
		advance_next_List(this_list);
		count++;
	}
	/* to check if there needs to be a new node at the front or not */
	if (count > 0) {
		return FALSE;
	}
	return TRUE;
}

/*--------------------------------------------------------------------------
Function Name:         insert
Purpose:	       Inserts the element into this_list either at the front,
		       end or in sorted form. Find_location is used to 
		       locate where the node should go in the list when the 
		       user wants the input number sorted in the list. 
		       This function should then call insert_Node to 
		       incorporate the Node into the list. 
Description:	       This method will insert a node by calling the 
		       insert_Node method. If there isn't any Nodes in the 
		       list, then that Node will be the front pointer. However,
		       when there are other Nodes in the list, the user can 
		       input "1" at the terminal to initialize and place
		       a new Node to be the front pointer. '2' will sort 
		       the number inputted into a specific place where the 
		       number is between a higher value number and bigger than
		       the lower value number by calling the Find_location 
		       function. '0' will place the number inputted into
		       the end of the list. Every time the user inserts
		       the occupancy in this list will grow by 1. 
Input:                 List * this_list: A pointer to the current this_list.
		       void * element: Any value/character/object that the user
		       has inputted 
		       long where: A long value, '1','2','0' for this program,
		       that will take in the number that the user has typed
		       in. 
Result:                Returns TRUE if this method has worked perfectly. 
		       Depending on the number the user types in for where, 
		       the insert will happen at a different location. 
--------------------------------------------------------------------------*/
long insert (List * this_list, void * element, long where) {
	/* saving the current front pointer */
	Node * temp = this_list->front; 
	/* if the list has not been created, the program will display an 
	 * error message. */
	if (this_list == NULL) {
		fprintf(stderr, INSERT_NONEXIST);
		return FALSE;
	}
	/* prints the debug message with the number of list allocated */
	if (debug_on == TRUE) {
		fprintf(stderr, INSERT, this_list->list_count);
	}
	/* if there are no Nodes in the list */
	if (this_list->occupancy == NULL) {
		/* the front pointer of this list will be the return
		 * Node from the insert_Node method */
		this_list->front = insert_Node(this_list->front, element, 
					this_list->copy_func);
		/* the occupancy in the list increases by 1 */
		this_list->occupancy++;
	}
	/* if there are Node(s) in the list */
	else {
		/* if the user types in '1' to the terminal */
		if (where == 1) {
			/* the front pointer of this list will have a new
			 * front pointer that is going to be the return
			 * Node from the insert_Node method */
			this_list->front = insert_Node(this_list->front, 
						element, this_list->copy_func);
		}
		/* if the user types in '2' to the terminal */
		if (where == 2) {
			/* first calls the find_location method to correctly
			 * place the new insert in the correct spot in the 
			 * list */
			if (find_location(this_list, element) == TRUE) {
				this_list->front = insert_Node(this_list->front,
						element, this_list->copy_func);
			}
			else {
				/* calls the insert_Node method to correctly 
				* insert the new Node and align the nodes 
				* correctly */
				insert_Node(this_list->front, element, 
					this_list->copy_func);
				/* to go back to the original front pointer */
				this_list->front = temp;
			}
		}
		/* if the user types in '0' to the terminal */
		if (where == 0) {
			/* just insert the Node to the end because every
			 * insert is before the front pointer */
			insert_Node(this_list->front, element, 
				this_list->copy_func);
		}
		/* the occupancy in the list increase by 1 */
		this_list->occupancy++;
	}
	return TRUE;
}
 
/*--------------------------------------------------------------------------
Function Name:         isempty_List
Purpose:               Returns true if this_list is empty, and false if it is
		       not.
Description:	       If the occupancy of the list is zero, which 
		       means that no numbers are stored in it, then returns 
		       TRUE. Otherwise, this method returns false. 
Input:                 List * this_list: Calls/points to the current list 
		       that the user is operating on. 
Result:                Returns true if the current list is empty else returns
		       false to notifiy that it has a number in it. 
--------------------------------------------------------------------------*/
long isempty_List (List * this_list) {
	/* if the list has not been created, the program will display an 
	 * error message. */
	if (this_list->list_count == 0) {
		fprintf(stderr, ISEMPTY_NONEXIST);
		return TRUE;
	}
	/* if the list is empty then it returns false */
	if (this_list->occupancy == NULL) { 
		return TRUE;
	}
	return FALSE;
}

/*--------------------------------------------------------------------------
Function Name:	       new_List
Purpose:	       This constructor function allocates and initializes a 
		       new List object. It initializes the list data fields, 
		       and returns a pointer to the list. All new lists should
		       be empty.
Description:	       Creates a new list that comes with a front pointer,
		       copy_func, and occupancy, which are initialized to zero.
		       Every time a new list is created the list count 
		       increases by 1. 
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
Result:                Returns the created list with all the parameters
		       in it. 
--------------------------------------------------------------------------*/
List * new_List (
        void *(*copy_func) (void *),
        void (*delete_func) (void *),
        long (*is_greater_than_func) (void *, void *),
	FILE *(*write_func) (void *, FILE *)) {
	/* allocate */
	List * this_list = (List *)malloc(sizeof(List)); 
	/* initialize */
	this_list->front = NULL;
	this_list->copy_func = NULL;
	this_list->occupancy = NULL;
	/* incrementing */
	list_counter++;
	this_list->list_count = list_counter;
	/* prints the debug message with the number of list allocated */
	if (debug_on == TRUE) {
		fprintf(stderr, LIST_ALLOCATE, this_list->list_count);
	}
	/* setting each function to the functions in the list */
	this_list->copy_func = copy_func;
	this_list->delete_func = delete_func;
	this_list->is_greater_than_func = is_greater_than_func;
	this_list->write_func = write_func;
	return this_list; 
}

/*--------------------------------------------------------------------------
Function Name:         remove_List
Purpose:	       Removes an element in this_list at location where. 
		       This function should call remove_Node to restructure 
		       the list to remove the node.
Description:	       Calls the remove_Node method so that a Node can be 
		       removed from the list. 
Input:                 List * this_list: A pointer to the current list that
		       has been created. 
		       long where: A long that is taking in the value that
		       the user has inputted. 
Result:                Returns the new list after removing the Node; however,
		       if there is nothing in the list or the list has not 
		       been created, then the returns False. 
--------------------------------------------------------------------------*/
void * remove_List (List * this_list, long where) {
	Node * value;
	/* if the list has not been created, the program will display an 
	 * error message. */
	if (this_list == NULL) {
		fprintf(stderr, REMOVE_NONEXIST);
		return FALSE;
	}
	/* if there are no Nodes in the list */
	if (this_list->occupancy == NULL) {
		fprintf(stderr, REMOVE_EMPTY);
		return FALSE;
	}
	/* prints the debug message with the number of list allocated */
	if (debug_on == TRUE) {
		fprintf(stderr, REMOVE, this_list->list_count);	
	}
	/* if the user types in '1' to the terminal */
	if (where == 1) {
		this_list->front = this_list->front->next;
		/* the front pointer of this list will have a new
		 * front pointer that is going to be the return
		 * Node from the insert_Node method */
		value = remove_Node(this_list->front->pre);
	}
	/* if the user types in '0' to the terminal */
	if (where == 0) {
		/* just insert the Node to the end because every
		 * insert is before the front pointer */
		value = remove_Node(this_list->front->pre);
	}
	/* the occupancy in the list decrease by 1 */
	this_list->occupancy--;
	return value;
}

/*--------------------------------------------------------------------------
Function Name:         view
Purpose:	       Returns a pointer to the object stored at location 
		       where for viewing. This function should call view_Node,
		       which returns the data.
Description:	       This method will allow the user to view the number 
		       in the node by calling the view_Node function. 
		       If the user inputs "1" at the terminal then the user
		       will be able to see the front number and if the
		       user inputs '0', the user will be allowed to see the
		       end number that's stored in the node. 
Input:                 List * this_list: A pointer to the current list.
		       long where: A long that takes in the value of what
		       the user has inputted. 
Result:                Result changes depending on what's at the front
		       or end of the list. The return value is the 
		       return value of the view_Node function, the data 
		       that's stored inside the node.
--------------------------------------------------------------------------*/
void * view (List * this_list, long where) {
	/* if the list has not been created, the program will display an 
	 * error message. */
	if (this_list == NULL) {
		fprintf(stderr, VIEW_NONEXIST);
		return FALSE;
	}
	/* if the list does not have any number in the stack then the program
	 * will print out an error message that states it cannot view
	 * from an empty stack */
	if (this_list->occupancy == NULL) {
		fprintf(stderr, VIEW_EMPTY);
		return FALSE;
	}
	/* prints the debug message with the number of list allocated */
	if (debug_on == TRUE) {
		fprintf(stderr, VIEW, this_list->list_count);
	}
	/* if the user types in '1' to the terminal */
	if (where == 1) {
		/* allows to view the data inside the front pointer */
		view_Node(this_list->front);
		/* returns the data of the front pointer */
		return view_Node(this_list->front);
	}
	else {
		/* allows to view the data inside the previous front pointer */
		view_Node(this_list->front->pre);
		/* returns the data of the node at the end of the list */
		return view_Node (this_list->front->pre);
	}
}

FILE * write_List (List * this_list, FILE * stream) {
        long count;             /* to know how many elements to print */
        Node * working;                 /* working node */

        if (!stream) {
                fprintf (stderr, WRITE_NONEXISTFILE);
                return NULL;
        }

        if (!this_list) {
                fprintf (stderr, WRITE_NONEXISTLIST);
                return NULL;
        }

        if (stream == stderr)
                fprintf (stream, "List %ld has %ld items in it.\n",
                        this_list->list_count, this_list->occupancy);

        if (!this_list->write_func) {
                fprintf (stream, WRITE_MISSINGFUNC);
                return stream;
        }

        if (this_list->occupancy >= 1)
                working = this_list->front;

        for (count = 1; count <= this_list->occupancy; count++) {
                if (stream == stderr)
                        fprintf (stream, "\nelement %ld:  ", count);
                write_Node (working, stream, this_list->write_func);
                working = working->next;
        }
                
        return stream;
}

/*--------------------------------------------------------------------------
Function Name:         write_reverse_List:  
Purpose:	       Writes the elements of this_list backwards, starting 
	               with the last item. The list is printed to filestream
		       stream.
Description:	       Prints out the reverse order of the list by going
		       back from the end of the list to the first of the list.
Input:                 List * this_list: A pointer to the current list 
		       File * stream: A pointer to the output of the File. 
Result:                Result will change depending on what numbers and how
		       many nodes are in the list. Returns the output. 
--------------------------------------------------------------------------*/
FILE * write_reverse_List (List * this_list, FILE * stream) {
        Node * working; 
	long count;
	/* if there is a Node inside the list */
	if (this_list->occupancy >= 1)
		/* working will equal the Node that's in the end */
                working = this_list->front->pre;
	/* runs a for loop that prints out the Nodes backwards in the 
	 * list */ 
        for (count = 1; count <= this_list->occupancy; count++) {
                if (stream == stderr)
                        fprintf (stream, "\nelement %ld:  ", count);
                write_Node (working, stream, this_list->write_func);
                working = working->pre;
        } 
        return stream;
}

/* a more readable delete_Node method: use a "this_Node" local pointer */
static void delete_Node (Node ** npp, void (*delete_func) (void *)) {
	
	Node * this_Node;

        /* does the node exist??? */
        if (!npp || !*npp) {
                fprintf (stderr, DELETE_NONEXISTNODE);
                return;
        }
	
	this_Node= *npp;

        /* call function to delete element */
        if (delete_func && (*npp)->data)
                (*delete_func) (&((*npp)->data));

        /* delete element */
        free (*npp);

        /* assign node to NULL */
        *npp = NULL;
}


/*--------------------------------------------------------------------------
Function Name:         Node * insert_Node
Purpose:	       Creates a new node to hold element, or, if copy_func is
		       non-NULL, a copy of element. This new node is then 
		       incorporated into the list at the location BEFORE 
		       this_Node.
Description:	       Attaches the Node that has been created with the other
		       Nodes and moves the previous attachment to the correct
		       Nodes. 
Input:                 Node * this_Node: A pointer to the current node. 
		       void * element: Any element being passed to the function
		       void * (*copy_func) (void *): A copy of the element. 
Result:                Returns the Node with the attachments. Result changes
		       depending there is a Node already created or not. 
--------------------------------------------------------------------------*/
static Node * insert_Node (Node * this_Node, void * element, 
        void * (*copy_func) (void *)) {
	

	/* at the very beginning when there is no Nodes */
	if (this_Node == NULL) {
		/* first creates a node storing in the element */
		this_Node = new_Node(element, copy_func);
		/* the pre and the next only points to this list */
		this_Node->pre = this_Node; 
		this_Node->next = this_Node;
		return this_Node;
	}
	/* if there are at least one Node in the list */ 
	else {
		Node * working = new_Node(element, copy_func);
		/* the new created Node will point next to the 
		 * Node that was last created */
		working->next = this_Node;
		/* the new created Node will point back to the Node
		 * that was the previous created of the last created */
		working->pre = this_Node->pre;
		/* the last created will point back to the new created Node */
		working->next->pre = working;
		/* the second to the last created will point next to the new
		 * created Node */
		working->pre->next = working; 
		return working;
	}
}

static Node* new_Node (void * element, void * (*copy_func) (void *)) {

        /* allocate memory */
        Node *this_Node = (Node *) malloc (sizeof (Node));

        /* initialize memory */
        this_Node->next = this_Node->pre = NULL;
	/* if the copy_func is true do copy_func element, else
	 * element */ 
        this_Node->data = (copy_func) ? (*copy_func) (element) : element;

        return this_Node;
}

/*--------------------------------------------------------------------------
Function Name:         remove_Node
Purpose:	       "Unlinks" this_Node from the list by arranging the 
		       pointers of the surrounding Nodes so they no longer 
		       point to this_Node. The memory associated with the Node
		       object is freed, but the Node's data is not deleted. 
		       A pointer to the data is returned.
Description:	       Deattaches a Node correctly so that every other
		       Nodes are still correctly attached to each other. 
Input:                 Node * this_Node: A pointer to the current Node. 
Result:                Returns the data of the delete Node but does not
		       allow access to it. 
--------------------------------------------------------------------------*/
static void * remove_Node (Node * this_Node) {
	/* saving the previous data so that it can be called later. */
	Node * temp = this_Node->data; 
	/* deattaches the current node and attaching the current front node
	 * to the previous node of the current node */
	this_Node->next->pre = this_Node->pre;
	/* deattaches the current node and attaching the current previous
	 * node to the next node of the current node */
	this_Node->pre->next = this_Node->next; 
	/* deletes the Node */
	delete_Node(&this_Node, NULL);
	return temp;
}

/*--------------------------------------------------------------------------
Function Name:         view_Node:
Purpose:	       Returns a pointer to this_Node's data
Description:	       Returns the pointer to the current Node's data. 
Input:		       Node * this_Node: A pointer to the current Node.
Result:                Returns the number that's in the Node. The result
		       might change depending on which Node it is being
		       called for. 
--------------------------------------------------------------------------*/
static void * view_Node (Node * this_Node) {
	/* returns the number inside the Node */
	return this_Node->data;
}

static FILE* write_Node (Node * this_Node, FILE * stream,
        FILE * (*write_func) (void *, FILE *)) {

        if (!stream) {
                fprintf (stderr, WRITE_NONEXISTFILE);
                return NULL;
        }

        if (!this_Node) {
                fprintf (stream, WRITE_NONEXISTNODE);
                return stream;
        }

        if (!write_func) {
                fprintf (stream, WRITE_MISSINGFUNC);
                return stream;
        }

        return (*write_func) (this_Node->data, stream);
}
