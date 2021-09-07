#include "minishell.h"

void	ft_perror(char *perror_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(perror_str);
}

void	ft_puterror(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	if (str3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}
