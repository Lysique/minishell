#include "../../includes/minishell.h"

char	*next_word(char *s, char c)
{
	char	*d;

	d = s;
	while (*d == c && *d != '\0')
		d++;
	return (d);
}

char	*ft_word(char const *s, char c)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	while (s[j] != c && s[j] != '\0')
		j++;
	i = 0;
	if (*s == '\0')
		return ((char *)s);
	str = malloc (sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	s = &s[i];
	return (str);
}

char	*ft_splitfct(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (s[j] != c && s[j] != '\0')
		j++;
	i = 0;
	if (*s == '\0')
		return ((char *)s);
	while (i < j)
		i++;
	s = &s[i];
	return ((char *)s);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	**tabres;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	tab = malloc (sizeof(char *) * (count_sep((char *)s, c) + 1));
	if (!tab)
		return (tab);
	tabres = tab;
	while (*s)
	{
		s = next_word((char *)s, c);
		if (*s == '\0')
			break ;
		*tab++ = ft_word(s, c);
		s = ft_splitfct(s, c);
		j++;
		s = next_word((char *)s, c);
		if (*s == '\0')
			break ;
	}
	*tab = NULL;
	return (tabres);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;
	char	*rres;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	res = malloc (i + j + 1);
	if (!res)
		return (res);
	rres = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (rres);
}
