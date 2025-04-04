/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:10:17 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/25 21:21:56 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
#define _PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

# define MAX 2147483647
# define MIN -2147483648
# define RST "\033[0m"
# define RED "\033[1;31m"
# define GRN "\033[1;32m"
# define YEL "\033[1;33m"
# define BLU "\033[1;34m"
# define MAG "\033[1;35m"
# define CYN "\033[1;36m"
# define WHT "\033[1;37m"

typedef struct s_data t_data;
typedef struct s_fork t_fork;

typedef struct s_philo
{
    int id;
    size_t meals_counter;
    volatile bool is_eating;
    size_t last_meal;
    size_t time_offset;    // Nuevo campo para offset de tiempo
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t id_thread;
    t_data *data;
} t_philo;

struct s_fork
{
	pthread_mutex_t t_mtx;
	//t_mtx  forks_id;
	
};
struct s_data
{
	size_t number_of_philosophers;
	size_t time_to_die;
	size_t time_to_eat;
	size_t time_to_sleep;
	size_t nbr_limit_meals;
	size_t start_time;
	bool end_time;
	t_fork *forks;
	t_philo *philos;
	pthread_t monitor_thread;
	pthread_mutex_t print_mutex;
	
};
typedef struct s_time
{
    long int x;  // Microsegundos de la última medición (o alguna referencia temporal)
    long int c;  // Segundos de la última medición (o alguna referencia temporal)
    pthread_mutex_t lock;
} t_time;


void  	error_exit(const char *str);
void *philo_routine(void *arg);
int data_init(t_data *data);
double set_start_time(t_data *data);
int create_philos_threads(t_data *data);
int create_monitor_thread(t_data *data);
int wait_for_threads(t_data *data);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_think(t_philo *philo);
int philo_take_forks(t_philo *philo);
void *monitor_routine(void *arg);
size_t get_time_ms(void);
int has_phil_died(t_philo *philo);
void valid_input(char **argv, t_data *data);
void clean(t_data *data);
int start_dinner(t_data *data);
void precise_sleep(size_t duration, t_data *data);
void    print_status(t_data *data, int id, char *status);
void destroy_forks(t_data *data);

#endif