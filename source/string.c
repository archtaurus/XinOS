/* string.c for XinOS */

#include "types.h"
#include "string.h"

/* 返回字符串长度 */
uint32_t strlen(const char *str){
	uint32_t i = 0;
	while(str[i++]);
	return i;
}
