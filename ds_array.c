/* Full Name: Camille Cua
 * Student ID number: 1046663
 * Email: ccua@uoguelph.ca */

#include "ds_array.h"
#include "ds_memory.h"

/* global variable - holds the number of elements currently
 * in the array */
long elements;

/* this function */
int ds_create_array()
{
	/* call ds_init to open the file
     * "array.bin"*/
	ds_init("array.bin");
	
	/* should ds_malloc for single long
	 * at the beginning of the file */
	fseek(ds_file.fp, 0, SEEK_SET);
	
	/* set value of long to 0, no elements currently
	 * in array */
	/* call once to allocate data for the entire array */
	ds_malloc(0);
	
	/* to close the file and print the number of reads
	 * and writes */
	ds_finish();
	
return 0;
}

/* this function should access an array on disk */
int ds_init_array()
{
	/* calling ds_init to open the file */
	ds_init("array.bin");
	
	/* read the first block of memory, which holds a long
	 * and store the value in global variable elements */
	elements = fread(ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp);
	
	
return 0;
}

/* this function should replace the contents located at given index
 * in the array with value*/
int ds_replace(int value, long index)
{
	/*call ds_write, replace contents at given index with value */
	ds_write(index, ds_file.block, value);
	

return 0;
}


/* this function should store contents located at index in the file in a
 * temporary variable */
int ds_insert(int value, long index)
{
	int i;
	
	/* temporary variable */
	long new;
	
	/* loop starts at index and loops to last element in the
	 * array */
	for (i = 0; i < MAX_BLOCKS; i++)
	{
		i = index;
		
		/* convert index to file location */
		new = (index*sizeof(int)) + sizeof(elements);
		
		ds_read(ds_file.block, new, sizeof(new));
		
	}
	
	/* increment the value of elements */
	elements += 1;
	
	
return 0;
}

/* this function should remove the item at index */
int ds_delete(long index)
{
	int i;
	
	for (i = index; i < MAX_BLOCKS - 1; i++)
	{
		/* remove item at index */
	    ds_file.block[i] = ds_file.block[i + 1];
			
		/* reduce elements by 1 */
		elements -= 1;
	}
	
return 0;
}

/* this function should swap elements stored at
 * index1 and index2 */
int ds_swap(long index1, long index2)
{
	long temp;
	
	temp = index1;
	
	index1 = index2;
	
	index2 = temp;
	
	
	
return 0;
}

/* this function should search the array for first element
 * whose value is equal to target */
long ds_find(int target)
{

	
return 0;
}

int ds_read_elements(char *filename)
{
	
return 0;
}

int ds_finish_array()
{

	
return 0;
}
