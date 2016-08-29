/*****************************************************************
//
// NAME: Mary Santabarbara
//
// HOMEWORK: Project 1
//
// CLASS: ICS 212
//
// INSTRUCTOR: Ravi Narayan
//
// DATE: March 7, 2016
//
// FILE: prototypes.h
//
// DESCRIPTION: This file contains the prototypes for project 1.
//
//****************************************************************/

#include <stdio.h>
#include "record.h"

int addRecord (struct record **, int, char [ ],char [ ],int);
int printRecord (struct record *, int);
int modifyRecord (struct record *, int, char [ ]);
void printAllRecords(struct record *);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
void writefile(struct record *, char []);
