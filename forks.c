/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	try_take_forks(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(philo->monitor->lock);
	if (philo->monitor->stick_states[left] == 'D'
		&& philo->monitor->stick_states[right] == 'D')
	{
		philo->monitor->stick_states[left] = 'U';
		philo->monitor->stick_states[right] = 'U';
		pthread_mutex_unlock(philo->monitor->lock);
		return (1);
	}
	pthread_mutex_unlock(philo->monitor->lock);
	return (0);
}

static void	wait_before_retry(t_philo *philo)
{
	long	last_meal;
	long	min_wait;
	long	waited;
	int		meal_count;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal_time;
	meal_count = philo->meal_count;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (meal_count == 0)
		return ;
	min_wait = philo->time_to_eat * 2;
	if (philo->amount % 2 == 1)
		min_wait = philo->time_to_eat * 3;
	waited = get_current_time() - last_meal;
	if (waited < min_wait)
		precise_sleep(min_wait - waited, philo);
}

int	wait_4_fork(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->amount;
	wait_before_retry(philo);
	if (check_death(philo))
		return (1);
	while (!try_take_forks(philo, left, right))
	{
		if (check_death(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

void	put_fork_down(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->amount;
	pthread_mutex_lock(philo->monitor->lock);
	philo->monitor->stick_states[left] = 'D';
	philo->monitor->stick_states[right] = 'D';
	pthread_mutex_unlock(philo->monitor->lock);
}
