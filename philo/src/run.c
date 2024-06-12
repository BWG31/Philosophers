/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:50:36 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/21 16:54:36 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_simulation(t_monitor *monitor)
{
	size_t	i;

	gettimeofday(&monitor->time.start, NULL);
	while (monitor->time.start.tv_usec % 1000 > 10)
		gettimeofday(&monitor->time.start, NULL);
	if (pthread_create(&monitor->thread, NULL, &monitor_routine, monitor))
		return (printf("Thread creation error\n"), 1);
	i = 0;
	while (i < monitor->seats)
	{
		if (pthread_create(&monitor->philo[i].thread, NULL, \
							&philo_routine, &monitor->philo[i]))
			return (printf("Thread creation error\n"), 1);
		i++;
	}
	i = 0;
	while (i < monitor->seats)
		if (pthread_join(monitor->philo[i++].thread, NULL))
			return (printf("Thread join error\n"), 1);
	if (pthread_join(monitor->thread, NULL))
		return (printf("Thread join error\n"), 1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	void	(*actions[ACTION_COUNT])(t_philo *);

	philo = (t_philo *)arg;
	define_philo_actions(actions);
	while (get_philo_state(philo) < END_STATES)
	{
		actions[get_philo_state(philo) % ACTION_COUNT](philo);
		philo_update(philo);
	}
	return (NULL);
}
