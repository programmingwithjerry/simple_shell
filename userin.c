#include "mshell.h"

void read_cmd(char *prompt_command, size_t prompt_size) 
{
	size_t len = 0;
	char *line = NULL;

	ssize_t read_bytes = getline(&line, &len, stdin);

	/* handle errors while reading user input */
	if (read_bytes == -1)
	{
		m_print("error while reading user input\n");
		exit(EXIT_FAILURE);
	} else if (read_bytes == 0) {
		m_print("\n");
		exit(EXIT_SUCCESS);
	}

	/* REMOVE TRAILING NEWLINE IF PRESENT */
	if (line [read_bytes -1] == '\n' ){
		line[read_bytes -1] = '\0';
	}

	/* copy the readline to prompt_command to ensure buffer size is sufficient*/
	strncpy(prompt_command, line, prompt_size -1 );
	prompt_command[prompt_size -1] = '\0';

	/* free the memory allocated by getline */
	free(line);
}
