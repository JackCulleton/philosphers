/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackculleton <jackculleton@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/12 18:27:50 by jackculleto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	init_philo_values(t_sim *sim, int i, int argc, char **argv)
{
	sim->philos[i].id = i + 1;
	sim->philos[i].time_to_die = atoi(argv[2]);
	sim->philos[i].time_to_eat = atoi(argv[3]);
	sim->philos[i].time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		sim->philos[i].max_meals = atoi(argv[5]);
	else
		sim->philos[i].max_meals = -1;
	sim->philos[i].meal_count = 0;
	sim->philos[i].finished = 0;
	sim->philos[i].amount = sim->amount;
	sim->philos[i].dead = sim->dead;
	sim->philos[i].print_mutex = &sim->print_mutex;
	sim->philos[i].last_meal_time = sim->start_time;
	sim->philos[i].start_time = sim->start_time;
	sim->philos[i].monitor = sim->monitor;
	sim->philos[i].meal_check = sim->meal_check;
}

static int	init_philos(t_sim *sim, int argc, char **argv)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->amount);
	if (!sim->philos)
		return (0);
	pthread_mutex_init(&sim->print_mutex, NULL);
	sim->start_time = get_current_time();
	i = 0;
	while (i < sim->amount)
	{
		pthread_mutex_init(&sim->philos[i].meal_mutex, NULL);
		init_philo_values(sim, i, argc, argv);
		i++;
	}
	return (1);
}

static void	cleanup_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->amount)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->dead->dead);
	pthread_mutex_destroy(&sim->meal_check->meal_counter);
	pthread_mutex_destroy(sim->monitor->lock);
	free(sim->philos);
	free_monitor(sim);
	free(sim->meal_check);
	free(sim->dead);
}

int	validate(int argc, char **argv)
{
	t_sim	sim;

	if (!check_positive(argc, argv))
	{
		printf("not positive");
		return (0);
	}
	if (!is_digit(argc, argv))
	{
		printf("not correct");
		return (0);
	}
	sim.amount = atoi(argv[1]);
	if (!init_dead(&sim) || !init_monitor(&sim) || !init_meal(&sim))
		return (0);
	if (!init_philos(&sim, argc, argv))
	{
		free_monitor(&sim);
		free(sim.meal_check);
		free(sim.dead);
		return (0);
	}
	init_thread(sim.philos, sim.amount);
	cleanup_sim(&sim);
	return (1);
}
