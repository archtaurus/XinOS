/* string.c for XinOS */

#include "types.h"
#include "string.h"

uint16 strlen(const string str){
    uint16 i = 0;
    while(str[i++]);
    return i;
}
