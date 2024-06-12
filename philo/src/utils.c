/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:24:06 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/16 12:23:32 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(philo->print_mutex);
	if (!end_flag(philo->end_flag) || print_code == P_DEAD)
	{
		timestamp = get_timestamp(philo->time->start);
		printf("%s%zu\tms\t\t%zu\t", \
			color[(philo->id - 1) % 6], timestamp, philo->id);
		printf("%s"RST, msg[print_code]);
	}
	pthread_mutex_unlock(philo->print_mutex);
	return (0);
}

t_bool	end_flag(t_shared *end_flag)
{
	t_bool	result;

	pthread_mutex_lock(&end_flag->mutex);
	result = end_flag->value;
	pthread_mutex_unlock(&end_flag->mutex);
	return (result);
}
