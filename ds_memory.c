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
    return -1;
  }

  /* open a file and write block array */
  fwrite(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp);

/* accessing the block attribute of global variable
   in a for loop */
for (i = 0; i < MAX_BLOCKS; i++)
{
  /* check first block */
  if (i == 0)
  {
    ds_file.block[i].start = 0;

    ds_file.block[i].length = size;

    ds_file.block[i].alloced = 0;
  }

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
    return -1;
  }
  
  /* move to beginning of the file */
  fseek(ds_file.fp, 0, SEEK_SET);

  /* read in all the blocks from the file */
  fread(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp);

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

      for (j = 0; j < MAX_BLOCKS; j++)
      {
        /* checks second block length is equal to 0 */
        if (ds_file.block[j].length == 0)
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

/* this function should read bytes bytes from the location given by start,
   offset the length of header in binary file */
void *ds_read(void *ptr, long start, long bytes)
{
	/* size of block array */
	long offset;
	
	/* offset(size of the block array) the length of header in binary file */
	offset = (sizeof(struct ds_blocks_struct) * MAX_BLOCKS);
	
	/* moves file to specific location */
	fseek(ds_file.fp, offset + start, SEEK_SET);
	
	/*read 'bytes' bytes from the location given by start */
	fread(ptr, sizeof(struct ds_blocks_struct), bytes, ds_file.fp);
	
		
	/* increment the value of reads in counts
	 * by 1 */
	ds_counts.reads +=1;
	
	/* if successful, return address ptr */
	if (fread(ptr, sizeof(struct ds_blocks_struct), bytes, ds_file.fp) == 1)
	{
		return ptr;
	}
	
	/* return NULL if unsuccessful */
	else
	{
		return NULL;
	}
	
}

/* this function should move file pointer to start location offset
   by the length of header in binary file */
long ds_write(long start, void *ptr, long bytes)
{	
	/* size of block array */
	long offset;
	
	/* offset(size of the block array) the length of header in binary file */
	offset = (sizeof(struct ds_blocks_struct) * MAX_BLOCKS);
	
	/* move file pointer to start location offset by length of
	 * header in binary file */
	fseek(ds_file.fp, offset + start, SEEK_SET);
	
	/* write 'bytes' bytes to file from address ptr */
	fwrite(ptr, sizeof(struct ds_blocks_struct), bytes, ds_file.fp);
	
	printf("here\n");

    /* increment the value of writes in counts
     * by 1*/
    ds_counts.writes += 1;
    
    	/* if successful, return value of start */
	if (fwrite(ptr, sizeof(struct ds_blocks_struct), bytes, ds_file.fp) == 1)
	{
		return start;
	}
	
	/* return -1 if unsuccessful */
	else
	{
		return -1;
	}


}

/* search through the block array, until it finds the block's
   start value matches start */
void ds_free(long start)
{
  int i;

  /* search the block array */
  for (i = 0; i < MAX_BLOCKS; i++)
  {

    /* find a block whose start value is equal to start */
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
  fwrite(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp);

  /* close the file */
  fclose(ds_file.fp);

  /* print out the values of counts data structure */
  printf("reads: %d\n", ds_counts.reads);
  printf("writes: %d\n", ds_counts.writes);

  /* check if successful, return 1 */
  if (fwrite(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp) == 1)
  {
	  return 1;
  }
  
  /* if not, return 0 */
  else
  {
	  return 0;
  }

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
