/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:25:14 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/24 22:09:46 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int isvalid(const char *str1)
{
	if (!str1 || !*str1)
		return (0);
	if (*str1 == ' ' || (*str1 > 9 && *str1 < 13))
		return (0);
	if (*str1 == '-' || *str1 == '+')
		str1++;
	while (*str1)
	{
		if (*str1 < '0' || *str1 > '9')
			return (0);
		str1++;
	}
	return (1);
}

static size_t ft_atol(const char *str)
{
	size_t res;
	int sign;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str > 9 && *str < 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
	{
		str++;
		if (*str < '0' || *str > '9')
			return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res > ((size_t)MAX - (*str - '0')) / 10)
		{
			error_exit("number too large");
			return (0);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

void valid_input(char **argv, t_data *data)
{
    if (!isvalid(argv[1]) || !isvalid(argv[2]) || !isvalid(argv[3]) || !isvalid(argv[4]))
        error_exit("Invalid input");
    data->number_of_philosophers = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);  // Asegúrate de que esta entrada sea en milisegundos
    data->time_to_eat = ft_atol(argv[3]);  // Asegúrate de que esta entrada sea en milisegundos
    data->time_to_sleep = ft_atol(argv[4]);  // Asegúrate de que esta entrada sea en milisegundos
    if (data->number_of_philosophers < 2 || data->number_of_philosophers > 200)
        error_exit("Invalid number_of_philosophers (must be between 2 and 200)");
    if (data->time_to_die < 60)
        error_exit("Invalid time_to_die (must be >= 60)");
    if (data->time_to_eat < 60)
        error_exit("Invalid time_to_eat (must be >= 60)");
    if (data->time_to_sleep < 60)
        error_exit("Invalid time_to_sleep (must be >= 60)");
    if (argv[5])
    {
        if (!isvalid(argv[5]))
            error_exit("Invalid meal count");
        data->nbr_limit_meals = ft_atol(argv[5]);
        if (data->nbr_limit_meals < 1)
            error_exit("Invalid meal count");
    }
    else
        data->nbr_limit_meals = -1;
}


void clean(t_data *data)
{
	free(data->philos);
	free(data->forks);
}

