/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:47:21 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 09:37:47 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}

static int	intlen(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*str;

	num = (long)n;
	len = intlen(num);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
		num *= -1;
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = num % 10 + '0';
		num /= 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*get_sem_name(int i)
{
	char	*str_i;
	char	*name;

	str_i = ft_itoa(i);
	if (!str_i)
		return (NULL);
	name = ft_strjoin(SEM_PHILO, str_i);
	free(str_i);
	if (!name)
		return (NULL);
	return (name);
}
