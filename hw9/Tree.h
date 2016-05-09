/****************************************************************************
                                                        Ji Woon Chung
                                                        CSE 12, Winter 15
                                                        March 9, 2015
                                                        cs12xbo
                                Assignment Nine

File Name:      Tree.h
Description:    Tree.h is a public file that public/others can see.
****************************************************************************/

#ifndef TREE_H
#define TREE_H

/* YOU CAN ADD CLASS HEADER AND FILE HEADER
 * DO NOT CHANGE ANYTHING ELSE:  This file is used in evaluation */

#include <fstream>
#include <iostream>
using namespace std;

typedef long offset;

template <class Whatever>
struct TNode;

/***************************************************************************
% Routine Name : class Tree (public)
% File :         Tree.h
% 
% Description : What the public can see about Tree constructor.
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
        static long cost;
        static int debug_on;
        fstream * fio;
        long occupancy;
        static long operation;
        offset root;
        unsigned long tree_count;
        void ResetRoot (void);

public:
        Tree (const char *);
        ~Tree (void);

        static long GetCost ();
        static long GetOperation ();
        static void IncrementCost ();
        static void IncrementOperation ();
        static void Set_Debug_On (void);
        static void Set_Debug_Off (void);

        unsigned long Insert (Whatever &);
        unsigned long Lookup (Whatever &) const;
        unsigned long Remove (Whatever &);
        ostream & Write (ostream &) const;
};

#include "Tree.c"

#endif
