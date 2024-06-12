/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:10:19 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 10:46:13 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	last_meal_time(t_philo *philo)
{
	size_t	result;

	sem_wait(philo->update);
	result = philo->last_meal;
	sem_post(philo->update);
	return (result);
}

static t_bool	philo_died(t_philo *philo)
{
	size_t	current_time;

	current_time = get_timestamp(philo->time.start);
	if (current_time - last_meal_time(philo) >= philo->time.to_die)
		return (TRUE);
	return (FALSE);
}

static void	*wait_for_end_flag(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->end_flag);
	if (get_philo_state(philo) < END_STATES)
		set_state(philo, STOP);
	sem_post(philo->end_flag);
	sem_post(philo->full);
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	end_flag_checker;

	philo = (t_philo *)arg;
	pthread_create(&end_flag_checker, NULL, &wait_for_end_flag, philo);
	while (get_philo_state(philo) < END_STATES)
	{
		if (philo_died(philo))
		{
			set_state(philo, DEAD);
			sem_post(philo->end_flag);
			print_event(philo, P_DEAD);
		}
		usleep(1000);
	}
	pthread_join(end_flag_checker, NULL);
	return (NULL);
}
