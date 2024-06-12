/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:46:28 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/20 17:49:46 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_not_number(char *s)
{
	while (*s)
	{
		if (*s < '0' || '9' < *s)
			return (1);
		s++;
	}
	return (0);
}

int	ft_atoi(const char *c)
{
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	while (('\t' <= *c && *c <= '\r') || *c == ' ')
		c++;
	if (*c == '+')
		c++;
	else if (*c == '-')
	{
		sign = -1;
		c++;
	}
	while (*c && (*c >= '0' && *c <= '9'))
		number = number * 10 + (*c++ - '0');
	return (number * sign);
}

static int	print_help(void)
{
	printf(GRN"Usage:\t./philo <pcount> <t2d> <t2e> <t2s> [eatnum]\n"YEL \
					"- pcount:	number of philosophers (and also forks)\n" \
					"- t2d:		time to die (ms)\n" \
					"- t2e:		time to eat (ms)\n" \
					"- t2s:		time to sleep (ms)\n" \
					"- eatnum:	number of times each philosopher must eat" \
					"(optional)\n"RST);
	return (1);
}

int	invalid_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || 6 < argc)
	{
		printf(RED"Wrong argument count\n");
		return (print_help());
	}
	i = 1;
	while (i < argc)
	{
		if (is_not_number(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			printf(RED"Error: arg %d invalid\n"RST, i);
			return (print_help());
		}
		if (i == 1 && ft_atoi(argv[i]) > PHILO_LIMIT)
		{
			printf(RED"Error: Too many philosophers! Limit: %d\n", PHILO_LIMIT);
			printf("Safeguard to avoid kill signal from system.\n");
			printf("Set PHILO_LIMIT in philo_bonus.h at your own risk!\n"RST);
			return (print_help());
		}
		i++;
	}
	return (0);
}
