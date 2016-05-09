/****************************************************************************
                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        February 27, 2015
                                                        cs12xbo
                                Assignment Eight

File Name:      Tree.h
Description:    Tree.h is a public file that public/others can see.
****************************************************************************/

#ifndef TREE_H
#define TREE_H

/* YOU CAN ADD CLASS HEADER AND FILE HEADER
 * DO NOT CHANGE ANYTHING ELSE:  This file is used in evaluation */

#include <iostream>
using namespace std;

// debug message
static const char ALLOCATE[] = " - Allocating]\n";
static const char TREE[] = "[Tree ";

template <class Whatever>
struct TNode;

/***************************************************************************
% Routine Name : class Tree (public)
% File :         Tree.h
% 
% Description :  A class that runs the Tree.c file and a class that has some
%		 methods/variables of Tree in Tree.c.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% None			Nothing
***************************************************************************/
template <class Whatever>
class Tree {
        friend struct TNode<Whatever>;
        long occupancy;
        TNode<Whatever> * root;
        unsigned long tree_count;
        static int debug;
public:
        
        Tree (void): occupancy (0), root (NULL) {
                
                static long counter;
                tree_count = ++counter;

                if (debug) {
                        cerr << TREE << tree_count << ALLOCATE;
                }
        }
        
        ~Tree (void);
        
        static void Set_Debug_On (void);
        static void Set_Debug_Off (void);
        
        unsigned long Insert (const Whatever &);
        unsigned long Lookup (Whatever &) const;
        unsigned long Remove (Whatever &);
        ostream & Write (ostream &) const;
};

#include "Tree.c"

#endif
