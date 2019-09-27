#include "ds_memory.h"

/* global variable - holds the file pointer and blocks array */
struct ds_file_struct ds_file;
/* global variable - holds the read and write counts */
struct ds_counts_struct ds_counts;

/* must do two things:
   1) write the header
   2) write the bytes */
int ds_create(char *filename, long size)
{
  int i;
  int j;
  char writeBytes;

  /* open file to write into binary */
  ds_file.fp = fopen(filename, "wb+");

  if (ds_file.fp == NULL)
  {
    printf("The file doesn't exist!\n");
  }

  /* open a file and write block array */
  fwrite(&ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp);

/* accessing the block attribute of global variable
   in a for loop */
for (i = 0; i < MAX_BLOCKS; i++)
{

  ds_file.block[i].start = 0;
  ds_file.block[i].length = 0;
  ds_file.block[i].alloced = 0;

}

/* write "size" bytes using a loop, write
   bytes one at a time */
for (j = 0; j < MAX_BLOCKS; j++)
{

  fwrite(&writeBytes, sizeof(writeBytes), 1, ds_file.fp);

}

 /* close the file */
 fclose(ds_file.fp);

  return 0;
}

/* print out the contents of all the
   blocks and the counts variables */
int ds_init(char *filename)
{
  /* set reads and writes count to 0 */
  ds_counts.reads = 0;
  ds_counts.writes = 0;

  /* open the file for both reading and
     writing at start of beginning of the file */
  ds_file.fp = fopen(filename, "rb+");

  if (ds_file.fp == NULL)
  {
    printf("The file doesn't exist\n");
  }

  /* read in all the blocks from the file */
  fwrite(&ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp);

  return 0;
}

/* search the block array, checking the appropriate
   amount of memory has been allocated */
long ds_malloc(long amount)
{
  int i, j;


  for (i = 0; i < MAX_BLOCKS; i++)
  {

    /* checks block length is greater than or equal to amount, and alloced is 0*/
    if ((ds_file.block[i].length >= amount) && (ds_file.block[i].alloced == 0))
    {

      for (j = i; j < MAX_BLOCKS; j++)
      {

        /* checks second block length is equal to 0 */
        if ((ds_file.block[j].length == 0) && (ds_file.block[j].alloced == 0))
        {

          /* sets the start value of second block to original block's
             start value plus amount */
          ds_file.block[j].start = ds_file.block[i].start + amount;

          /* sets the length of second block to original block's length
             minus amount */
          ds_file.block[j].length = ds_file.block[i].length - amount;

          /* set second block's alloced to 0 */
          ds_file.block[j].alloced = 0;
          break;
        }


      }

      ds_file.block[i].length = amount;
      ds_file.block[i].alloced = 1;

      return ds_file.block[i].start;
    }

  }

return -1;
}

/* search through the block array, until it finds the block's
   start value matches start */
void ds_free(long start)
{

  int i;

  for (i = 0; i < MAX_BLOCKS; i++)
  {

    if (ds_file.block[i].start == start)
    {
      /* set the value allocated value to 0 */
      ds_file.block[i].alloced = 0;
    }

    /* if no block is found, should return without
       doing anything */
    else if (ds_file.block[i].start != start)
    {
      return;
    }

  }

}

/* this function should write block array into header at beginning of the file
   and close the file */
int ds_finish()
{

  /* write block array */
  fwrite(&ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp);

  /* close the file */
  fclose(ds_file.fp);

  /* print out the values of counts data structure */
  printf("reads: %d\n", ds_counts.reads);
  printf("writes: %d\n", ds_counts.writes);

return 1;
}

/* this function should write the block array into the header
   at the beginning of the file and close the file*/


/* test ds_init function */
/*int ds_test_init(char *filename)
{
  int i;

  printf("Block #   start   length   alloced\n");

  for (i = 0; i < MAX_BLOCKS; i++)
  {

    printf("%d        %lu     %lu      %c\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);

  }

  printf("reads = %d\n",ds_counts.reads);
  printf("writes = %d\n", ds_counts.writes);

return 0;
}*/
