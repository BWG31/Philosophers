/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:17:48 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/20 17:54:43 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# ifndef PHILO_LIMIT
#  define PHILO_LIMIT (200)
# endif

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define RST	"\x1B[0m"

# define MSG_FORK	"has taken a fork\n"
# define MSG_EAT	"is eating\n"
# define MSG_SLEEP	"is sleeping\n"
# define MSG_THINK	"is thinking\n"
# define MSG_DEAD	"died\n"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_state
{
	START,
	EATING,
	SLEEPING,
	THINKING,
	ACTION_COUNT,
	END_STATES,
	DEAD,
	STOP,
	STATE_COUNT
}	t_state;

enum e_fork
{
	RIGHT_FORK,
	LEFT_FORK,
	FORK_COUNT
};

typedef enum e_print
{
	P_FORK,
	P_EAT,
	P_SLEEP,
	P_THINK,
	P_DEAD,
	P_LIMIT
}	t_print;

typedef struct s_shared
{
	size_t			value;
	pthread_mutex_t	mutex;
}					t_shared;

typedef struct s_time
{
	struct timeval	start;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
}					t_time;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	size_t			seats;
	t_shared		state;
	t_shared		meal_count;
	t_shared		last_meal;
	t_shared		my_fork;
	t_shared		*forks[FORK_COUNT];
	t_shared		*end_flag;
	t_time			*time;
	pthread_mutex_t	*print_mutex;
}					t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	size_t			seats;
	size_t			times_to_eat;
	t_time			time;
	t_shared		end_flag;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}					t_monitor;

// main
void	print_simulation_report(t_monitor *monitor);
// input_check
int		ft_atoi(const char *c);
int		invalid_input(int argc, char **argv);
// init
int		init_simulation(t_monitor *monitor, int argc, char **argv);
int		init_monitor(t_monitor *monitor, int argc, char **argv);
t_philo	*init_philos(t_monitor *m);
void	init_philos_mutexes(t_philo *philo);
size_t	set_right_fork_value(size_t id, size_t seats);
// utils
size_t	get_timestamp(struct timeval start);
void	philo_time(size_t ms);
int		print_event(t_philo *philo, t_print print_code);
t_bool	end_flag(t_shared *end_flag);
// run
int		run_simulation(t_monitor *monitor);
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
// monitor
void	*monitor_routine(void *arg);
t_bool	a_philo_died(t_monitor *monitor, t_philo *philo);
size_t	last_meal_time(t_philo *philo);
t_bool	philos_all_full(t_monitor *monitor, t_philo *philo);
void	toggle_end_flag(t_monitor *monitor);
// philo_actions
void	define_philo_actions(void (*actions[])(t_philo *));
void	philo_start(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
// philo_utils
t_state	get_philo_state(t_philo *philo);
void	philo_update(t_philo *philo);
void	set_state(t_philo *philo, t_state new_state);
void	update_last_meal(t_philo *philo);
void	update_meal_count(t_philo *philo);
// forks
t_bool	my_turn(t_philo *philo);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
// terminate
int		terminate_simulation(t_monitor *monitor);

#endif