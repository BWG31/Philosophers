/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:42:00 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/21 16:58:10 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_simulation(t_philo *philo)
{
	close_shared_semaphores(philo);
	free(philo->pid);
}

void	close_shared_semaphores(t_philo *philo)
{
	if (philo->forks != SEM_FAILED)
		sem_close(philo->forks);
	if (philo->print != SEM_FAILED)
		sem_close(philo->print);
	if (philo->end_flag != SEM_FAILED)
		sem_close(philo->end_flag);
	if (philo->full != SEM_FAILED)
		sem_close(philo->full);
}

void	philo_exit(t_philo *philo, int exit_code)
{
	close_shared_semaphores(philo);
	sem_close(philo->update);
	free(philo->pid);
	exit(exit_code);
}

/*	Sends a signal to all active processes to terminate.
	If a trigger is specified, it will not send a signal to this process
	as it will have allready exited.
	philo->full semaphore is posted so that full_checker thread can finish */
int	terminate_all_philos(t_philo *philo, pid_t trigger)
{
	while (*philo->pid)
	{
		if (*philo->pid > 0 && *philo->pid != trigger)
			kill(*philo->pid, SIGTERM);
		sem_post(philo->full);
		philo->pid++;
	}
	return (1);
}
