/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:39:35 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/15 12:41:19 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	Returns TRUE is either fork value doesn't match the philo ID */
t_bool	my_turn(t_philo *philo)
{
	t_bool	r_result;
	t_bool	l_result;

	pthread_mutex_lock(&philo->forks[RIGHT_FORK]->mutex);
	r_result = (philo->forks[RIGHT_FORK]->value == philo->id);
	pthread_mutex_unlock(&philo->forks[RIGHT_FORK]->mutex);
	pthread_mutex_lock(&philo->forks[LEFT_FORK]->mutex);
	l_result = (philo->forks[LEFT_FORK]->value == philo->id);
	pthread_mutex_unlock(&philo->forks[LEFT_FORK]->mutex);
	return (r_result && l_result);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[RIGHT_FORK]->mutex);
	print_event(philo, P_FORK);
	pthread_mutex_lock(&philo->forks[LEFT_FORK]->mutex);
	print_event(philo, P_FORK);
}

/*	Puts forks back down, setting the value variable to the neighbour id */
void	drop_forks(t_philo *philo)
{
	if (philo->id == philo->seats)
		philo->forks[RIGHT_FORK]->value = 1;
	else
		philo->forks[RIGHT_FORK]->value = philo->id + 1;
	pthread_mutex_unlock(&philo->forks[RIGHT_FORK]->mutex);
	if (philo->id == 1)
		philo->forks[LEFT_FORK]->value = philo->seats;
	else
		philo->forks[LEFT_FORK]->value = philo->id - 1;
	pthread_mutex_unlock(&philo->forks[LEFT_FORK]->mutex);
}
