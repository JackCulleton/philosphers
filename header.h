/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_monitor
{
	pthread_mutex_t	*lock;
	int				*stick_states;
}					t_monitor;

typedef struct s_dead
{
	int				dead_stop;
	pthread_mutex_t	dead;
}					t_dead;

typedef struct s_meal
{
	int				philo_meals_counted;
	pthread_mutex_t	meal_counter;
}					t_meal;

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				amount;
	int				meal_count;
	int				max_meals;
	int				finished;
	long			last_meal_time;
	long			start_time;
	t_dead			*dead;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*print_mutex;
	t_monitor		*monitor;
	t_meal			*meal_check;
}					t_philo;

typedef struct s_sim
{
	t_philo			*philos;
	int				amount;
	t_dead			*dead;
	pthread_mutex_t	print_mutex;
	t_monitor		*monitor;
	t_meal			*meal_check;
	long			start_time;
}					t_sim;

int					validate(int argc, char **argv);
int					check_positive(int argc, char **argv);
int					is_digit(int argc, char **argv);
int					init_dead(t_sim *sim);
int					init_monitor(t_sim *sim);
int					init_meal(t_sim *sim);
void				free_monitor(t_sim *sim);
void				init_thread(t_philo *philo, int amount);
void				*count(void *arg);
void				*starve_check(void *arg);
long				get_current_time(void);
int					check_death(t_philo *philo);
void				set_dead(t_philo *philo);
int					print_state(t_philo *philo, const char *msg);
int					wait_4_fork(t_philo *philo);
int					philo_eat(t_philo *philo);
void				update_meal(t_philo *philo);
void				put_fork_down(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				precise_sleep(long ms, t_philo *philo);
int					check_eat_count(t_philo *philo);

#endif
