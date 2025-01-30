/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:32:12 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/11 09:54:06 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_exist(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*newstr;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_exist(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_exist(set, s1[end - 1]))
		end--;
	newstr = (char *)malloc((end - start + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (start < end)
		newstr[i++] = s1[start++];
	newstr[i] = '\0';
	return (newstr);
}
