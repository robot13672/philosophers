/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:22:24 by ikhristi          #+#    #+#             */
/*   Updated: 2023/10/27 15:48:38 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *p)
{
	long int	now;

	pthread_mutex_lock(p->params->print);
	now = time_now() - p->meal;
	if (now >= p->params->ttd)
	{
		pthread_mutex_unlock(p->params->print);
		ft_print(p, 5);
		pthread_mutex_unlock(p->forkl);
		pthread_mutex_unlock(p->forkr);
		return (1);
	}
	pthread_mutex_unlock(p->params->print);
	return (0);
}

void	check_threads(t_philo *p)
{
	int	i;

	while (!p->params->ready)
		continue ;
	while (!p->params->over)
	{
		i = -1;
		while (++i < p->params->num_p)
		{
			if (check_death(&p[i]))
				p->params->over = 1;
		}
		if (p->params->eated == p->params->num_p)
			p->params->over = 1;
	}
	return ;
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->forkl);
	ft_print(p, 4);
	pthread_mutex_lock(p->forkr);
	ft_print(p, 4);
	p->meal = time_now();
	p->iter++;
	ft_print(p, 1);
	ft_usleep(p->params->tte);
	pthread_mutex_unlock(p->forkl);
	pthread_mutex_unlock(p->forkr);
}

void	*routine(void *phil)
{
	t_philo	*p;

	p = (t_philo *)phil;
	while (!(p->params->ready))
		continue ;
	if (p->id & 1)
		ft_usleep(p->params->tte * 0.9 + 1);
	while (!p->params->over)
	{
		ft_eat(p);
		pthread_mutex_lock(p->params->print);
		if (p->params->check_tme && \
			p->iter == p->params->tme)
		{
			p->params->eated++;
			pthread_mutex_unlock(p->params->print);
			return (NULL);
		}
		pthread_mutex_unlock(p->params->print);
		ft_print(p, 2);
		ft_usleep(p->params->tts);
		ft_print(p, 3);
	}
	return (NULL);
}

void	free_all(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->params->num_p)
		pthread_mutex_destroy(p[i].forkl);
	pthread_mutex_destroy(p->params->print);
	free(p->params->print);
	free(p->params->fork);
	free(p->params);
	free(p);
}
