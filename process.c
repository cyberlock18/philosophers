/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:14:21 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/28 12:00:00 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_data *data, int id, char *status)
{
	size_t	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	if (!data->end_time)
	{
		timestamp = get_time_ms() - data->start_time;
		printf("%zu %d %s\n", timestamp, id, status);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

int	philo_take_forks(t_philo *philo)
{
	t_data	*data = philo->data;

	if (data->end_time)
		return (0);
	// Los filósofos pares e impares toman los tenedores en orden diferente
	// para evitar deadlocks
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->right_fork->t_mtx);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->t_mtx);
		print_status(data, philo->id, "has taken a fork");
	}
	else
	{
		usleep(100); // Pequeño delay para evitar competencia
		pthread_mutex_lock(&philo->left_fork->t_mtx);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->t_mtx);
		print_status(data, philo->id, "has taken a fork");
	}
	return (1);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data = philo->data;

	pthread_mutex_lock(&data->print_mutex);
	philo->is_eating = true;
	philo->last_meal = get_time_ms();
	if (!data->end_time)
		printf("%zu %d is eating\n", philo->last_meal - data->start_time,
			philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	
	precise_sleep(data->time_to_eat, data);
	philo->meals_counter++;
	
	pthread_mutex_lock(&data->print_mutex);
	philo->is_eating = false;
	pthread_mutex_unlock(&data->print_mutex);
	
	pthread_mutex_unlock(&philo->right_fork->t_mtx);
	pthread_mutex_unlock(&philo->left_fork->t_mtx);
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data = philo->data;

	print_status(data, philo->id, "is sleeping");
	precise_sleep(data->time_to_sleep, data);
}

void	philo_think(t_philo *philo)
{
	t_data	*data = philo->data;

	print_status(data, philo->id, "is thinking");
}
