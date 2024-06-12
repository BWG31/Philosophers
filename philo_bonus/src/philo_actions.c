/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:09:01 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 11:34:07 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	define_philo_actions(void (*actions[])(t_philo *))
{
	actions[START] = &philo_start;
	actions[EATING] = &philo_eat;
	actions[SLEEPING] = &philo_sleep;
	actions[THINKING] = &philo_think;
}

/*	Handle edge case for 1 philo || Set priority for uneven id philos. */
void	philo_start(t_philo *philo)
{
	if (philo->count == 1)
	{
		sem_wait(philo->forks);
		print_event(philo, P_FORK);
		sem_wait(philo->end_flag);
		sem_post(philo->full);
	}
	else if (philo->id % 2 == 0)
	{
		philo_think(philo);
		philo_time(philo->time.to_eat / 2);
	}
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	if (get_philo_state(philo) < END_STATES)
	{
		print_event(philo, P_FORK);
		sem_wait(philo->forks);
		if (get_philo_state(philo) < END_STATES)
		{
			print_event(philo, P_FORK);
			print_event(philo, P_EAT);
			update_last_meal(philo);
			philo_time(philo->time.to_eat);
			update_meal_count(philo);
		}
		sem_post(philo->forks);
	}
	sem_post(philo->forks);
}

void	philo_sleep(t_philo *philo)
{
	print_event(philo, P_SLEEP);
	philo_time(philo->time.to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_event(philo, P_THINK);
}
