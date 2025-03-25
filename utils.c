/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:38:33 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/25 23:42:19 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "unistd.h"

void error_exit(const char *str)
{
	printf(RED"%s\n", str);
	exit(EXIT_FAILURE);
}
void philo_think_when_no_forks(t_philo *philo)
{
    t_data *data = philo->data;

    if (!data->end_time)
    {
        pthread_mutex_lock(&data->print_mutex);
        printf("%zu %d is thinking\n", get_current_time(), philo->id);
        pthread_mutex_unlock(&data->print_mutex);
    }
}
void *philo_routine(void *arg)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;
    if (philo->id % 2)  // Filósofos impares comienzan un poco más tarde
        usleep(1000);  // Introduce un retraso mayor para desincronizar los hilos
    while (!data->end_time && (philo->meals_counter < (size_t)data->nbr_limit_meals 
        || data->nbr_limit_meals == (size_t)-1))
    {
        if (philo_take_forks(philo))  // Si puede tomar los tenedores
        {
            philo_eat(philo);
            philo_sleep(philo);
            philo_think(philo);
        }
        else
        {
            philo_think_when_no_forks(philo);
        }
        if (has_phil_died(philo))  // Verifica si el filósofo ha muerto
            break;
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
        while (i < data->number_of_philosophers && !data->end_time)
        {
            if (has_phil_died(&data->philos[i]))
                return NULL;
            i++;
            usleep(500);  // Revisar más frecuentemente (cada 0.5ms)
        }
    }
    return NULL;
}

    
int has_phil_died(t_philo *philo)
{
    size_t current;
    size_t elapsed;
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&data->print_mutex);
    current = get_current_time();
    elapsed = current - philo->last_meal;
    
    if (elapsed >= data->time_to_die)
    {
        if (!data->end_time)
        {
            printf(MAG"%zu %d died\n", current - data->start_time, philo->id);
            data->end_time = true;
        }
        pthread_mutex_unlock(&data->print_mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->print_mutex);
    return (0);
}

void	clean(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i].t_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philos);
	free(data->forks);
}








