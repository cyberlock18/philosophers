/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:33:02 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/13 23:55:12 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void data_init(t_data *data)
{
	size_t i;

	i = 0;
	data->end_time = false;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return(printf("Error: memory allocation for forks failed\n"),free(data->forks));
	data->forks = malloc(sizeof(t_fork) * data->number_of_philosophers);
	if (!data->forks)
		return(printf("Error: memory allocation for forks failed\n"),free(data->forks));	
	while(i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].is_eating = false;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) 
			% data->number_of_philosophers];
		pthread_mutex_init(&data->forks[i].t_mtx, NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
}
void set_start_time(t_data *data)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
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
