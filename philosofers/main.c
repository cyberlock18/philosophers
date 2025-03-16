/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruortiz- <ruortiz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:46:19 by ruortiz-          #+#    #+#             */
/*   Updated: 2025/03/03 23:24:48 by ruortiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int main (int arc, char **argv)
{
	t_data data;

	if (arc == 5 || arc == 6)
	{
		memset(&data, 0, sizeof(t_data));
		valid_input(argv, &data);
		data_init(&data);
		start_dinner(&data);
		clean(&data);
	}
	else
	{
		error_exit("Wrong inpuu \n");
	}
}