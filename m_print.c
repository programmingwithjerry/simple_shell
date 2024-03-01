#include "mshell.h"
/*
 * 
*/
void m_print(const char *string_prompt){
	write(STDOUT_FILENO, string_prompt, strlen(string_prompt));
}
