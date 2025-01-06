/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:51:42 by ikhristi          #+#    #+#             */
/*   Updated: 2023/10/27 15:52:34 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *p)
{
	int			i;
	long int	k;

	i = -1;
	while (++i < p->params->num_p)
		pthread_create(&p[i].thread, NULL, &routine, &p[i]);
	i = -1;
	k = time_now();
	while (++i < p->params->num_p)
	{
		p[i].start = k;
		p[i].meal = k;
	}
	p->params->ready = 1;
}

void	init_mutex(t_philo *p, t_gdata *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
		pthread_mutex_init(p[i].forkl, NULL);
	pthread_mutex_init(params->print, NULL);
}

void	init_threads(t_philo *p, t_gdata *params)
{
	init_mutex(p, params);
	create_threads(p);
	check_threads(p);
}
