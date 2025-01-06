/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:42:17 by ikhristi          #+#    #+#             */
/*   Updated: 2023/11/01 10:03:34 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->params->num_p)
		pthread_join(p[i].thread, (void *)&p[i]);
}

int	main(int argc, char **argv)
{
	t_gdata	*data;
	t_philo	*philos;

	if ((argc != 5 && argc != 6) || !check_input(argv))
	{
		ft_error_input();
		exit(0);
	}
	philos = malloc (sizeof(t_philo) * ft_atoi(argv[1]));
	data = parse_data(argv);
	init_philos(philos, data);
	init_threads(philos, data);
	join_threads(philos);
	free_all(philos);
}
