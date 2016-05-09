/***************************************************************************
% Name: Ji Woon Chung
% Login: cs12xbo
% Date: March 9, 2015
% Class: CSE 12, Winter 2015
%
% Assignment Nine
% File Name: Driver.c
% Description: A file filled with methods needed to properly run Tree.c
% under UCSDStudent. Commands will appear to the terminal when the Driver
% is ran. Then depending on whatever letter, commands, that the user types
% into the terminal, the program will run certain methods in Tree.c.
***************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <getopt.h>
#include "Driver.h"
#include "SymTab.h"
#include <fstream> //for the fstream class definition

using namespace std;

/* DO NOT CHANGE:  This file is used in evaluation */

#ifdef NULL
#undef NULL
#define NULL 0
#endif

ostream & operator << (ostream & stream, const UCSDStudent & stu) {
        return stream << "name:  " << stu.name
                << " with studentnum:  " << stu.studentnum;
}

/*******************************************************************
% Routine Name : int main  (public)
% File :         Driver.c
% 
% Description :  The main method that runs the whole program/file for
%		 Tree.c. 
%
% Parameters descriptions :
% 
% name		Description
% -------------- ---------------------------------------------------
% int argc:		The argument count. It is the number of 
%			arguments passed into the program from the 
%			command line, including the name of the program.
% char * const * argv:	The character pointers that is the listing
%			of all the arguments.
*******************************************************************/
int main (int argc, char * const * argv) {
        char buffer[BUFSIZ];
        char command;
        long number;
        char option;
	istream *is = &cin; // initializing a pointer is, to be the reference
	// of cin. 
	ostream *os = &cout; // initializing a pointer os, to be the reference
	// of cout of this program.
        
        SymTab<UCSDStudent>::Set_Debug_Off ();

        while ((option = getopt (argc, argv, "x")) != EOF) {

        switch (option) {
                case 'x': SymTab<UCSDStudent>::Set_Debug_On ();
                        break;
                }       
        }
        
        SymTab<UCSDStudent> ST("Driver.datafile"); // creates a Driver.datafile
        ST.Write (cout << "Initial Symbol Table:\n" );
	
	// a while loop that runs when the user inputs something to the 
	// terminal
	while (cin) {
		// if there isn't anything inputted into the terminal
		// by the file
		if (!*is) {
			// if the file input is not equal to the keyboard 
			// input
			if (is != &cin) {
				// delete the is to clean up the file after
				// the terminal has done reading from the file
				delete is;
				// delete the os to clean up the file after
				// the terminal has done reading from the file
				delete os;
				// then is goes back to reading from the 
				// keyboard
				is = &cin;
				// os also goes back to being the regular 
				// output to the terminal
				os = &cout;
			}
			else {
				break;
			}
		}
                command = NULL;         // reset command each time in loop
		// the program outputs to the terminal if it is 
		// from the keyboard, otherwise it does not appear
                *os << "Please enter a command ((f)ile, (i)nsert, " 
                        << "(l)ookup, (r)emove, (w)rite):  ";
                // so that the program could read in the commands from the 
		// keyboard and file
		*is >> command;

                switch (command) {
		
		// a case for when the user types in the 'f' command to the 
		// terminal
		case 'f': {
			// first outputs this command to the terminal so that
			// the user could type in the file name
			*os << "Please enter file name for commands: ";
			// reads in whatever file the user has typed into the
			// terminal
			*is >> buffer;
			// if the file input is not similar to the keyboard
			// input
			if (is != &cin) {
				// delete the previous input system
				delete is;
				// delete the previous output system. 
				delete os;
			}
			// now is is a new ifstream that reads in from the 
			// file
			is = new ifstream(buffer);
			// os is now a new ofstream that does not output to 
			// terminal
			os = new ofstream("/dev/null");
			break;
		}

                case 'i': {
			// so that it could output to the terminal when it is
			// from the keyboard, otherwise it does not appear.
                        *os << "Please enter UCSD student name to insert:  ";
			// allows to read in from both the keyboard and file
                        *is >> buffer;  // formatted input
			// outputs in the terminal or not at all depending
			// if it is reading from keyboard or file
                        *os << "Please enter UCSD student number:  ";
			// reads in from the keyboard or file
                        *is >> number;

                        UCSDStudent stu (buffer, number);

                        // create student and place in symbol table
                        ST.Insert (stu);
                        break;
                }
                case 'l': { 
                        unsigned long found;    // whether found or not
			// outputs in the terminal or not at all depending
			// if the terminal is reading from the keyboard or
			// file
                        *os << "Please enter UCSD student name to lookup:  ";
                        // reads in from the file or keyboard
			*is >> buffer;  // formatted input
                        UCSDStudent stu (buffer, 0);
                        found = ST.Lookup (stu);
                        
                        if (found)
                                cout << "Student found!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                        }
                case 'r': { 
                        unsigned long removed;
			// outputs to the terminal or not at all depending
			// if the terminal is reading in the commands from the
			// file or keyboard.
                        *os << "Please enter UCSD student name to remove:  ";
                        // reads in from the keyboard or file
			*is >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        removed = ST.Remove(stu);

                        if (removed)
		                cout << "Student removed!!!\n" << stu << "\n";
                        else
				cout << "student " << buffer <<" not there!\n";
                        break;
                }
                case 'w':
	                ST.Write (cout << "The Symbol Table contains:\n");
                }
	}

	ST.Write (cout << "\nFinal Symbol Table:\n");

	// if the user presses Ctrl ^D and if GetOperation() method from Tree.c
	// does not return 0
	if (ST.GetOperation() != 0) {
		// outputs the statement telling the cost of operations which
		// is read in from the GetCost method in Tree.c
		cout << "\nCost of operations: ";
		cout << ST.GetCost();
		cout << " tree accesses";
		
		// outputs the statement telling the number of operations which
		// is read in from the GetOperations() from Tree.c
		cout << "\nNumber of operations: ";
		cout << ST.GetOperation();
		// outputs the statement telling the average cost, which
		// is the cost divided by number of operations
		cout << "\nAverage cost: ";
		cout << (((float)(ST.GetCost()))/(ST.GetOperation()));
		cout << " tree accesses/operation\n";
	}
	// if nothing is returned from the GetOpertion method from Tree.c
	else
		// outputs that there is no cost information avaiable.
		cout << "\nNo cost information available.\n";
}
