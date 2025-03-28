#include "philo.h"

static int	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i].t_mtx, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static void	assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].is_eating = false;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		if (data->number_of_philosophers == 1)
			data->philos[i].right_fork = NULL;
		else
			data->philos[i].right_fork = &data->forks[(i + 1)
					% data->number_of_philosophers];
		i++;
	}
}

int	data_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (printf("Error: memory allocation for philosophers failed\n"), 0);
	data->forks = malloc(sizeof(t_fork) * data->number_of_philosophers);
	if (!data->forks)
		return (printf("Error: memory allocation for forks failed\n"),
			free(data->philos), 0);
	if (!init_forks(data))
		return (free(data->philos), free(data->forks), 0);
	assign_forks(data);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (1);
}

double 	set_start_time(t_data *data)
{
	struct timeval	tv;
	size_t			i;

	gettimeofday(&tv, NULL);
	// Asegurar precisión de microsegundos en el tiempo inicial
	data->start_time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	// Pequeña pausa para sincronización inicial
	usleep(50);
	return (data->start_time);
}

int create_philos_threads(t_data *data)
{
    size_t i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_create(&data->philos[i].id_thread, NULL, 
            philo_routine, (void *)&data->philos[i]))
            return (printf("Error: pthread_create failed\n"), 1);
        i++;
    }
    return (0);
}

int create_monitor_thread(t_data *data)
{
    if (pthread_create(&data->monitor_thread, NULL, monitor_routine, (void *)data))
        return (printf("Error: monitor thread join failed\n"), 1);
    return (0);
}

int wait_for_threads(t_data *data)
{
    size_t i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_join(data->philos[i].id_thread, NULL))
            return (printf("Error: pthread_join failed\n"), 1);
        i++;
    }
    if (pthread_join(data->monitor_thread, NULL))
        return (printf("Error: monitor thread join failed\n"), 1);
    return (0);
}
