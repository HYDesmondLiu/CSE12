/**
 * Name: Ji Woon Chung
 * Class: CSE 12, Winter 15
 * Date: February 10, 2015
 * login: cs12xbo
 *
 * Assignment Six
 * File Name: Driver.java
 * Description: A file filled with methods needed to test, run, and
 * check if HashTable.java works properly. Converts the strings
 * that the user has inputted and turns it into an ASCII sum. Has constructors
 * that allows the user to input multiple names and student's number. 
 */ 

import java.io.EOFException; 
class UCSDStudent extends Base {
        private String name;
        private long Studentnum;

        public String toString () {

                return "name: " + name + " Studentnum: " + Studentnum;
        }

        /**
         * This method will store the name and the student number that the
	 * user has inputted. 
	 *
         * @param   name	A string that the user has inputted into
	 *			the terminal. 
         * @param   number	A long value that the user has inputted into
	 *			the terminal.
         * @return		Nothing. 
        */
	public UCSDStudent (String name, long number) {
		// creates a new string name that will be stored into
		// the global name.
		this.name = new String (name);
		// a number that the user has inputted  will be stored 
		// to the Studentnum. 
		Studentnum = number; 
	}

        /**
         * This method will also be the constructor to store the name and 
	 * student number that the user has inputted into the terminal. 
	 *
         * @param   ucsdstudent	A constructor for UCSDStudent.  
         * @return		Nothing. 
        */
	public UCSDStudent (UCSDStudent ucsdstudent) {
		// creates a new string for ucsdstudent, which will be stored
		// into the global name. 
		name = new String (ucsdstudent.name);
		// the specific student created will have that specific number
		// which the user has inputted into the terminal. 
		Studentnum = ucsdstudent.Studentnum;
	}
	
	/**
         * This method will get/recieve the name which was stored in the 
	 * heap/Hashtable. 
	 *
         * @return		Will return the name that was stored in the 
	 *			table index. 
        */
	public String getName() {
		return name;
	}

        /**
         * This method will check to see if the name or the sum of ASCII of 
	 * the name that the user has inputted is a match or not to the 
	 * one already stored. 
	 *
         * @param   other	A different object that is being compared to.
         * @return		True if the two objects are similar or false
	 *			if the two objects are not. 
        */
	public boolean equals (Object other) {
		if (this == other)
			return true;
		// overwriting the equals operator 
		if (!(other instanceof UCSDStudent))
			return false; 
		UCSDStudent otherVar = (UCSDStudent)other;
		return name.equals (otherVar.getName ());
	}

        /**
         * This method will turn the name that the user has inputted into 
	 * the terminal to an ASCII sum.
	 *
         * @return		Returns the value that was translated to 
	 *			ASCII sum from the user's inputted name. 
        */
	public int hashCode() {
		// initialize
		int returnval = 0;
		int index = 0;
		// sums up the ASCII value of each characters
		while (index != name.length()) {
			returnval += name.charAt (index);
			index++;
		}
		return returnval;
	}

        /**
         * This method will return the value of a specific student's number 
	 * that the user has inputted at the beginning. 
	 *
         * @param   number	Long value that is being passed to 
         * @return		Returns the value of a specific student's 
	 *			number.
        */
	public UCSDStudent assign (long number) {
		UCSDStudent returnval; //returns value
	
		// give student number its number
		Studentnum = number; 
		returnval = new UCSDStudent (this);
		return returnval; 
	}
}

public class Driver {

        public static void main (String [] args) {

                /* initialize debug states */
                HashTable.debugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                HashTable.debugOn();
                }

                /* The real start of the code */
                SymTab symtab = new SymTab (5);
                String buffer = null;
                char command;
                long number = 0;

                System.out.print ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = 0;    // reset command each time in loop
                        System.out.print ("Please enter a command:  "
                                + "((i)nsert, (l)ookup, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {
                        case 'i':
                                System.out.print (
                                "Please enter UCSD Student name to insert:  ");
                                buffer = MyLib.getline ();// formatted input

                                System.out.print (
                                        "Please enter UCSD Student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return
                                // create Student and place in symbol table
                                if(!symtab.insert (
                                        new UCSDStudent (buffer, number), 1)){

                                        System.out.println("Couldn't insert " + 
                                                           "student!!!"); 
                                }
                                break;

                        case 'l': {
                                Base found;     // whether found or not

                                System.out.print (
                                "Please enter UCSD Student name to lookup:  ");

                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println ("Student found!!!");
                                        System.out.println (found);
                                }
                                else
                                        System.out.println ("Student " + buffer
                                                + " not there!");
                                }
                                break;

                        case 'w':
                                System.out.print (
                                    "The Symbol Table contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }

                System.out.print ("\nFinal Symbol Table:\n" + symtab);
        }
}
