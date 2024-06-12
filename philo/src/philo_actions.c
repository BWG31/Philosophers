/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:57:59 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/16 16:12:36 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	define_philo_actions(void (*actions[])(t_philo *))
{
	actions[START] = &philo_start;
	actions[EATING] = &philo_eat;
	actions[SLEEPING] = &philo_sleep;
	actions[THINKING] = &philo_think;
}

/*	Edge case handling: only 1 philosopher. */
void	philo_start(t_philo *philo)
{
	if (philo->seats == 1)
	{
		pthread_mutex_lock(&philo->forks[RIGHT_FORK]->mutex);
		print_event(philo, P_FORK);
		philo_time(philo->time->to_die + 1);
		pthread_mutex_unlock(&philo->forks[RIGHT_FORK]->mutex);
	}
	else if (philo->id % 2 == 0)
	{
		philo_think(philo);
		philo_time(philo->time->to_eat / 2);
	}
}

void	philo_eat(t_philo *philo)
{
	while (!my_turn(philo))
		usleep(5);
	take_forks(philo);
	if (!end_flag(philo->end_flag))
	{
		print_event(philo, P_EAT);
		update_last_meal(philo);
		philo_time(philo->time->to_eat);
		update_meal_count(philo);
	}
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_event(philo, P_SLEEP);
	philo_time(philo->time->to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_event(philo, P_THINK);
}
