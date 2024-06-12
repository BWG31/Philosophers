/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:39:30 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/21 17:17:36 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_semaphores(t_philo *philo, int philo_count)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_END_FLAG);
	sem_unlink(SEM_FULL);
	philo->forks = sem_open(SEM_FORKS, O_CREAT, 0644, philo_count);
	if (philo->forks == SEM_FAILED)
		return (printf(RED"sem_open error\n"RST), 1);
	sem_unlink(SEM_FORKS);
	philo->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (philo->print == SEM_FAILED)
		return (printf(RED"sem_open error\n"RST), 1);
	sem_unlink(SEM_PRINT);
	philo->end_flag = sem_open(SEM_END_FLAG, O_CREAT, 0644, 0);
	if (philo->end_flag == SEM_FAILED)
		return (printf(RED"sem_open error\n"RST), 1);
	sem_unlink(SEM_END_FLAG);
	philo->full = sem_open(SEM_FULL, O_CREAT, 0644, 0);
	if (philo->full == SEM_FAILED)
		return (printf(RED"sem_open error\n"RST), 1);
	sem_unlink(SEM_FULL);
	philo->update = NULL;
	return (0);
}

int	init_simulation(t_philo *philo, int argc, char **argv)
{
	philo->count = ft_atoi(argv[1]);
	philo->time.to_die = ft_atoi(argv[2]);
	philo->time.to_eat = ft_atoi(argv[3]);
	philo->time.to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = -1;
	if (init_semaphores(philo, ft_atoi(argv[1])))
		return (printf(RED"semaphore init error\n"RST), 1);
	philo->pid = malloc(sizeof(pid_t) * philo->count + 1);
	if (!philo->pid)
		return (printf(RED"malloc error\n"RST), 1);
	memset(philo->pid, 0, sizeof(int) * philo->count + 1);
	philo->id = 0;
	philo->state = START;
	philo->last_meal = 0;
	gettimeofday(&philo->time.start, NULL);
	while (philo->time.start.tv_usec % 1000 > 10)
		gettimeofday(&philo->time.start, NULL);
	return (0);
}
