/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:57:04 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/16 11:47:24 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (!a_philo_died(monitor, monitor->philo) && \
			!philos_all_full(monitor, monitor->philo))
		usleep(100);
	return (NULL);
}

t_bool	a_philo_died(t_monitor *monitor, t_philo *philo)
{
	size_t	i;
	size_t	current_time;

	i = 0;
	while (i < monitor->seats)
	{
		current_time = get_timestamp(monitor->time.start);
		if (current_time - last_meal_time(&philo[i]) >= monitor->time.to_die)
		{
			toggle_end_flag(monitor);
			set_state(&philo[i], DEAD);
			print_event(&philo[i], P_DEAD);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

size_t	last_meal_time(t_philo *philo)
{
	size_t	result;

	pthread_mutex_lock(&philo->last_meal.mutex);
	result = philo->last_meal.value;
	pthread_mutex_unlock(&philo->last_meal.mutex);
	return (result);
}

t_bool	philos_all_full(t_monitor *monitor, t_philo *philo)
{
	size_t	i;
	size_t	full_philos;

	if (monitor->times_to_eat == 0)
		return (FALSE);
	i = 0;
	full_philos = 0;
	while (i < monitor->seats)
	{
		pthread_mutex_lock(&philo[i].meal_count.mutex);
		if (philo[i].meal_count.value >= monitor->times_to_eat)
			full_philos++;
		pthread_mutex_unlock(&philo[i].meal_count.mutex);
		i++;
	}
	if (full_philos == monitor->seats)
	{
		toggle_end_flag(monitor);
		return (TRUE);
	}
	return (FALSE);
}

void	toggle_end_flag(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->end_flag.mutex);
	monitor->end_flag.value = TRUE;
	pthread_mutex_unlock(&monitor->end_flag.mutex);
}
