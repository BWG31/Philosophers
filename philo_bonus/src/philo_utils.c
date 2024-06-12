/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:12:33 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/21 17:18:28 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_state	get_philo_state(t_philo *philo)
{
	t_state	current;

	sem_wait(philo->update);
	current = philo->state;
	sem_post(philo->update);
	return (current);
}

void	philo_update(t_philo *philo)
{
	t_state	current;

	current = get_philo_state(philo);
	if (current > END_STATES)
		return ;
	else
		set_state(philo, (current % 3) + 1);
}

void	set_state(t_philo *philo, t_state new_state)
{
	sem_wait(philo->update);
	if (philo->state < END_STATES)
		philo->state = new_state;
	sem_post(philo->update);
}

void	update_last_meal(t_philo *philo)
{
	sem_wait(philo->update);
	philo->last_meal = get_timestamp(philo->time.start);
	sem_post(philo->update);
}

void	update_meal_count(t_philo *philo)
{
	t_bool	finished;

	finished = FALSE;
	sem_wait(philo->update);
	if (philo->meals_to_eat > 0)
	{
		philo->meals_to_eat--;
		if (philo->meals_to_eat == 0)
			finished = TRUE;
	}
	sem_post(philo->update);
	if (finished)
		sem_post(philo->full);
}
