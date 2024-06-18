/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:16:20 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 10:50:14 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>

# ifndef PHILO_LIMIT
#  define PHILO_LIMIT (200)
# endif

# define RED	"\x1B[91m"
# define GRN	"\x1B[92m"
# define YEL	"\x1B[93m"
# define BLU	"\x1B[94m"
# define MAG	"\x1B[95m"
# define CYN	"\x1B[96m"
# define WHT	"\x1B[97m"
# define RST	"\x1B[0m"

# define MSG_FORK	"has taken a fork\n"
# define MSG_EAT	"is eating\n"
# define MSG_SLEEP	"is sleeping\n"
# define MSG_THINK	"is thinking\n"
# define MSG_DEAD	"died\n"

# define SEM_PHILO "/binary_semaphore_philo_"

# define SEM_FORKS "/semaphore_forks"
# define SEM_PRINT "/binary_semaphore_print"
# define SEM_END_FLAG "/binary_semaphore_end_flag"
# define SEM_FULL "/semaphore_full_flag"

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

typedef enum e_print
{
	P_FORK,
	P_EAT,
	P_SLEEP,
	P_THINK,
	P_DEAD,
	P_LIMIT
}	t_print;

typedef struct s_time
{
	struct timeval	start;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
}					t_time;

typedef struct t_philo
{
	pid_t			*pid;
	size_t			count;
	size_t			id;
	t_state			state;
	size_t			last_meal;
	int				meals_to_eat;
	t_time			time;
	sem_t			*update;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*end_flag;
	sem_t			*full;
	pthread_t		monitor;
}					t_philo;

// main
// input_check
int		ft_atoi(const char *c);
int		invalid_input(int argc, char **argv);
// init
int		init_simulation(t_philo *philo, int argc, char **argv);
// run
int		run_simulation(t_philo *philo);
// sem_name
char	*get_sem_name(int i);
// philo_routine
int		philo_routine(t_philo *philo);
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
// utils
size_t	get_timestamp(struct timeval start);
void	philo_time(size_t ms);
int		print_event(t_philo *philo, t_print print_code);
// monitor_routine
void	*monitor_routine(void *arg);
// end_simulation
void	end_simulation(t_philo *philo);
void	close_shared_semaphores(t_philo *philo);
void	philo_exit(t_philo *philo, int exit_code);
int		terminate_all_philos(t_philo *philo, pid_t trigger);
#endif