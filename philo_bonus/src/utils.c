/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:49 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 11:13:16 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_timestamp(struct timeval start)
{
	struct timeval	current;
	size_t			milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = (current.tv_sec - start.tv_sec) * 1000 \
					+ (current.tv_usec / 1000 - start.tv_usec / 1000);
	return (milliseconds);
}

void	philo_time(size_t ms)
{
	struct timeval	start;
	size_t			elapsed;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < ms)
	{
		usleep((ms - elapsed) / 2);
		elapsed = get_timestamp(start);
	}
}

int	print_event(t_philo *philo, t_print print_code)
{
	size_t		timestamp;
	static char	*color[] = {RED, GRN, YEL, CYN, MAG, BLU};
	static char	*msg[] = {MSG_FORK, MSG_EAT, MSG_SLEEP, MSG_THINK, MSG_DEAD};

	if (print_code >= P_LIMIT)
		return (1);
	sem_wait(philo->print);
	timestamp = get_timestamp(philo->time.start);
	printf("%s%zu\tms\t\t%zu\t", \
	color[(philo->id - 1) % 6], timestamp, philo->id);
	printf("%s"RST, msg[print_code]);
	sem_post(philo->print);
	return (0);
}
