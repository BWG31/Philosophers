/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:04:30 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 11:26:24 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_philo_semaphore(t_philo *philo)
{
	char	*sem_name;

	sem_name = get_sem_name(philo->id);
	if (!sem_name)
		return (1);
	sem_unlink(sem_name);
	philo->update = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	free(sem_name);
	if (philo->update == SEM_FAILED)
		return (1);
	sem_unlink(sem_name);
	return (0);
}

int	philo_routine(t_philo *philo)
{
	void	(*actions[ACTION_COUNT])(t_philo *);

	if (init_philo_semaphore(philo))
		return (1);
	if (pthread_create(&philo->monitor, NULL, &monitor_routine, philo))
		return (1);
	define_philo_actions(actions);
	while (get_philo_state(philo) < END_STATES)
	{
		actions[get_philo_state(philo) % ACTION_COUNT](philo);
		philo_update(philo);
	}
	if (pthread_join(philo->monitor, NULL))
		return (1);
	return (0);
}
