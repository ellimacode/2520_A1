#include <stdio.h>
#include "ds_memory.h"

int main()
{

  /* check return value created by ds_create */
   if (ds_init("test.bin") == 0)
   {
     printf("Success!\n");

   }

   else
   {
     printf("Failure!\n");
   }


return 0;
}
