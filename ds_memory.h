/* defining the constant, copying the three structures and
   then copyin the prototypes for the functions */
/* add semi-colon for each function prototype */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* global variables*/
/* global variable - holds the file pointer and blocks array */
struct ds_file_struct ds_file;
/* global variable - holds the read and write counts */
struct ds_counts_struct ds_counts;


/* indicates the maximum number of blocks of memory */
#define MAX_BLOCKS 4096

/* this data structure counts the number of read and
   write operations performed */
struct ds_counts_struct {
   int reads;
   int writes;

};

/* this structure keeps track of one block in binary
   file */
struct ds_blocks_struct {
   long start;
   long length;
   char alloced;

};

/* this structure holds a file pointer to a file, open
   in binary, read/write mode and an array of blocks */
struct ds_file_struct {
   FILE *fp;
   struct ds_blocks_struct block[MAX_BLOCKS];

};

/* function prototypes */
int ds_create(char *filename, long size);
int ds_init(char *filename);
long ds_malloc(long amount);
void ds_free(long start);
void *ds_read(void *ptr, long start, long bytes);
long ds_write(long write, void *ptr, long bytes);
int ds_finish();
