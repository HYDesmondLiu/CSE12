/****************************************************************************
                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        February 27, 2015
                                                        cs12xbo
                                Assignment Eight

File Name:      Tree.c
Description:    Tree.c will implement a binary tree as did Tree.java in hw7,
		but Tree.c will implement a proper remove as well as a
		threshold check to maintain the appropriate balance of the 
		tree, which is -3/3. This program will also correctly adjust
		the height and balance of the TNodes whenever a TNode is 
		removed, replaced, or inserted. 
****************************************************************************/

#include <cstdlib>
#include <string>
#include "Tree.h"
using namespace std;

// messages
static const char AND[] = " and ";
static const char COMPARE[] = " - Comparing ";
static const char DEALLOCATE[] = " - Deallocating]\n";
static const char INSERT[] = " - Inserting ";
static const char REPLACE[] = " - Replacing ";
static const char UPDATE[] = " - Updating ";

template <class Whatever>
int Tree<Whatever>::debug = 0;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define THRESHOLD 2

template <class Whatever>
ostream & operator << (ostream &, const TNode<Whatever> &);

template <class Whatever>
struct TNode {
        long balance;
        Whatever data;
        long height;
        TNode<Whatever> * left;
        long & occupancy;
        TNode<Whatever> * right;
        unsigned long & tree_count;
       
       	/*******************************************************************
	% Routine Name : TNode (public)
	% File :         Tree.c
	% 
	% Description :  Called when creating any other TNodes.
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% Whatever & element:		A reference to the element that the 
	%				user has typed into the terminal. 
	% Tree<Whatever> & theTree:	A reference to the Tree.
	*******************************************************************/
        TNode (const Whatever & element, Tree<Whatever> & theTree)
                : balance (0), data (element), height (0), left (0), 
                occupancy (theTree.occupancy), right (0), 
                tree_count (theTree.tree_count) {
                // increase the occupancy by one whenever this constructor
		// is called. 
		occupancy++;
        }
        
	/*******************************************************************
	% Routine Name : TNode (public)
	% File :         Tree.c
	% 
	% Description :  Called when creating the root TNode
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% Whatever & element:		A reference to the element that the 
	%				user has typed into the terminal.
	% Tree<Whatever> & parentTNode: A reference to the parent of this
	%				TNode that will be created with this
	%				method.
	*******************************************************************/
        TNode (const Whatever & element, TNode<Whatever> & parentTNode)
        : balance (0), data (element), height (0), left (0), 
                occupancy (parentTNode.occupancy), right (0), 
                tree_count (parentTNode.tree_count) {
                // increasing the occupancy by one.
		occupancy++;
        }

	/*******************************************************************
	% Routine Name : ~TNode (public)
	% File :         Tree.c
	% 
	% Description : Called when deallocating a TNode.
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% void				Nothing.
	*******************************************************************/
        ~TNode (void) {
		left = NULL; // setting the left to NULL
		right = NULL; // setting the right to NULL
		occupancy--; //occupancy decrements by one
	}

	/*******************************************************************
	% Routine Name : delete_AllTNodes (public)
	% File :         Tree.c
	% 
	% Description :  Performs a post-order traversal through the Tree 
	%		 deleting each TNode.
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% void				Nothing. 
	*******************************************************************/
        void delete_AllTNodes (void) {
		// a recursion for the left. If there is a left
		if (left)
			// go to the left and call on the delete_AllTNodes() 
			// method.
			left->delete_AllTNodes();
		// a recursion for the right. if there is a right
		if (right)
			// go to the right and call on the delete_AllTNodes()
			// method.
			right->delete_AllTNodes();
		// finally delete the current TNode.
		delete this;
        }

        unsigned long Insert (const Whatever & element, 
                              TNode<Whatever> *& PointerInParent);

        // OPTIONAL TNode :: Lookup => uncomment if implementing recursively
        // unsigned long Lookup(Whatever & element) const;


	/********************************************************************
	% Routine Name : ReplaceAndRemoveMax (public)
	% File :         Tree.c
	% 
	% Description : Called when removing a TNode with 2 children, replaces
	%		that TNode with the maximum TNode in its left subtree
	%		to maintain the Tree structure.
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% TNode<Whatever> & targetTNode:A reference to the TNode that we are
	%				trying to remove.
	% TNode<Whatever> *& PointerInParent:
	%				A reference to the TNode's parent
	%				that is used to traverse to the the
	%				current TNode.
	*******************************************************************/
        void ReplaceAndRemoveMax (TNode<Whatever> & targetTNode, 
                TNode<Whatever> *& PointerInParent){
                // if the user turns on debug
		if (Tree<Whatever>::debug == 1) {
			// a debug message about comparing the predecessor 
			// of the targetTNode pops out.
			cerr << TREE << tree_count << COMPARE <<
			(const char *) (data) << ']' << '\n';
			// a debug message will pop out with a replace 
			// statment about the predecessor replacing the TNode
			// with two children. 
			cerr << TREE << tree_count << REPLACE <<
			(const char *) data << ']' << '\n';
		}
		// if there is a right 
		if (right) {
			// recursively call the ReplaceAndRemoveMax method
			// to keep going right until there is no more 
			// right child. 
			right->ReplaceAndRemoveMax(targetTNode, right);
			// call the SetHeightAndBalance method to correctly
			// set the height and balance as it goes back up.
			SetHeightAndBalance(PointerInParent);
		}
		else {
			// overwriting the one being replaced with the data of
			// the parent.
			targetTNode.data = data;
			// setting the pointer to parent to the left. 
			PointerInParent = left;
			// delete the child that is going to replace the TNode
			// being removed. 
			delete this;
		}
        }

	/*******************************************************************
	% Routine Name : Remove (public)
	% File :         Tree.c
	% 
	% Description : Removes the matching data from the binary tree. 
	%		Returns true or false indicating success of removal.
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% TNode<Whatever> & elementTNode:
	%				A reference to the TNode containing 
	%				the data that identifies the element
	%				to be removed.
	% TNode<Whatever> *& PointerInParent:
	%				A reference to the TNode pointer in 
	%				the parent TNode used to get to the 
	%				current TNode.
	% long fromSHB = FALSE:		True or false, keeping track of	
	%				whether or not Remove was called 
	%				from SetHeightAndBalance so that 
	%				Remove can determine whether or not 
	%				to call SetHeightAndBalance.
	*******************************************************************/
        unsigned long Remove (TNode<Whatever> & elementTNode, 
                TNode<Whatever> *& PointerInParent,
                long fromSHB = FALSE){
                // if the user turns on debug
		if (Tree<Whatever>::debug == 1) {
			// a debug message about comparing the element, that
			// the user wants to remove, to the element that is
			// in the tree. 
			cerr << TREE << tree_count << COMPARE <<
			(const char*) elementTNode.data
			<< AND << (const char *) (data) << ']' << '\n';
		}
		// if there is a match
		if (elementTNode.data == data) {
			// first store that data into the elementTNode
			elementTNode.data = data;
			// if the element in the tree does not have any 
			// child
			if (left == NULL && right == NULL) {
				// delete the one in the Tree
				PointerInParent = NULL;
				delete this;
				return true;
			}
			// else if there is a left child but not a right 
			// child
			else if (left != NULL && right == NULL) {
				// traverse left one more, setting a proper
				// connection from the TNode before the TNode
				// we are trying to remove to the TNode's left
				// child of the TNode we are trying to remove.
				PointerInParent = left;
				// then delete the TNode we are trying to 
				// remove.
				delete this;
				return true;
			}
			// else if there is a right child but not a left child
			else if (left == NULL && right != NULL) {
				// traverse right one more, setting a proper
				// connection from the TNode before the TNode
				// we are trying to remove to the TNode's right
				// child of the TNode we are trying to remove.
				PointerInParent = right;
				// then delete the TNode we are trying to 
				// remove.
				delete this;
				return true;
			}
			// if there is a right and left child 
			else 
				// go left once and call the 
				// ReplaceAndRemoveMax to properly 
				// replace and remove the TNode we are 
				// trying to replace and remove.
				left->ReplaceAndRemoveMax(*this, left);
				return true;
		}
		// if the element that the user has typed into the terminal is
		// bigger than the data that is in the TNode, in the tree. 
		else if (elementTNode.data > data) {
			// recurisively go right until the method returns true
			// and if there is a right.
			if (right &&
			right->Remove(elementTNode, right, fromSHB) == true){
				// if the method is not called from SHAB then 
				// call the SHAB method.
				if (fromSHB == false) {
					// SHAB going back up the tree after
					// the removal
					SetHeightAndBalance(PointerInParent);
				}	
				return true;
			}
		}
		// if the element that the user has typed into the terminal 
		// is smaller than the data that is in the TNode, in the tree.
		else {
			// recurisibely go left until the method returns true
			// and if there is a left.
			if (left &&
			left->Remove(elementTNode, left, fromSHB) == true) {
				// if the method is not called from SHB then
				// call the SHAB method. 
				if (fromSHB == false) {
					// SHAB going back up the tree after 
					// the removal
					SetHeightAndBalance(PointerInParent);
				}
				return true;
			}
		}
		return false;
	}

	/*******************************************************************
	% Routine Name : SetHeightAndBalance (public)
	% File :         Tree.c
	% 
	% Description : Updates the height and balance of the current TNode.
	%
	% Parameters descriptions :
	% 
	% name               description
	% -------------- ---------------------------------------------------
	% TNode<Whatever> *& PointerInParent:
	%				A reference to the TNode pointer in
	%				the parent TNode used to get to the
	%				current TNode.
	*******************************************************************/
	void SetHeightAndBalance (TNode<Whatever> *& PointerInParent) {
		long leftHeight = -1; // setting the left height to -1
		long rightHeight = -1; // setting the right height to -1
		// creating a temporary RTS TNode<Whatever> that has 
		// the data and the connection
		// if the user turns on debug
		if (Tree<Whatever>::debug == 1) {
			// print out the debug message about updating 
			// the SHAB of the current TNode in the tree.
			cerr << TREE << tree_count << UPDATE <<
			(const char*) data << ']' << '\n';
		}
		// if there is a left child of the current TNode
		if (left != NULL) {
			// setting the leftHeight to the left
			// TNode's height.
			leftHeight = left->height;
		}
		// if there is a right child of the current TNode.
		if (right != NULL) {
			// setting the rightHeight to the right
			// TNode's height. 
			rightHeight = right->height;
		}
		// if the leftHeight is greater or equal to the
		// rightHeight 
		if (leftHeight >= rightHeight) {
			// then that current TNode's height
			// equals to the leftHeight plus one.
			height = leftHeight + 1;
		}
		// if the rightHeight is greater than the
		// leftHeight 
		if (rightHeight > leftHeight) {
			// then the current TNode's height will
			// equal to the rightHeight plus one. 
			height = rightHeight + 1;
		}
		// the current TNode's balance will be leftHeight
		// minus rightHeight. 
		balance = leftHeight - rightHeight;
		// if the balance exceed the THRESHOD which is -2/2
		if (balance > THRESHOLD || balance < -THRESHOLD) {
			// call the Remove method with the temporary TNode.
		TNode<Whatever> TEMP(data, *this);
			Remove(TEMP, PointerInParent, true);
			// Then reinsert it correctly to the tree. 
			PointerInParent->Insert(TEMP.data, PointerInParent);
		}
        }

        ostream & Write_AllTNodes (ostream & stream) const {
                if (left)
                        left->Write_AllTNodes (stream);
                stream << *this;
                if (right)
                        right->Write_AllTNodes (stream);

                return stream;
        }
};

/***************************************************************************
% Routine Name : Tree :: Set_Debug_On (public)
% File :         Tree.c
% 
% Description :  This function sets debug mode on
%
% Parameters descriptions :
% 
% name               description
% ------------------ -------------------------------------------------------
% None			Nothing
***************************************************************************/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_On () {
	// debug is on.
	debug = 1;
}

/***************************************************************************
% Routine Name : Tree :: Set_Debug_Off (public)
% File :         Tree.c
% 
% Description :  This function sets debug mode off
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% None			Nothing
***************************************************************************/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off () {
	// debug is off
	debug = 0;
}

/***************************************************************************
% Routine Name : TNode<Whatever> :: Insert (public)
% File :         Tree.c
% 
% Description :  Inserts an element into the binary tree. Returns true or
%		 false indicating success of insertion.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% const Whatever & element:	 Values of element are expected to be the 
%				 data stored in the TNode.
% TNode<Whatever> *& PointerInParent:
%				 A reference to the TNode pointer in the
%				 parent TNode used to get to the current 
%				 TNode.
***************************************************************************/
template <class Whatever>
unsigned long TNode<Whatever> :: Insert (const Whatever & element, 
                                         TNode<Whatever> *& PointerInParent) {
	long retVal = FALSE; // initializing a long value retVal to false.
        // if the user turns on debug
	if (Tree<Whatever>::debug == 1) {
		// print out the debug message about comparing the element 
		// that the user has typed into the terminal to the data 
		// that's each TNode
		cerr << TREE << tree_count << COMPARE << (const char*) element
		<< AND << (const char *) (data) << ']' << '\n';
	}
	// if the user types in the element that is similar to the data that 
	// is already in the TNode 
	if (element == data) {
		// then just override the data that is in the TNode to the
		// element that the user has typed in
		data = element;
		return true;
	}
	// if the element has a higher value than the data that is in the 
	// the TNode
	else if (element > data) {
		// if there is nothing to the right of that TNode
		if (right == NULL) {
			// if the user turns debug on
			if (Tree<Whatever>::debug == 1) {
				// print out the error message about inserting
				// the element that the user has typed in to 
				// terminal to the Tree.
				cerr << TREE << tree_count << INSERT << 
				(const char*) element << ']' << '\n';
			}
			// insert a new TNode with the element to the right
			// of the current TNode.
			right = new TNode<Whatever>(element, *this);
			// call SHAB method to correctly SHAB
			SetHeightAndBalance(PointerInParent);
			return true;
		}
		// if there is right of that TNode
		else 
			// recursively go right until there is none and 
			// whatever is returned is stored into retVal.
			retVal = right->Insert(element, right);
	}
	// if the element has a lower value than the data that is in the 
	// TNode
	else {
		// if there is nothing to the left of that TNode
		if (left == NULL) {
			// if the user turns debug on
			if (Tree<Whatever>::debug == 1) {
				// print out the error message about inserting
				// the element that the user has typed into 
				// the Tree. 
				cerr << TREE << tree_count << INSERT <<
				(const char*) element << ']' << '\n';
			}
			// insert a new TNode with the element to the left
			// of the current TNode.
			left = new TNode<Whatever>(element, *this);
			// call SHAB method to correctly SHAB
			SetHeightAndBalance(PointerInParent);
			return true;
		}
		// if there is left child of that TNode
		else 
			// recursively go left until there is none and
			// whatever is returned is stroed into retVal.
			retVal = left->Insert(element, left);
	}
	// call SHAB method to correctly SHAB
	SetHeightAndBalance(PointerInParent);
	return retVal;
}

template <class Whatever>
ostream & operator << (ostream & stream, const TNode<Whatever> & nnn) {
        stream << "at height:  :" << nnn.height << " with balance:  "
                << nnn.balance << "  ";
        return stream << nnn.data << "\n";
}

/***************************************************************************
% Routine Name : Tree :: Insert (public)
% File :         Tree.c
% 
% Description :  Inserts an element into the binary tree. Inserts at the root
%		 TNode if Tree is empty, otherwise delegates to TNode's 
%		 Insert. Returns true or false indicating success of 
%		 insertion.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% const Whatever & element:	 Values of element are expected to be the 
%				 data stored in the TNode.
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Insert (const Whatever & element) {
	// if there is no root at the beginning
	if (root == NULL) {
		// setting root to a new created TNode with the element
		// that the user has typed to the terminal. 
		root = new TNode<Whatever>(element, *this);
		// if the debug is on
		if (Tree<Whatever>::debug == 1) {
			// Prints out the debug message that states
			// that the name that the user has inputted 
			// has been inserted. 
			cerr << TREE << tree_count << INSERT 
			<< (const char*) (element) << ']' << '\n';
		}
		return true;
	}
	// if there is a root.
	else {
		// recursively call the Insert method with the root being
		// the parent. 
		root->Insert(element, root);
		return true;
	}
	return false;
}



/***************************************************************************
% Routine Name : Tree<Whatever> :: Lookup (public)
% File :         Tree.c
% 
% Description :  Searches for an element in the Tree. Delegates to TNode's 
%		 Lookup when implemented recursively. Returns true or false 
%		 indicating success of look up.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% const Whatever & element:	 Values of element are expected to be the 
%				 data stored in the TNode.
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {

        // creating a working TNode<Whatever> and setting to root.
	TNode<Whatever> *working = root;
	// while working is not empty
	while (working != NULL) {
		// if the user turns on debug
		if (Tree<Whatever>::debug == 1) {
			// print out the debug message about comparing the 
			// string that the user has inputted to the string 
			// of each TNode's
			cerr << TREE << tree_count << COMPARE << 
			(const char*) element << AND << 
			(const char *) (working->data) << ']' << '\n';
		}
		// if the element is equal to the data that is in the TNode
		if ((element) == (working->data)) {
			// element will be the data that is in the TNode
			element = working->data;
			return true;
		}
		// else if the element has a higher value than the data
		// that is in the current TNode.
		else if ((element) > (working->data)) {
			// working will be the right child of the current
			// TNode.
			working = working->right;
		}
		// if the element has a lower value than the data that is
		// in the current TNode.
		else 
			// the current TNode will be the left child of the
			// previous TNode
			working = working->left;
	}
	return false;
}


/***************************************************************************
% Routine Name : Tree<Whatever> :: Remove (public)
% File :         Tree.c
% 
% Description :  Removes an element from the Tree. Delegates to TNode's 
%		 Remove when Tree is not empty. Returns true or false 
%		 indicating success of removal.
%
% Parameters descriptions : 
%
% name               description
% ------------------ ------------------------------------------------------
% Whatever & element:		 Values of element are expected to be the 
%				 data stored in the TNode.
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {
	// initializing a long value called result to be false
	long result = false;
	// creating a TNode<whatever> called working that has element the
	// user has typed into the terminal in RTS
	TNode<Whatever> working(element, *this);
	// if there is a root in the tree
	if (root != NULL) {
		// result will be the output of whatever is returned
		// from Remove, which is recursively called. 
		result = root->Remove(working, root, false);
	}
	// element is the data that is in the TNode
	element = working.data;
	// returns false if root is empty or data if there is a root in the
	// tree.
	return result;
}
                                
template <class Whatever>
Tree<Whatever> :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree<Whatever> :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  
%
% Parameters descriptions : 
%
% name               description
% ------------------ ------------------------------------------------------
% None
***************************************************************************/
{
        // if the user turns on debug
	if (Tree<Whatever>::debug == 1) {
		// print out the debug message about deallocating the tree
		// created. 
		cerr << TREE << tree_count << DEALLOCATE;
	}
	// if there is a TNode in the tree
	if (root != NULL) {
		// recursively call the delete_AllTNodes method starting
		// from the root. 
		root->delete_AllTNodes();
	}
	// decrement the tree_count.
	tree_count--;
}

template <class Whatever>
ostream & Tree<Whatever> :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree<Whatever> :: Write (public)
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
        stream << "Tree " << tree_count << ":\n"
                << "occupancy is " << occupancy << " elements.\n";

        return (root) ? root->Write_AllTNodes (stream) : stream;
}
