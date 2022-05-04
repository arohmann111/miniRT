/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 09:54:55 by afrasch           #+#    #+#             */
/*   Updated: 2021/12/06 13:00:02 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts how many 'words' there are in s, seperated by the delimiter */
static int	ft_word_count(const char *s, char c)
{
	int	bool;
	int	words;
	int	i;

	bool = 0;
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			bool = 0;
		else if (bool == 0)
		{
			words++;
			bool = 1;
		}
		i++;
	}
	return (words);
}

/* Fills the array with the words */
static char	**ft_put_words_in_arr(const char *s, char c, int words, char **arr)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[j] = ft_substr(s, start, i - start);
		if (arr[j] == NULL)
		{
			ft_free_array(arr);
			return (NULL);
		}
		i++;
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

/* Allocates and returns an array of strings by splitting str ’s’ using char ’c’
   as a delimiter. The array ends with a NULL pointer. */
char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	if (!s || s[0] == '\0')
		return (0);
	words = ft_word_count(s, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (0);
	arr = ft_put_words_in_arr(s, c, words, arr);
	return (arr);
}
