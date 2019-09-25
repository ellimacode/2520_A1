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

  /* read in all the blocks from the file */
  fread(&ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp);

/* prints out contents of all blocks, one
   at a time */
/*for (i = 0; i < MAX_BLOCKS; i++)
{

} */


  return 0;
}

/* test ds_init function */
/*int ds_test_init(char *filename)
{
  int i;

  for (i = 0; i < MAX_BLOCKS; i++)
  {

    printf("Block #   start   length   alloced\n");
    printf("%d        %lu     %lu      %c\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);

  }

return 0;
} */
