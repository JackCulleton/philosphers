/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	*single_philo_routine(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time,
		philo->id);
	precise_sleep(philo->time_to_die, philo);
	printf("%ld %d died\n", get_current_time() - philo->start_time, philo->id);
	return (NULL);
}

static int	run_cycle(t_philo *philo)
{
	int	done;

	if (check_death(philo))
		return (1);
	if (wait_4_fork(philo))
		return (1);
	if (check_death(philo))
	{
		put_fork_down(philo);
		return (1);
	}
	done = philo_eat(philo);
	put_fork_down(philo);
	if (done)
		return (1);
	philo_sleep(philo);
	philo_think(philo);
	return (0);
}

void	*count(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo->start_time)
		usleep(100);
	if (philo->amount == 1)
		return (single_philo_routine(philo));
	if (philo->id % 2 == 1)
		precise_sleep(philo->time_to_eat, philo);
	while (!run_cycle(philo))
		;
	return (NULL);
}

int	check_eat_count(t_philo *philo)
{
	int	must_stop;

	must_stop = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->max_meals > 0 && philo->meal_count >= philo->max_meals
		&& philo->finished == 0)
	{
		philo->finished = 1;
		must_stop = 1;
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!must_stop)
		return (0);
	pthread_mutex_lock(&philo->meal_check->meal_counter);
	philo->meal_check->philo_meals_counted++;
	if (philo->meal_check->philo_meals_counted == philo->amount)
		set_dead(philo);
	pthread_mutex_unlock(&philo->meal_check->meal_counter);
	return (1);
}
