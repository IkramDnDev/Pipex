/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:30:21 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/12 21:57:09 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	int		i;
	int		j;
	char	*total_str;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	total_str = (char *)malloc(total_len + 1);
	if (!total_str)
		return (NULL);
	i = -1;
	while (s1[++i])
		total_str[i] = s1[i];
	j = -1;
	while (s2[++j])
		total_str[i + j] = s2[j];
	total_str[i + j] = '\0';
	return (total_str);
}
