/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_monitor(t_sim *sim)
{
	free(sim->monitor->lock);
	free(sim->monitor->stick_states);
	free(sim->monitor);
}

int	init_dead(t_sim *sim)
{
	sim->dead = malloc(sizeof(t_dead));
	if (!sim->dead)
		return (0);
	sim->dead->dead_stop = 0;
	pthread_mutex_init(&sim->dead->dead, NULL);
	return (1);
}

int	init_meal(t_sim *sim)
{
	sim->meal_check = malloc(sizeof(t_meal));
	if (!sim->meal_check)
	{
		free_monitor(sim);
		free(sim->dead);
		return (0);
	}
	sim->meal_check->philo_meals_counted = 0;
	pthread_mutex_init(&sim->meal_check->meal_counter, NULL);
	return (1);
}

int	init_monitor(t_sim *sim)
{
	int	i;

	sim->monitor = malloc(sizeof(t_monitor));
	if (!sim->monitor)
		return (0);
	sim->monitor->lock = malloc(sizeof(pthread_mutex_t));
	sim->monitor->stick_states = malloc(sizeof(int) * sim->amount);
	if (!sim->monitor->lock || !sim->monitor->stick_states)
	{
		free_monitor(sim);
		free(sim->dead);
		return (0);
	}
	pthread_mutex_init(sim->monitor->lock, NULL);
	i = 0;
	while (i < sim->amount)
		sim->monitor->stick_states[i++] = 'D';
	return (1);
}
