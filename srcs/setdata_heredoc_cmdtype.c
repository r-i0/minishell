#include "minishell.h"

/*
** Used to prepare data before executing command.
** 1 Recieve all here documents and the pipe
**   (contains here documents) fd.
** 2 get command type of each data.
*/

static int	is_cmd_type(t_cmdlist *clst)
{
	if (clst == NULL)
		return (NON_CMD);
	else if (ft_strcmp(clst->str, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(clst->str, "cd") == 0)
		return (CD);
	else if (ft_strcmp(clst->str, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(clst->str, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(clst->str, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(clst->str, "env") == 0)
		return (ENV);
	else if (ft_strcmp(clst->str, "exit") == 0)
		return (EXIT);
	else
		return (OTHER);
}

static void	expansion_heredoc(char **line, t_envlist *elst)
{
	char	*doll_ptr;

	doll_ptr = ft_strdoll(*line);
	while (doll_ptr)
	{
		expansion_key_io(line, elst, doll_ptr);
		doll_ptr = ft_strdoll(*line);
	}
}

static t_cmd	get_here_doc(char *limiter, t_execdata *data, int is_quot)
{
	char	*line;
	int		pipefd[PIPEFD_NUM];
	int		no_limit;

	xpipe(pipefd);
	no_limit = 1;
	while (no_limit)
	{
		line = readline("> ");
		if (!line)
			exit(1);
		no_limit = ft_strcmp(line, limiter);
		if (no_limit)
		{
			if (is_quot == 0)
				expansion_heredoc(&line, data->elst);
			ft_putendl_fd(line, pipefd[WRITE]);
		}
		free(line);
	}
	xclose(pipefd[WRITE]);
	return (pipefd[READ]);
}

void	setdata_heredoc_cmdtype(t_execdata *data)
{
	t_iolist	*move;
	int			is_quot;

	is_quot = 0;
	while (data)
	{
		move = data->iolst;
		while (move)
		{
			if (move->c_type == IN_HERE_DOC)
			{
				if (ft_strchr(move->next->quot, '1') || \
					ft_strchr(move->next->quot, '2'))
					clear_quot_filename(&(move->next->str), \
						&(move->next->quot)), is_quot++;
				move->here_doc_fd = get_here_doc(move->next->str, \
										data, is_quot);
			}
			move = move->next;
		}
		data->cmd_type = is_cmd_type(data->clst);
		data = data->next;
	}
}
