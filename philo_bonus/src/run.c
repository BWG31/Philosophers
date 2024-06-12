/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:52:48 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 11:32:18 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*full_check(void *arg)
{
	t_philo	*philo;
	size_t	i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->count)
	{
		sem_wait(philo->full);
		i++;
	}
	sem_post(philo->end_flag);
	return (NULL);
}

static int	spawn_philos(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->count)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] < 0)
			return (terminate_all_philos(philo, 0));
		if (philo->pid[i] == 0)
		{
			philo->id = i + 1;
			if (philo_routine(philo))
				philo_exit(philo, EXIT_FAILURE);
			philo_exit(philo, EXIT_SUCCESS);
		}
		i++;
	}
	return (0);
}

static int	handle_philo_exits(t_philo *philo, size_t active_processes)
{
	int		status;
	pid_t	exited_pid;

	while (active_processes)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (exited_pid > 0)
		{
			active_processes--;
			if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
				return (terminate_all_philos(philo, exited_pid));
		}
	}
	return (0);
}

int	run_simulation(t_philo *philo)
{
	pthread_t	full_checker;

	if (pthread_create(&full_checker, NULL, &full_check, philo))
		return (printf(RED"Thread creation error\n"RST), 1);
	if (spawn_philos(philo) == 1)
		return (printf(RED"Error spawning philos: fork() error\n"RST), 1);
	if (handle_philo_exits(philo, philo->count))
		return (printf(RED"Philo process error, terminated philos\n"RST), 1);
	else
		printf(GRN"|== All Philo processes exited successfully ==|\n"RST);
	if (pthread_join(full_checker, NULL))
	{
		printf(RED"Error joining full_checker thread\n"RST);
		terminate_all_philos(philo, 0);
		return (1);
	}
	return (0);
}
