/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:14:21 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/16 20:34:12 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_eat(t_philo *philo)
{
    t_data *data;
	
	data= philo->data;
    pthread_mutex_lock(&data->print_mutex);
    printf("%zu %d is eating\n", get_timestamp(data) / 1000, philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    philo->last_meal = get_timestamp(data);
    philo->meals_counter++;
    usleep(data->time_to_eat); // YA está en microsegundos, no multiplicamos por 1000
    pthread_mutex_unlock(&philo->right_fork->t_mtx);
    pthread_mutex_unlock(&philo->left_fork->t_mtx);
}


void philo_sleep(t_philo *philo)
{
    t_data *data;

	data = philo->data;
    pthread_mutex_lock(&data->print_mutex);
    printf("%zu %d is sleeping\n", get_timestamp(data) / 1000, philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    usleep(data->time_to_sleep); // YA está en microsegundos
}



void philo_think(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d is thinking\n", get_current_time()-data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}
int philo_take_forks(t_philo *philo)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&philo->left_fork->t_mtx);
    pthread_mutex_lock(&data->print_mutex);
    printf("%zu %d has taken fork1\n", get_timestamp(data) / 1000, philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    pthread_mutex_lock(&philo->right_fork->t_mtx);
    pthread_mutex_lock(&data->print_mutex);
    printf("%zu %d has taken fork2\n", get_timestamp(data) / 1000, philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    return 1;
}





