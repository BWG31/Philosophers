/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:35:20 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/15 16:53:50 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_state	get_philo_state(t_philo *philo)
{
	t_state	current;

	pthread_mutex_lock(&philo->state.mutex);
	current = philo->state.value;
	pthread_mutex_unlock(&philo->state.mutex);
	return (current);
}

/*	If current state is an END_STATE, will do nothing.
	If end_flag is true, will set state to STOP.
	Otherwise will move on to next state within 1-3 range
	(EATING[1] - SLEEPING[2] - THINKING[3]) */
void	philo_update(t_philo *philo)
{
	t_state	current;

	current = get_philo_state(philo);
	if (current > END_STATES)
		return ;
	if (end_flag(philo->end_flag))
		set_state(philo, STOP);
	else
		set_state(philo, (current % 3) + 1);
}

void	set_state(t_philo *philo, t_state new_state)
{
	pthread_mutex_lock(&philo->state.mutex);
	if (philo->state.value < END_STATES)
		philo->state.value = new_state;
	pthread_mutex_unlock(&philo->state.mutex);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal.mutex);
	philo->last_meal.value = get_timestamp(philo->time->start);
	pthread_mutex_unlock(&philo->last_meal.mutex);
}

void	update_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_count.mutex);
	philo->meal_count.value++;
	pthread_mutex_unlock(&philo->meal_count.mutex);
}
