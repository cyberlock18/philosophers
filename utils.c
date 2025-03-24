/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:38:33 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/24 22:13:23 by ruortiz-         ###   ########.fr       */
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








/*size_t get_timestamp(t_data *data)
{
    struct timeval time;
    size_t current_time;

    gettimeofday(&time, NULL);
    current_time = (time.tv_sec * 1000 + time.tv_usec) / 1000;  // Convertir a ms con mayor precisión
    return (current_time - data->start_time);  // Devolver diferencia en ms
}*/



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
            usleep(100);  // Verificar más frecuentemente
        }
    }
    return NULL;
}

    
int has_phil_died(t_philo *philo)
{
    size_t current;
    t_data *data;

    data = philo->data;
    current = get_current_time() - data->start_time;  // Calcula la diferencia con el start_time

    if (current - philo->last_meal >= data->time_to_die)  // Compara el tiempo de muerte
    {
        pthread_mutex_lock(&data->print_mutex);
        if (!data->end_time)
        {
            printf("%zu %d died\n", current, philo->id);  // Imprime el tiempo en milisegundos
            data->end_time = true;
        }
        pthread_mutex_unlock(&data->print_mutex);
        return 1;
    }
    return 0;
}









