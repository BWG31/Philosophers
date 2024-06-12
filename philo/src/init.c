/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:35:52 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/16 12:17:52 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_monitor *monitor, int argc, char **argv)
{
	init_monitor(monitor, argc, argv);
	monitor->philo = init_philos(monitor);
	if (!monitor->philo)
		return (1);
	return (0);
}

int	init_monitor(t_monitor *monitor, int argc, char **argv)
{
	monitor->thread = NULL;
	monitor->seats = ft_atoi(argv[1]);
	monitor->time.to_die = ft_atoi(argv[2]);
	monitor->time.to_eat = ft_atoi(argv[3]);
	monitor->time.to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		monitor->times_to_eat = ft_atoi(argv[5]);
	else
		monitor->times_to_eat = 0;
	monitor->end_flag.value = FALSE;
	pthread_mutex_init(&monitor->end_flag.mutex, NULL);
	pthread_mutex_init(&monitor->print_mutex, NULL);
	monitor->philo = NULL;
	return (0);
}

t_philo	*init_philos(t_monitor *m)
{
	t_philo	*philo;
	size_t	i;

	philo = malloc(sizeof(t_philo) * m->seats);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < m->seats)
	{
		philo[i].id = i + 1;
		philo[i].seats = m->seats;
		philo[i].state.value = START;
		philo[i].meal_count.value = 0;
		philo[i].last_meal.value = 0;
		philo[i].my_fork.value = set_right_fork_value(i + 1, m->seats);
		init_philos_mutexes(&philo[i]);
		philo[i].forks[RIGHT_FORK] = &philo[i].my_fork;
		philo[i].forks[LEFT_FORK] = \
			&philo[(i + m->seats - 1) % m->seats].my_fork;
		philo[i].end_flag = &m->end_flag;
		philo[i].time = &m->time;
		philo[i].print_mutex = &m->print_mutex;
		i++;
	}
	return (philo);
}

void	init_philos_mutexes(t_philo *philo)
{
	pthread_mutex_init(&philo->state.mutex, NULL);
	pthread_mutex_init(&philo->meal_count.mutex, NULL);
	pthread_mutex_init(&philo->last_meal.mutex, NULL);
	pthread_mutex_init(&philo->my_fork.mutex, NULL);
}

size_t	set_right_fork_value(size_t id, size_t seats)
{
	if (id == seats)
		return (1);
	else
		return (id + ((id - 1) % 2));
}
