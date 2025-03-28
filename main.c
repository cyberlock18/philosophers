/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:46:19 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/27 12:10:00 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dinner(t_data *data)
{
	set_start_time(data);
	if (create_philos_threads(data))
		return (0);
	if (create_monitor_thread(data))
		return (0);
	if (wait_for_threads(data))
		return (0);
	return (1);
}

int	main(int arc, char **argv)
{
	t_data	data;

	if (arc == 5 || arc == 6)
	{
		memset(&data, 0, sizeof(t_data));
		valid_input(argv, &data);
		if (!data_init(&data))
		{
			error_exit("Failed to initialize data\n");
			return (1);
		}
		if (!start_dinner(&data))
		{
			clean(&data);
			error_exit("Simulation failed\n");
			return (1);
		}
		clean(&data);
	}
	else
		return (error_exit("wrong input\n"), 1);
	return (0);
}
