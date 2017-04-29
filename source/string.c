/* string.c for XinOS */

#include "types.h"
#include "string.h"

/* 返回字符串长度 */
uint32 strlen(const char *str){
	int i = 0;
	while(str[i++]);
	return i;
}
