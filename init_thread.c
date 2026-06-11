/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	init_start_times(t_philo *philo, int amount)
{
	long	start;
	int		i;

	start = get_current_time() + 500;
	i = 0;
	while (i < amount)
	{
		philo[i].start_time = start;
		pthread_mutex_lock(&philo[i].meal_mutex);
		philo[i].last_meal_time = start;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
}

static void	start_threads(t_philo *philo, pthread_t *thread, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_create(&thread[i], NULL, count, &philo[i]);
		i++;
	}
}

static void	join_threads(pthread_t *thread, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

void	init_thread(t_philo *philo, int amount)
{
	pthread_t	*thread;
	pthread_t	monitor;

	thread = malloc(sizeof(pthread_t) * amount);
	if (!thread)
		return ;
	init_start_times(philo, amount);
	start_threads(philo, thread, amount);
	if (amount > 1)
		pthread_create(&monitor, NULL, starve_check, philo);
	join_threads(thread, amount);
	if (amount > 1)
		pthread_join(monitor, NULL);
	free(thread);
}
