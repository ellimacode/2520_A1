#include <stdio.h>
#include "ds_memory.h"

int main()
{

  /* check return value created by ds_create */
   if (ds_create("test.bin", 1234) == 0)
   {
     printf("Success\n");

   }

   else
   {
     printf("Failure\n");
   }


return 0;
}
