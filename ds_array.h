/* Full Name: Camille Cua
 * Student ID number: 1046663
 * Email: ccua@uoguelph.ca */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* this constant represents the maximum number of elements 
 * that can be included in the array */
#define MAX_ELEMENTS 256

/* global variable - holds the number of elements
 * currently in the array */
long elements;

/* function prototypes */
int ds_create_array();
int ds_init_array();
int ds_replace(int value, long index);
int ds_insert(int value, long index);
int ds_delete(long index);
int ds_swap(long index1, long index2);
long ds_find(int target);
int ds_read_elements(char *filename);
int ds_finish_array();
