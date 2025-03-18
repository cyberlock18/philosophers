/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:38:33 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/18 01:21:27 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  	error_exit(const char *str)
{
	printf(RED"%s\n", str);
	exit(EXIT_FAILURE);
}
void *philo_routine(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;
	if(philo->id % 2)
		usleep(1000);
	while (!data->end_time && (philo->meals_counter < data->nbr_limit_meals 
		|| data->nbr_limit_meals == -1))
	{
		if (philo_take_forks(philo))
		{
    		philo_eat(philo);
    		philo_sleep(philo);
    		philo_think(philo);
		}
		else
		{
    		pthread_mutex_lock(&data->print_mutex);
    		printf("%ld %d is thinking\n", get_current_time(), philo->id);
    		pthread_mutex_unlock(&data->print_mutex);
		}
    }
    return NULL;
}
size_t get_timestamp(t_data *data)
{
	struct timeval time;
    size_t timestamp;

    gettimeofday(&time, NULL);
    timestamp = (time.tv_sec * 1000000) + time.tv_usec; // Convertimos a microsegundos
    return (timestamp - data->start_time);
}
void *monitor_routine(void *arg)
{
    t_data *data;
    size_t i;

    data = (t_data *)arg;
    while (!data->end_time)
    {
        i = 0;
        while (i < data->number_of_philosophers)
        {
            if (has_philo_died(&data->philos[i]))
                return NULL;
            i++;
        }
        usleep(1000); // Pequeña pausa para evitar consumo excesivo de CPU
    }
    return NULL;
}
void *monitor_routine(void *arg)
{
    t_data *data;
    size_t i;

    data = (t_data *)arg;
    while (!data->end_time)
    {
        i = 0;
        while (i < data->number_of_philosophers)
        {
            if (has_philo_died(&data->philos[i]))
                return NULL;
            i++;
        }
        usleep(1000); // Pequeña pausa para evitar consumo excesivo de CPU
    }
    return NULL;
}