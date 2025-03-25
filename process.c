/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:14:21 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/25 21:12:57 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_current_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);  // Obtiene el tiempo actual en microsegundos
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));  // Convierte a milisegundos
}


void philo_eat(t_philo *philo)
{
    t_data *data;
    size_t current;

    data = philo->data;
    pthread_mutex_lock(&data->print_mutex);
    current = get_current_time();
    philo->last_meal = current;  // Actualizar tiempo antes de comer
    if (!data->end_time)
        printf("%zu %d is eating\n", current - data->start_time, philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    
    philo->meals_counter++;
    usleep(data->time_to_eat * 1000);  // Convertir ms a microsegundos
    pthread_mutex_unlock(&philo->right_fork->t_mtx);
    pthread_mutex_unlock(&philo->left_fork->t_mtx);
}

void philo_sleep(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&data->print_mutex);
    if (!data->end_time)
        printf("%zu %d is sleeping\n", get_current_time() - data->start_time, philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    usleep(data->time_to_sleep * 1000);  // Convertir ms a microsegundos
}

void philo_think(t_philo *philo)
{
    t_data *data;
    size_t timestamp;

    data = philo->data;
    timestamp = get_current_time() - data->start_time;  // Calcula el tiempo transcurrido
    pthread_mutex_lock(&data->print_mutex);
    if (!data->end_time)
        printf("%zu %d is thinking\n", timestamp, philo->id);  // Muestra el tiempo en milisegundos
    pthread_mutex_unlock(&data->print_mutex);
}


int philo_take_forks(t_philo *philo)
{
    t_data *data;
    size_t current;

    data = philo->data;

    if (data->end_time)
        return 0;

    pthread_mutex_lock(&philo->left_fork->t_mtx);
    pthread_mutex_lock(&philo->right_fork->t_mtx);

    current = get_current_time();
    pthread_mutex_lock(&data->print_mutex);
    if (!data->end_time)
        printf("%zu %d has taken both forks\n", current - data->start_time, philo->id);
    pthread_mutex_unlock(&data->print_mutex);

    return (1);
}








