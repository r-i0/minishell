#include "../includes/minishell.h"

bool	is_delimiter(char c)
{
	if (!(ft_isalnum(c) || c == '_'))
		return (true);
	else
		return (false);
}

char	*ft_strjoin_three(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_xstrjoin(str1, str2);
	ret = ft_xstrjoin(tmp, str3);
	xfree(tmp);
	return (ret);
}

size_t	ft_strlen_excluded_quot(char *str, char *quot)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && quot[i] == '1')
			|| (str[i] == '\"' && quot[i] == '2'))
		{
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

bool	is_delimiter_quot(char c, char flag)
{
	if (((c == '\'' && (flag == '1' || flag == 'S'))
			|| (c == '\"' && (flag == '2' || flag == 'D'))))
	{
		return (true);
	}
	else
		return (false);
}