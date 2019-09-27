#include <stdio.h>
#include "ds_memory.h"

int main()
{

  long memory;
  ds_create("test.bin", 1234);

  ds_init("test.bin");


  printf("Calling ds_malloc(10)\n");
  memory = ds_malloc(10);
  printf("Return value is %ld\n", memory);

  printf("Calling ds_malloc(100000)\n");
  memory = ds_malloc(100000);
  printf("Return value is %ld\n", memory);

  ds_finish();





return 0;
}
