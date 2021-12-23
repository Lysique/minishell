#include "../../includes/minishell.h"

int	ft_strchhr(char *envp)
{
	if (ft_strlen(envp) > 5)
	{
		if (ft_srch(envp) == 1)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && ft_check(s1[i], (char *)set))
		i++;
	j = ft_strlen((char *)s1);
	while (j > i && ft_check(s1[j - 1], (char *)set))
		j--;
	res = malloc(sizeof(char) * (j - i + 1));
	if (!res)
		return (res);
	k = i;
	l = 0;
	while (l < j - i)
	{
		res[l++] = s1[k];
		k++;
	}
	res[l] = '\0';
	return (res);
}

int	find_path2(char **tab, char *cmd, char **cmd1)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		*cmd1 = ft_strjoin(tab[i], "/");
		tmp = *cmd1;
		*cmd1 = ft_strjoin(*cmd1, cmd);
		free(tmp);
		if (!(*cmd1))
			return (0);
		if (access(*cmd1, X_OK) == 0)
			break ;
		free(*cmd1);
		i++;
	}
	if (tab[i] == NULL)
		return (0);
	return (1);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**tab;
	char	*cmd1;

	i = 0;
	while (ft_strchhr(envp[i]) == 0)
		i++;
	path = ft_strtrim(envp[i], "PATH=");
	tab = ft_split(path, ':');
	if (!tab)
		return (0);
	free(path);
	if (find_path2(tab, cmd, &cmd1) == 0)
		return (0);
	free(tab);
	return (cmd1);
}

int	count_sep(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}
