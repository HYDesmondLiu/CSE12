/****************************************************************************

                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        February 10, 2015
                                                        cs12xbo
                                Assignment Six

File Name:      Hash.c
Description:    This program will allow the user to insert and save 
		information using a Symbol Table (Hashing algorithm). The 
		user will also be allowed to call and recieve that saved 
		information. 
****************************************************************************/

#include <cstdlib>
#include <string>
#include "Hash.h"

using namespace std;

static const char AND[] = " and ";
static const char DEBUG_ALLOCATE[] = " - Allocated]\n";
static const char DEBUG_DEALLOCATE[] = " has been deallocated]\n";
static const char DEBUG_LOCATE[] = " - Locate]\n";
static const char DEBUG_LOOKUP[] = " - Lookup]\n";
static const char BUMP[] = "[Bumping To Next Location...]\n";
static const char COMPARE[] = " - Comparing ";
static const char FOUND_SPOT[] = " - Found Empty Spot]\n";
static const char HASH[] = "[Hash Table ";
static const char HASH_VAL[] = "[Hash value is: ";
static const char INSERT[] = " - Inserting ";
static const char PROCESSING[] = "[Processing ";
static const char TRYING[] = "[Trying index ";

bool HashTable :: debug = 0;
int HashTable :: counter = 0;

void HashTable :: Set_Debug (int option)

/***************************************************************************
% Routine Name : HashTable :: Set_Debug (public)
% File :         hash.c
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
{
	/* if the user turns on debug */
	if (option == 1) {
		/* debug is on */
		debug = true;
	}
	/* if the user turns off debug */
	if (option == 0) {
		/* debug is off */
		debug = false;
	}
} /* end debug */


HashTable :: HashTable (int sz) : size (sz),
	table_count(++counter), occupancy (0), table (new Base *[sz]), 
	probeCount (new int[sz])
/***************************************************************************
% Routine Name : HashTable :: HashTable (public)
% File :         hash.c
% 
% Description :  This function allocates an initializes the memory
%                associated with a hash table.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% size               The number of elements for the table...MUST BE PRIME!!!
% table_count	     To keep track of number of tables that have been created.
% occupancy	     To keep track elements that have been created in the
%                    table.
% table		     To construct table array.
% probeCount	     To construct probeCount array. 
***************************************************************************/

{
	/* initialize all table elements and setting it to NULL */
	for (int i = 0; i < size; i++) {
		table[i] = NULL;
		probeCount[i] = NULL;
	}

}	/* end: HashTable */


HashTable :: ~HashTable (void)
/***************************************************************************
% Routine Name : HashTable :: ~HashTable  (public)
% File :         hash.c
% 
% Description :  deallocates memory associated with the Hash Table.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/
	
{	
	/* if the user turns on debug */
	if (debug == true) {
		/* print out the debug message for deallocation */
		cerr << HASH << table_count << DEBUG_DEALLOCATE;
	}
	/* to delete individual elements */
	for (int i = 0; i < size; i++) {
		/* if there is an element in the table array */
		if  (table[i] != NULL) {
			/* delete the control element in the array */
			delete (table[i]);
			/* and set it to NULL */
			table[i] = NULL;
		}
		/* delete the element in the table array */
		delete table[i];
	}
	/* delete table */
	delete[] table;
	/* delete the probeCount also */
	delete[] probeCount;
	/* set the table to NULL */
	table = NULL;
	/* set the probeCount to NULL */
	probeCount = NULL;
}	/* end: ~HashTable */


bool HashTable :: Insert (Base * element, int initialCount)
/***************************************************************************
% Routine Name : HashTable :: Insert (public)
% File :         hash.c
% 
% Description : This function will insert the element in the hash table.
%		If the element cannot be inserted, false will be returned.
%		If the element can be inserted, the element is inserted
%		and true is returned.  Duplicate insertions will
%		cause the existing element to be deleted, and the duplicate
%		element to take its place.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert.
% recursiveCall      Whether or not we are entering from recursion
% <return>           true or false indicating success or failure of insertion
***************************************************************************/

{	
	/* initializing */
	count = initialCount;
	Base * tempElement;
	int tempInitialCount;
	/* if the user turns on debug */
	if (debug == true) {
		/* print the debug message about inserting the element */
		cerr << HASH << table_count << INSERT 
		<< (char*) (*element) << ']' << '\n';
	}
	/* if Locate returns false */
	if (Locate(element) == false) {
		/* and if the inside of the table array is empty */
		if (table[index] == NULL) {
			/* automatically insert the element and probeCount in
			 * to the empty table array */
			table[index] = element;
			probeCount[index] = count;
		}
		/* if the inside of the table array is not empty. */
		else {	
			/* if the user turns on debug */
			if (debug == true) {
				/* print the debug message about bumping */
				cerr << BUMP;
			}
			/* first save the element that is in the table array */
			tempElement = table[index];
			/* and save the probeCount that is in the table array */
			tempInitialCount = probeCount[index];
			/* insert the new element into that spot */
			table[index] = element;
			/* with the new probeCount of that element */
			probeCount[index] = count; 
			/* then pass the saved element and probeCount to the 
			 * Insert method so that it can properly be placed
			 * in the table array */
			Insert(tempElement, tempInitialCount + 1);
		}
	}
	/* if Locate returns true */
	else {
		/* just insert the element and probeCount of that element into
		 * the table array, overwriting whatever is in it. */
		table[index] = element;
		probeCount[index] = count;
	}
	/* increase the occupancy of the hashTable */
	this->occupancy++;
	return true;	
} /* end Insert */


bool HashTable :: Locate (Base * element)
/**********************************************************************
% Routine Name : HashTable :: Locate (private)
% File :         HashTable.c
% 
% Description : This function will locate the location in the
%               table for the insert or lookup.
%
% Parameters descriptions :
%  
% name               description
% ------------------ -------------------------------------------------
% element            The element needing a location.
% <return>           true if tem found, or false if not found
**********************************************************************/

{
	/* initializing */
	int attribute;
	int location;
	int increment;
	/* setting the sum of the ASCII to attribute */
	attribute = *element;
	/* then setting the ASCII sum mode by size to location */
	location = attribute % size;  
	/* so that the element properly increments */
	increment = (attribute % (size - 1)) + 1;
	/* so that it starts off at a proper index */
	index = (location + (this->count - 1)* increment) % size;
	/* if the user turns on debug */
	if (debug == true) {
		/* print out the locate, processing, and the sum of the 
		 * ASCII debug message */
		cerr << HASH << table_count << DEBUG_LOCATE;
		cerr << PROCESSING << (char*) (*element) << ']' << '\n';
		cerr << HASH_VAL << attribute << ']' << '\n';
	}
	/* while the hashtable is not full */ 
	while (occupancy != size) {
		/* if the user turns on debug */ 
		if (debug == true) {
			/* print out the debug message about trying an index */
			cerr << TRYING << index << ']' << '\n';
		}
		/* if the current spot in the table array is empty */
		if (table[index] == NULL) {
			/* if the user turns on debug */
			if (debug == true) {
				/* print out the debug message about finding 
				 * an empty spot */
				cerr << HASH << table_count << FOUND_SPOT;
			}
			return false;
		}
		/* if the user turns on debug */
		if (debug == true) {
			/* print out the debug message about comparing the 
			 * element stored in the table array to the element
			 * that the user just has inputted */
			cerr << HASH << table_count << COMPARE 
			<< (char*) (*element) << AND 
			<< (char*) (*table[index]) << ']' << '\n';
		}
		/* if the element that is in the table array is exactly the 
		 * same as the element that the user has just inputted */ 
		if ((*table[index]) == (*element)) {
			return true;
		}
		/* if the current spot in the table array is not empty */
		if (table[index] != NULL) {
			/* if the probeCount of what is in the current
			 * spot of the table array is smaller than the 
			 * count */ 
			if (probeCount[index] < count) {
				return false;
			}
		}
		count++;
		/* to find the next index in the array if it already has an
		 * element in it. */
		index = (index + increment) % size;
	}
	return true;
}

Base * HashTable :: Lookup (Base * element)
/***************************************************************************
% Routine Name : HashTable :: Lookup (public)
% File :         hash.c
% 
% Description : This function will lookup the element in the hash table.  If
%               found a pointer to the element is returned.  If the element
%               is not found, NULL will be returned to the user.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert or to lookup.
% <return>           A pointer to the element if found, else NULL
***************************************************************************/

{
	/* starting count off with 1 */
	count = 1;
	/* if the user turns on debug */
	if (debug == true) {
		/* print out the debug message about searching */
		cerr << HASH << table_count << DEBUG_LOOKUP;
	}
	/* if locate returns false */
	if (Locate(element) == false) {
		/* do not do anything */
		return NULL;
	}
	/* if the locate returns true */ 
	else
		/* return every information in that current spot of the table
		 * array */ 
		return table[index];
}


ostream & HashTable :: Write (ostream & stream)
/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         hash.c
% 
% Description : This funtion will output the contents of the hash table
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
	stream << "Hash Table " << table_count << ":\n"
	       << "size is " << size << " elements, "
	       << "occupancy is " << occupancy << " elements.\n";

	/* go through all table elements */
	for (int index = 0; index < size; index++)
		if (table[index])
			table[index]->Write(stream << "at index "
			<< index << ": ") << " with probeCount: "
			<< probeCount[index] << "\n";
	return stream;
}	/* end: Write */
