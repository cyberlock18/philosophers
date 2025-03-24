/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:33:02 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/24 22:16:55 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int data_init(t_data *data)
{
	size_t i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return(printf("Error: memory allocation for forks failed\n"),free(data->forks),0);
	data->forks = malloc(sizeof(t_fork) * data->number_of_philosophers);
	if (!data->forks)
		return(printf("Error: memory allocation for forks failed\n"),free(data->forks),0);	
	while(i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].is_eating = false;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) 
			% data->number_of_philosophers];
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_init(&data->forks[i].t_mtx, NULL);
		if (pthread_mutex_init(&data->forks[i].t_mtx, NULL) != 0)
			return(free(data->philos),free(data->forks), 0);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	return(1);
}
void set_start_time(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    data->start_time = 0;  // Convierte el tiempo a milisegundos
}





int create_philos_threads(t_data *data)
{
	size_t i;
	i=0;
	while(i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i].id_thread, NULL, philo_routine, (void *)&data->philos[i]))
			return(printf("Error: pthread_create failed\n"), 1);
		i++;
	}
	return(0);
}

int create_monitor_thread(t_data *data)
{
	pthread_t monitor_thread;
	if (pthread_create(&monitor_thread, NULL, monitor_routine, (void *)data))
		return(printf("Error: pthread_create failed\n"), 1);
	return(0);
}
int wait_for_threads(t_data *data)
{
	size_t i;

	i = 0;
	while(i < data->number_of_philosophers)
	{
		if(pthread_join(data->philos[i].id_thread, NULL))
			return(printf("Error: pthread_join failed\n"), 1);
		i++;
	}
	return(0);
}
