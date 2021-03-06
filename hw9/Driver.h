/***************************************************************************
% Name: Ji Woon Chung
% Login: cs12xbo
% Date: March 9, 2015
% Class: CSE 12, Winter 2015
%
% Assignment Nine
% File Name: Driver.h 
% Description: A file filled with methods needed to test, run, and
% check if Tree.c works properly under UCSDStudent. Has constructors
% that creates and stores multiple names and student number for UCSDStudent
% every time the user inputs a new name and number. Also, there is a 
% constructor that overwrites the operators ==, >, and char *. 
% This file has methods that stores name and numbers, that the user types
% into terminal, into disk too. 
***************************************************************************/

#ifndef DRIVER_H
#define DRIVER_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

/*******************************************************************
% Routine Name : class UCSDStudent  (public)
% File :         Driver.h
% 
% Description :  A class that runs the Tree.c file under UCSDStudent
%		 instead of Calc. 
%
% Parameters descriptions :
% 
% name		Description
% -------------- ---------------------------------------------------
*******************************************************************/
class UCSDStudent {
	// a friend that is allowed to use the ostream and the operator
        friend ostream & operator << (ostream &, const UCSDStudent &);
        char name[20]; // an empty array of 20 characters for the name
        long studentnum; // a long that will be initialized to the number
	// that the user inputs into the terminal

public:
	/*******************************************************************
	% Routine Name : UCSDStudent (public)
	% File :         Driver.h
	% 
	% Description :  A constructor for the name and number that the user
	%		 inputs into the terminal for UCSDStudent and number.
	%		 Could also store the inputs into the memory file. 
	%
	% Parameters descriptions :
	% 
	% name		Description
	% -------------- ---------------------------------------------------
	% char * nm:			A character pointer to the name that
	%				the user inputs	for UCSDStudent name.
	% long num = 0:			Setting a long value to 0, which 
	%				later will be initialized to a number
	%				that the user inputs to the terminal. 
	*******************************************************************/
	UCSDStudent (char * nm, long num = 0) : studentnum (num) {
		// creates an empty storage of 0 bits in the file with the 
		// spaces of what the user has typed. 
		memset (name, '\0', sizeof (name));
		// making a string copy of the name that the user
		// has inputted into the terminal.
                strcpy (name, nm);
        }

	/*******************************************************************
	% Routine Name : UCSDStudent (public)
	% File :         Driver.h
	% 
	% Description :  A basic constructor that takes in nothing and setting
	%		 name and number to null/0.
	%
	% Parameters descriptions :
	% 
	% name		Description
	% -------------- ---------------------------------------------------
	% void				Nothing. 
	*******************************************************************/
	UCSDStudent (void) : studentnum (0) {
		// creates an empty storage of 0 bits in the file with the 
		// spaces of what the user has typed.
		memset (name, '\0', sizeof (name));
		// making a string copy of name that starts with nothing. 
		strcpy(name, "");
        }

	/*******************************************************************
	% Routine Name : UCSDStudent (public)
	% File :         Driver.h
	% 
	% Description :  A copy constructor of whatever the user has inputted
	%		 into the terminal.
	%
	% Parameters descriptions :
	% 
	% name		Description
	% -------------- ---------------------------------------------------
	% UCSDStudent & ucsdstudent:	A copy constructor of the name that 
	%				the user has already inputted into
	%				the terminal and setting to 
	%				ucsdstudent
	*******************************************************************/
	UCSDStudent (const UCSDStudent & ucsdstudent) {
		// creating an empty storage of 0 bits in the file with the
		// spaces of what the user has typed.
		memset (name, '\0', sizeof (name));
		// copying the name that the user has inputted intto the 
		// terminal and setting it to the name in ucsdstudent.
		strcpy (name, ucsdstudent.name);
		// initializing the number of that student into studentnum.
		studentnum = ucsdstudent.studentnum;
		
	}

	/*******************************************************************
	% Routine Name : operator const char * (public)
	% File :         Driver.h
	% 
	% Description :  Returns the name that the user has inputted.
	%
	% Parameters descriptions :
	% 
	% name		Description
	% -------------- ---------------------------------------------------
	% void				A character that is nothing
	*******************************************************************/
	operator const char * (void) const {
		return name;
	}

	/*******************************************************************
	% Routine Name : long operator == (public)
	% File :         Driver.h
	% 
	% Description :  An operator override of the equals method to see if 
	%	       	 the name is similar that of the the names that is 
	%		 stored.
	%
	% Parameters descriptions :
	% 
	% name		Description
	% -------------- ---------------------------------------------------
	% const UCSDStudent & bbb:	Another element that it will be 
	%				compared to
	*******************************************************************/
	long operator == (const UCSDStudent & bbb) const {
		// returns true if the name that the user has inputted 
		// is similar to the one that is stored and not if it
		// is not. 
		return ! strcmp (name, bbb.name);
	}

	/*******************************************************************
	% Routine Name : long operator > (public)
	% File :         Driver.h
	% 
	% Description :  An operator constructor/override of the greater than 
	%		 symbol to see if the name that the user has inputted 
	%		 is greater alphabetically than the name that is 
	%		 stored in the tree.
	%
	% Parameters descriptions :
	% 
	% name		Description
	% -------------- ---------------------------------------------------
	% const UCSDStudent & bbb:	Another element that the terminal will
	%				compared the user's input with.
	*******************************************************************/
	long operator > (const UCSDStudent & bbb) const {
		// returns true if the user's input has a greater value than 
		// what is currently being compared to. False if it is not. 
		return (strcmp (name, bbb.name) > 0) ? 1 :0;
	}
};

#endif
