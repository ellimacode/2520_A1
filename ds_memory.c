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
  FILE *fp;
  char writeBytes;

  /* open a file and write block array */
  fp = fopen(filename, "wb+");
  fwrite(&ds_file.block, sizeof(struct ds_blocks_struct), 1, fp);


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

  writeBytes = fwrite(&ds_file.block, sizeof(struct ds_blocks_struct), 1, fp);

}


  return 0;
}
