/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead->dead);
	philo->dead->dead_stop = 1;
	pthread_mutex_unlock(&philo->dead->dead);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead->dead);
	if (philo->dead->dead_stop == 1)
	{
		pthread_mutex_unlock(&philo->dead->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->dead->dead);
	return (0);
}

int	print_state(t_philo *philo, const char *msg)
{
	long	now;
	long	elapsed;

	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(&philo->dead->dead);
	if (philo->dead->dead_stop)
	{
		pthread_mutex_unlock(&philo->dead->dead);
		pthread_mutex_unlock(philo->print_mutex);
		return (1);
	}
	now = get_current_time();
	elapsed = now - philo->start_time;
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	pthread_mutex_unlock(&philo->dead->dead);
	pthread_mutex_unlock(philo->print_mutex);
	return (0);
}

void	precise_sleep(long ms, t_philo *philo)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < ms)
	{
		if (check_death(philo))
			break ;
		usleep(100);
	}
}
