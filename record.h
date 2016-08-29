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
// DATE: February 29, 2016
//
// FILE: record.h
//
// DESCRIPTION: This file contains the structure called record -
//		Record contains the information of an account
//		Account Number 
//		Name
//		Address
//		Year of Birth
//		Link to the next record.
//
//****************************************************************/
struct record
{
    int              accountno;
    char             name[25];
    char             address[80];
    int              yearofbirth;
    struct record*  next;

}; 
