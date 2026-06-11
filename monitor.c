/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	report_philo_death(t_philo *philo, int i, long now)
{
	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(&philo->dead->dead);
	if (philo->dead->dead_stop == 0)
	{
		philo->dead->dead_stop = 1;
		printf("%ld %d died\n", now - philo[i].start_time, philo[i].id);
	}
	pthread_mutex_unlock(&philo->dead->dead);
	pthread_mutex_unlock(philo->print_mutex);
	return (1);
}

static int	check_starvation_round(t_philo *philo, int amount)
{
	int		finished;
	int		i;
	long	now;
	long	last_meal;

	i = 0;
	while (i < amount)
	{
		now = get_current_time();
		pthread_mutex_lock(&philo[i].meal_mutex);
		last_meal = philo[i].last_meal_time;
		finished = philo[i].finished;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		if (!finished && now - last_meal >= philo[i].time_to_die)
			return (report_philo_death(philo, i, now));
		i++;
	}
	return (0);
}

void	*starve_check(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo[0].start_time)
		usleep(100);
	while (!check_death(&philo[0]))
	{
		if (check_starvation_round(philo, philo[0].amount))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
