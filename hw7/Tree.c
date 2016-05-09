/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        February 18, 2015
                                                        cs12xbo
                                Assignment Seven

File Name:      Tree.c
Description:    Creates a tree and TNode that will take in multiple 
element/object that the user will input to the terminal. Each element/object
that the user inputs will go into a TNode that will be connected with another
TNode, creating parent and children. Height and balance will also be adjusted
every time a TNode is created. 
****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string.h>
#include "Tree.h"
using namespace std;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static const char ALLOCATE[] = " - Allocating]\n";
static const char DEALLOCATE[] = " has been deallocated]\n";
static const char AND[] = " and ";
static const char COMPARE[] = " - Comparing ";
static const char INSERT[] = " - Inserting ";
static const char TREE[] = "[Tree ";

struct TNode {
	Base * data;
	TNode * left, * right, *parent;
	static long occupancy;
        unsigned long hasBeenDeleted;

	// left child's height - right child's height
	long balance;

	// 1 + height of tallest child, or 0 for leaf
	long height;

	/*******************************************************************
	% Routine Name : TNode (public)
	% File :         tree.c
	% 
	% Description :  A constructor for a TNode
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% element		Any object that will take in whatever the user
	%			types into the system. 
	********************************************************************/
	TNode (Base * element) : data (element), left (0), right (0),
	        parent (0), hasBeenDeleted (FALSE), balance (0), height(0) {
		// increase the occupancy by one
		occupancy++;
	}

	/******************************************************************
	% Routine Name : ~TNode (public)
	% File :         tree.c
	% 
	% Description :  A destructor for a TNode
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% void		Nothing.
	********************************************************************/
	~TNode (void) {
		delete data; // delete the data of that TNode
		left = NULL; // setting the left to NULL
		right = NULL; // setting the right to NULL
		parent = NULL; // setting the parent to NULL
		occupancy--; //occupancy decrements by one
	}
        ostream & Write (ostream & stream) const {
                stream << "at height:  " << height << "  with balance:  "
			<< balance << "  ";
		return data->Write (stream) << "\n";
        }
	ostream & Write_AllTNodes (ostream & stream) const {
		if (left)
			left->Write_AllTNodes (stream);
		if (!hasBeenDeleted)
			Write (stream);
		if (right)
			right->Write_AllTNodes (stream);

		return stream;
	}

	/********************************************************************
	% Routine Name : delete_AllTNodes (public)
	% File :         tree.c
	% 
	% Description :  A destructor for all the TNodes
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% void		Nothing. 
	*******************************************************************/
	void delete_AllTNodes (void) {
		// a recursion for the left. If there is a left
		if (left)
			// go to the left and call on the delete_AllTNodes() 
			// method
			left->delete_AllTNodes();
		// if there is a right
		if (right)
			// go to the right and call on the delete_AllTNodes()
			// method
			right->delete_AllTNodes();
		// finally delete the current TNode
		delete this;
	}
};

// initialization of static data fields of Tree
long TNode :: occupancy = 0;
bool Tree :: debug_on = 0;

/***************************************************************************
% Routine Name : Tree :: Set_Debug (public)
% File :         tree.c
% 
% Description :  This function sets debug mode on or off
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% option             true should set debug mode on, false should set debug
%                    mode off.
***************************************************************************/
void Tree :: Set_Debug (bool option) {
	// if the option is zero
        if (option == 0) {
		// debug_on is false.
		debug_on = false;
	}
	else
		// debug_on is true. 
		debug_on = true;
}

Tree :: Tree (const char * name) : root (0), tree_name (strdup (name))
/***************************************************************************
% Routine Name : Tree :: Tree  (public)
% File :         Tree.c
% 
% Description :  Initializes root pointer to NULL, and occupancy to 0.
***************************************************************************/
{
	// the user turns on debug
	if (debug_on == true) {
		// print out the debug message about the tree with the 
		// tree name being allocated. 
		cerr << TREE << tree_name << ALLOCATE;
	}
}

Tree :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
	// if there is a root 
	if (root != NULL) 
		// start from the root and call the delete_AllTNodes() method
		root->delete_AllTNodes();
	// finally free/delete the pointer to the tree name. 
	free((char*) tree_name);
}	/* end: ~Tree */

/***************************************************************************
% Routine Name : Tree :: Insert (public)
% File :         tree.c
% 
% Description :  This function inserts the TNode to the tree alphabetically 
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element		Any object that the user has typed into the terminal 
***************************************************************************/
unsigned long Tree :: Insert (Base * element) {
	// creating a TNode working that will be set to root at the
	// beginning	
	TNode *working = root;
	// creating two long temporary heights that will take in the
	// values of left and right height. 
	long leftHeight;
	long rightHeight;
	// if there is no root at the beginning
	if (root == NULL) {
		// setting root to a new created TNode with the element
		// that the user has typed to the terminal. 
		root = new TNode(element);
		// if the debug is on
		if (debug_on == true) {
			// Prints out the debug message that states
			// that the name that the user has inputted 
			// has been inserted. 
			cerr << TREE << tree_name << INSERT 
			<< (char*) (*element) << ']' << '\n';
		}
		return true;
	}
	// a while loop that works only if the current TNode is present 
	// in the tree. 
	while (working != NULL) {
		// if the user turns on debug 
		if (debug_on == true) {
			// prints out the debug message that will
			// state the tree is comparing the element
			// that the user has inputted with the
			// element that is stored in the tree.
			cerr << TREE << tree_name << COMPARE 
			<< (char*) (*element) << AND <<
			(char*) (*working->data) << ']' << '\n';
		}
		// if the element that the user has inputted is same
		// as the one that is already stored in the tree
		if ((*element) == (*working->data)) {
			// if the TNode has already been removed. 
			if (working->hasBeenDeleted == true) {
				delete working->data;
				// just turn on the current TNode to be 
				// not removed. 
				working->hasBeenDeleted = false;
				// increment occupancy because occupancy
				// has been decremeted by remove method. 
				TNode :: occupancy++;
			}
			delete working->data;
			// then element will just overrides the data in the
			// current TNode. 
			working->data = element;
			break;
		}
		// however, if the element that the user has
		// inputted has a greater value than the one that is
		// stored, then attaches as a bottom right child. 
		else if ((*element) > (*working->data)){
			// if the current TNode does not have a
			// bottom right child
			if (working->right == NULL) {
				// if the user turned on the debug
				// message
				if (debug_on == true) {
					// prints out the debug
					// message about inserting
					// the element that the user
					// has typed. 
					cerr << TREE 
					<< tree_name << INSERT 
					<< (char*) (*element) << ']' << '\n';
				}
				// then the bottom right child of 
				// the current TNode will be created
				// with the element that the user
				// has inputted. 
				working->right = new TNode(element);
				// the parent of that child will
				// be the current TNode. 
				working->right->parent = working;
				break;
			}
			// if there is something at the bottom right
			// of the current TNode. 
			else
				// then working will be
				// that bottom right child and
				// goes through the while loop
				// again.
				working = working->right;
		}
		// if the element that is being passed in does not
		// have a greater value than the one that is stored.
		else {
			// if the current TNode does not have a
			// left bottom child
			if (working->left == NULL) {
				// if the user turns on debug 
				if (debug_on == true) {
					// prints out the debug
					// message about inserting
					// the element that the user
					// has typed. 
					cerr << TREE 
					<< tree_name << INSERT 
					<< (char*) (*element) << ']' << '\n';
				}
				// then the bottom left child of 
				// the current TNode will be created
				// with the element that the user
				// has inputted. 
				working->left = new TNode(element);
				// the parent of that child will
				// be the current TNode. 
				working->left->parent = working;
				break;
			}
			// if there is something at the bottom left
			// of the current TNode.
			else
				// then working will be
				// that bottom left child and
				// goes through the while loop
				// again.
				working = working->left;
		}
	}
	// while the current TNode is there
	while (working != NULL) {
		leftHeight = -1; // setting the left height to -1
		rightHeight = -1; // setting the right height to -1
		// if there is a left child of the current TNode
		if (working->left != NULL) {
			// setting the leftHeight to the left
			// TNode's height.
			leftHeight = working->left->height;
		}
		// if there is a right child of the current TNode.
		if (working->right != NULL) {
			// setting the rightHeight to the right
			// TNode's height. 
			rightHeight = working->right->height;
		}
		// if the leftHeight is greater or equal to the
		// rightHeight 
		if (leftHeight >= rightHeight) {
			// then that current TNode's height
			// equals to the leftHeight plus one.
			working->height = leftHeight + 1;
		}
		// if the rightHeight is greater than the
		// leftHeight 
		if (rightHeight > leftHeight) {
			// then the current TNode's height will
			// equal to the rightHeight plus one. 
			working->height = rightHeight + 1;
		}
		// the current TNode's balance will be leftHeight
		// minus rightHeight. 
		working->balance = leftHeight - rightHeight;
		// The current TNode's parent will now the current
		// TNode.
		working = working->parent;
	}
        return true;
}

/***************************************************************************
% Routine Name : Tree :: Lookup (public)
% File :         tree.c
% 
% Description :  This function looks for a TNode that has the same element 
%		 that the user has inputted into the system.  
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element		Any object that the user has typed into the terminal
***************************************************************************/
const Base * Tree :: Lookup (const Base * element) const {
	// creating a TNode called working and setting to the root. 
	TNode *working = root;
	// a while loop that runs only if the current TNode has
	// been created. 
	while (working != NULL) {
		// if the user turns on debug
		if (debug_on == true) {
			// prints out the debug message that
			// compares the element name that the user
			// has inputted to the store name of the
			// TNode.
			cerr << TREE << tree_name << COMPARE 
			<< (char*)(*element) << AND <<
			(char*)(working->data) << ']' << '\n';
		}
		// if the object that the user has inputted has the
		// similar value to the TNode data. 
		if ((*element) == (*working->data)) {
			// if the TNode's hasBeenDeleted is false
			if (working->hasBeenDeleted == false) {
				// return the data of that TNode.
				return working->data;
			}
			else 
				return NULL;
		}
		// if the element has a greater value than the 
		// data of the current TNode.
		else if ((*element) > (*working->data)) {
			// the right child of that current TNode
			// will now be the current TNode 
			working = working->right;
		}
		else 
			// the left child of that current TNode will
			// now be the current TNode
			working = working->left;
	}
        return NULL;    // not there
}

/***************************************************************************
% Routine Name : Tree :: Remove (public)
% File :         tree.c
% 
% Description :  This function lazy removes the element that is in the tree.  
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element		Any object that the user has typed into the terminal 
***************************************************************************/
Base * Tree :: Remove (const Base * element) {
        // creating a TNode working that is set to root.
	TNode *working = root;
	// while the current TNode is there. 
	while (working != NULL) {
		// if the user turns on debug
		if (debug_on == true) {
			// print out the debug message that states
			// that the system is comparing the name
			// that the user has inputted to the name
			// that is stored in the tree. 
			cerr << TREE << tree_name << COMPARE 
			<< (char*) (*element) << AND <<
			(char*) (working->data) << ']' << '\n';
		}
		// if the object that the user has typed into the
		// terminal is equal to the data of the current
		// TNode and that current TNode's hasBeenDeleted is 
		// at false.
		if ((*element) == (*working->data) &&
		working->hasBeenDeleted == false) {
			// turn that current TNode's hasBeenDeleted
			// to true
			working->hasBeenDeleted = true;
			// decrement the occupancy of the tree
			TNode :: occupancy--;
			// return the data of the current TNode
			return working->data;
		}
		// if the element that the user has inputted is
		// greater than the data of the current TNode
		else if ((*element) > (*working->data)) {
			// the right child of the current TNode will
			// now be the current TNode. 
			working = working->right;
		}
		else 
			// the left child of the current TNode will
			// now be the current TNode. 
			working = working->left;
	}
        return NULL;    // not there
}

ostream & Tree :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree :: Write (public)
% File :         Tree.c
% 
% Description : This function will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/

{
        stream << "Tree " << tree_name << ":\n"
		<< "occupancy is " << TNode :: occupancy << " elements.\n";

	return (root) ? root->Write_AllTNodes (stream) : stream;
}       /* end: Write */

