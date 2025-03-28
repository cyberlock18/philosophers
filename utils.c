/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:38:33 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/28 12:00:00 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	error_exit(const char *str)
{
	printf(RED"%s\n", str);
	exit(EXIT_FAILURE);
}

void	precise_sleep(size_t duration, t_data *data)
{
	size_t	start;

	start = get_time_ms();
	while (!data->end_time)
	{
		if ((get_time_ms() - start) >= duration)
			break ;
		usleep(200);
	}
}

int	has_phil_died(t_philo *philo)
{
	t_data	*data = philo->data;
	size_t	current;
	size_t	elapsed;

	current = get_time_ms();
	pthread_mutex_lock(&data->print_mutex);
	elapsed = current - philo->last_meal;

	if (philo->is_eating || elapsed < data->time_to_die)
	{
		pthread_mutex_unlock(&data->print_mutex);
		return (0);
	}

	if (!data->end_time)
	{
		data->end_time = true;
		printf("%zu %d died\n", current - data->start_time, philo->id);
	}
	pthread_mutex_unlock(&data->print_mutex);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	philo->last_meal = get_time_ms();
	if (philo->id % 2)
		usleep(1000);
	while (!data->end_time && 
		(philo->meals_counter < data->nbr_limit_meals 
		|| data->nbr_limit_meals == (size_t)-1))
	{
		philo_think(philo);
		if (!data->end_time && philo_take_forks(philo))
		{
			philo_eat(philo);
			if (!data->end_time)
				philo_sleep(philo);
		}
	}
	return (NULL);
}

void	scan_philosophers(t_data *data)
{
	size_t	i = 0;

	while (i < data->number_of_philosophers && !data->end_time)
	{
		if (has_phil_died(&data->philos[i]))
			return;
		i++;
		usleep(50); // Revisión más frecuente
	}
}

void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;

	while (!data->end_time)
	{
		scan_philosophers(data);
		usleep(100); // Reducido para detectar muerte más rápido
	}
	return (NULL);
}

void	destroy_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i].t_mtx);
		i++;
	}
}

void	clean(t_data *data)
{
	destroy_forks(data);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philos);
	free(data->forks);
}
