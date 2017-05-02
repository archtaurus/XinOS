/* string.c for XinOS */

#include "types.h"
#include "string.h"

/* 返回字符串长度 */
size_t strlen(const char *str){
	size_t i = 0;
	while(str[i++]);
	return i;
}
