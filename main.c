#include <stdio.h>
#include "ds_memory.h"

int main()
{

  /* check return value created by ds_create */
   if (ds_create("test.bin", 0) == 0)
   {
     printf("Success\n");

   }

   else if (ds_create("test.bin", 0) != 0)
   {
     printf("Failues\n");
   }


return 0;
}
