#include "shellheader.h"

/**
 * main - my own shell
 * Return: always 0, success
*/
int main(void)
{
	myshell_loop();

return (0);
}

/**
 * sig_handler - Function to happen when SINGIN is detected by signal
 * @signal: integer representing the signal
 * Return: nothing, always succes
*/
void sig_handler(int signal)
{
	if (signal == SIGINT)
	write(1, "\n($)", 4);
}

/**
 * myshell_loop - function that will mantain my shell running
 * Return: nothing, will always execute
*/
void myshell_loop(void)
{
	char *user_command, **args;
	int shell_status;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
	perror("hsh");

	if (isatty(STDIN_FILENO) != 1)
	{
		while (1)
		{
			user_command = read_command();
			args = split_into_arguments(user_command);
			myshell_execute(args);

			free(args);
			free(user_command);
		}
		return;
	}
	else
	{
		do {
		printf("($)");
		user_command = read_command();
		while (*user_command == '\0') /*to identify an enter*/
		{
			free(user_command);
			printf("($)");
			user_command = read_command();
		}
		args = split_into_arguments(user_command);
		if (args == NULL)
		break;
		shell_status = myshell_execute(args);
		free(user_command);
		free(args);
		if (shell_status == 2)
		exit(EXIT_SUCCESS);
		} while (shell_status);
	}
}
