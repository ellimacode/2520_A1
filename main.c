#include <stdio.h>
#include "ds_memory.h"

int main()
{
ds_create("test.bin", 1234);

ds_malloc(10);

ds_malloc(100000);


return 0;
}
