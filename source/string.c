/* string.c for XinOS */

#include "types.h"
#include "string.h"

uint16 strlen(const str string){
    uint16 i = 0;
    while(string[i++]);
    return i;
}
