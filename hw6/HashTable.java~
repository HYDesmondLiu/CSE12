/**
 * Name: Ji Woon Chung
 * Class: CSE 12, Winter 15
 * Date: February 10, 2015
 * login: cs12xbo
 *
 * Assignment Six
 * File Name: HashTable.java
 * Description: Creates an array of size five table, that will store names 
 * and numbers of whatever the user inputs into the terminal. Will also
 * be able to look up names or numbers that is already stored in the 
 * array table.  
 */ 

public class HashTable extends Base {

	private static int counter = 0;	// number of HashTables so far
        private static boolean debug;        // allocation of debug state

        // set in locate, last location checked in hash table 
        private int index = 0; 

        // set in insert/lookup, count of location in probe sequence
        private int count = 0;
        
        private int probeCount[];   // where we are in the probe sequence 
        private long occupancy;     // how many elements are in the Hash Table
        private int size;           // size of Hash Table
        private Base table[];       // the Hash Table itself ==> array of Base
        private int tableCount;     // which hash table it is

        // messages
        private static final String AND = " and ";
        private static final String DEBUG_ALLOCATE = " - Allocated]\n";
        private static final String DEBUG_LOCATE = " - Locate]\n";
        private static final String DEBUG_LOOKUP = " - Lookup]\n";
        private static final String BUMP = "[Bumping To Next Location...]\n";
        private static final String COMPARE = " - Comparing ";
        private static final String FOUND_SPOT = " - Found Empty Spot]\n";
        private static final String HASH = "[Hash Table ";
	private static final String HASH_VAL = "[Hash Value Is ";
        private static final String INSERT = " - Inserting ";
        private static final String PROCESSING = "[Processing ";
        private static final String TRYING = "[Trying Index ";

        
        /**
        * This method turns on the debug by setting it to be true.
        *
        */
        public static void debugOn () {
		debug = true;
        }

         /**
         * This method turns off the debug by setting it to false. 
         *
         */
        public static void debugOff () {
                debug = false; 
        }

        /**
         * This method allocates and initializes the memory
         * associated with a hash table.
         *
         * @param  sz   The number of elements for the table...MUST BE PRIME!!
         */
        public HashTable (int sz) {
                // initializing
		size = sz;
		tableCount = 0;
		occupancy = 0;
		// table will have an array size of sz and will already be 
		// initialized to 0 due to being in java code. 
		table = new Base[sz];
		// probeCount will also have that same size array and will
		// already be initialized to 0 due to being in java code
		probeCount = new int[size];
		// increments the counter every time the HashTable is created.
		counter++;
		tableCount = counter; 
        }

        /**
         * This method will insert the element in the hash table.
         * If the element cannot be inserted, false will be returned.
         * If the element can be inserted, the element is inserted
         * and true is returned.  Duplicate insertions will
         * cause the existing element to be deleted, and the duplicate
         * element to take its place.
         *
         * @param   element       The element to insert.
         * @param   initialCount  Where to start in probe seq (recursive calls)
         * @return  true or false indicating success or failure of insertion
         */
        public boolean insert (Base element, int initialCount) {
                // initialize
		count = initialCount;
		// creating temporary variable to be used later in the program
		Base tempElement;
		int tempInitialCount;
		// if the debug is on then the debug message will print out on
		// the terminal. 
		if (debug == true) {
			System.err.println(HASH + tableCount + 
			INSERT + element.getName() + "]");
		}
		// if the return value from locate is false 
		if (locate(element) == false) {
			// if there is nothing at the current index in the 
			// table array. 
			if (table[index] == null) {
				// will store that element, which the user has
				// inputted to the terminal, to that empty 
				// space with the number of times that element
				// has moved in the table.
				table[index] = element;
				probeCount[index] = count;
			}
			// if there is an element in that space.
			else {	
				// if the debug message is on then the bump 
				// message will show up in the terminal. 
				if (debug == true) {
					System.out.print(BUMP);
				}
				// saving the element that's in that certain 
				// index in the table array.
				tempElement = table[index];
				// also saving the probeCount of that element
				tempInitialCount = probeCount[index];
				// place a new element that was just inputted
				// by the user into that space
				table[index] = element;
				// also placing a new probeCount that's 
				// with the element.
				probeCount[index] = count;
				// passing the saved element and probeCount
				// to insert so it can properly placed in
				// the table array. 
				insert(tempElement, tempInitialCount + 1);
			}
		}
		// if the locate returns true.
		else {
			// overwrite the current index of the array table with
			// a new element and count.
			table[index] = element;
			probeCount[index] = count;
		}
		// occupancy increases.
		this.occupancy++;
		return true;
        }


        /**
         * This method will locate the location in the
         * table for the insert or lookup.
         *
         * @param   element  The element needing a location.
         * @return  true if tem found, or false if not found
         */
        private boolean locate (Base element) {
                // initializing
		int attribute;
		int location;
		int increment;
		// initiaiizing attribute to the sum of ASCII value returned
		// from hashCode)_
		attribute = element.hashCode();
		// moding the sum of ASCII values by the size of the array.
		location = attribute % size;  
		// to properly increment to the next index in the array.
		increment = (attribute % (size - 1)) + 1;
		// so it knows which index to properly go to first.
		index = (location + (this.count - 1)* increment) % size;
		// if the debug is on.
		if (debug == true) {
			// print out the debug messages.
			System.err.print(HASH + tableCount + DEBUG_LOCATE);
			System.err.println(PROCESSING + element.getName() 
			+ ']');
			System.err.println(HASH_VAL + attribute + "]");
		}
		// while loop that keeps occuring until the size of the array
		// is not full. 
		while (occupancy != size) {
			// if the debug is on
			if (debug == true) {
				// prints out the debug message
				System.err.println(TRYING + index + "]");
			}
			// if the index at a certain table array is empty.
			if (table[index] == null) {
				// if debug message is on.
				if (debug == true) {
					// print out the debug message about
					// finding an empty space.
					System.err.print(HASH + tableCount 
					+ FOUND_SPOT);
				}
				return false;
			}
			// if the debug message is on
			if (debug == true) {
				// print out the debug message about comparing
				// elements
				System.err.println(HASH + tableCount + COMPARE
				+ element.getName() + AND 
				+ table[index].getName() + ']');
			}
			// if the element that's in the index of the table 
			// array is exactly the same as the element that the
			// user has inputted. 
			if (table[index].equals (element)) {
				return true;
			}
			// if there is an element in the index of the table 
			// array
			if (table[index] != null) {
				// if the element in the array has a less 
				// movement count than the current count
				if (probeCount[index] < count) {
					// return false;
					return false;
				}
			}
			count++;
			// a new index for the element to go to.
			index = (index + increment) % size;
		}
		return true;
        }

        /**
         * This method will lookup the element in the hash table.  If
         * found a pointer to the element is returned.  If the element
         * is not found, NULL will be returned to the user.
         *
         * @param   element  The element to look up.
         * @return  A pointer to the element if found, else NULL
         */
        public Base lookup (Base element) {
                // initializing count to 1.
		count = 1;
		// if the debug message is on
		if (debug == true) {
			// print out the debug message about looking
			System.err.print(HASH + tableCount + DEBUG_LOOKUP);
		}
		// if the locate returns false
		if (locate(element) == false) {
			// do not do anything
			return null;
		}
		// however, if the locate returns true.
		else
			// return the name and student number in the stored
			// index of the table array. 
			return table[index];
	}

        /**
         * Creates a string representation of the hash table. The method 
         * traverses the entire table, adding elements one by one ordered
         * according to their index in the table. 
         *
         * @return  String representation of hash table
         */
        public String toString () {
                String string = "Hash Table " + tableCount + ":\n";
                string += "size is " + size + " elements, "; 
                string += "occupancy is " + occupancy + " elements.\n";

                /* go through all table elements */
                for (int index = 0; index < size; index++) {

                        if (table[index] != null) {
                                string += "at index " + index + ": ";
                                string += "" + table[index];
                                string += " with probeCount: "; 
                                string += probeCount[index] + "\n";
                        }
                }

                return string;
        }
}
