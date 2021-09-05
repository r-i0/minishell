#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# define FD_MAX 2000

typedef enum e_path_type
{
	UNKNOWN,
	IS_FILE,
	IS_DIR,
	ELSE_TYPE
}	t_path_type;

typedef enum e_fd_mode
{
	STD_SAVE,
	STD_RESTORE,
	FD_REDIRECTED,
	ALL_CLOSE
}	t_fd_mode;

//execution_start.c
int			execute_loop(t_execdata *data);
void		execute_start(t_execdata *data);

//setdata_cmdline_redirection.c
int			setdata_cmdline_redirect(t_execdata *data);

//setdata_heredoc_cmdtype.c
void		setdata_heredoc_cmdtype(t_execdata *data);

//command_*.c
void		builtin_echo(t_execdata *data);
void		builtin_cd(t_execdata *data);
void		builtin_pwd(t_execdata *data);
void		builtin_export(t_execdata *data);
void		builtin_unset(t_execdata *data);
void		builtin_env(t_execdata *data);
void		builtin_exit(t_execdata *data);
void		non_builtin(t_execdata *data);

//execution_utils.c
t_path_type	ft_stat(char *pathname);
int			ft_dup2(int oldfd, int newfd);
int			ft_open(t_iolist *filenode, \
					int flags, mode_t mode);
void		execute_command(t_execdata *data);
void		open_fd_handler(t_execdata *data, int mode, int redireceted_fd);

//env_functions.c
char		*ft_getenv(t_envlist *elst, char *search_key);
t_envlist	*ft_unsetenv(t_envlist *elst, char *rm_key);
void		ft_setenv(t_envlist *elst, char *new_key, \
						char *new_value, int append);

//execution_utils_list.c
char		**convert_envlist_2dchar(t_envlist *elst);
char		**convert_cmdlist_2dchar(t_cmdlist *clst);

//execution_utils_libft.c
long		ft_atol(char *str, bool *nonnum_check);
int			ft_strcmp(char *s1, char *s2);
void		free_2d_array(char **array);

//wrapper2.c
char		*ft_xstrjoin(char *str1, char *str2);
char		**ft_xsplit(char *src_str, char cut_char);
void		xclose(int fd);
int			xdup2(int oldfd, int newfd);
int			xdup(int oldfd);

//wrapper3.c
void		xwaitpid(pid_t pid, int *wstatus, int options);
void		xpipe(int *pipefd);
pid_t		xfork(void);

//minishell_loop.c
void		minishell_loop(char **envp);

//expansion_iolist.c
int			expand_filename(t_iolist *iolist, t_envlist *envlist);

//expansion_io_utils.c
void		clear_quot_filename(char **filename, char **filequot);
size_t		expansion_key_io(char **line, \
				t_envlist *envlist, char *doll_ptr);
char		*ft_strdoll(const char *s);

#endif