/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:48:43 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/13 16:06:43 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philos(t_philo *philo, size_t seats)
{
	size_t	i;

	if (philo)
	{
		i = 0;
		while (i < seats)
		{
			pthread_mutex_destroy(&philo->state.mutex);
			pthread_mutex_destroy(&philo->meal_count.mutex);
			pthread_mutex_destroy(&philo->last_meal.mutex);
			pthread_mutex_destroy(&philo->my_fork.mutex);
			i++;
		}
		free(philo);
	}
}

int	terminate_simulation(t_monitor *monitor)
{
	if (monitor->philo)
		destroy_philos(monitor->philo, monitor->seats);
	pthread_mutex_destroy(&monitor->end_flag.mutex);
	pthread_mutex_destroy(&monitor->print_mutex);
	return (1);
}
