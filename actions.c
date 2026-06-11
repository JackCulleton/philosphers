/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	philo_eat(t_philo *philo)
{
	int	result;

	if (print_state(philo, "has taken a fork"))
		return (1);
	if (print_state(philo, "has taken a fork"))
		return (1);
	update_meal(philo);
	if (print_state(philo, "is eating"))
		return (1);
	precise_sleep(philo->time_to_eat, philo);
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	result = check_eat_count(philo);
	if (result == 1)
		return (1);
	return (0);
}

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	philo_sleep(t_philo *philo)
{
	if (print_state(philo, "is sleeping"))
		return ;
	precise_sleep(philo->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	if (print_state(philo, "is thinking"))
		return ;
}
