/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:47:38 by ikhristi          #+#    #+#             */
/*   Updated: 2023/10/27 15:47:39 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *p, t_gdata *params)
{
	int	k;

	k = -1;
	while (++k < params->num_p)
	{
		p[k].start = 0;
		p[k].id = k + 1;
		p[k].thread = 0;
		p[k].meal = 0;
		p[k].forkl = &params->fork[k];
		if (p[k].id == params->num_p)
			p[k].forkr = &params->fork[0];
		else
			p[k].forkr = &params->fork[k + 1];
		p[k].params = params;
		p[k].iter = 0;
	}
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	arg_is_number(char *av)
{
	int	i;

	i = 0;
	while (av[i] && is_digit(av[i]))
		i++;
	if (av[i] != '\0' && !is_digit(av[i]))
		return (0);
	return (1);
}

int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!arg_is_number(av[i]))
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || \
		ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0 || \
		(av[5] && ft_atoi(av[5]) <= 0))
	{
		return (0);
	}
	return (1);
}

t_gdata	*parse_data(char **argv)
{
	t_gdata	*params;

	params = malloc(sizeof(t_gdata));
	if (params == NULL)
		return (NULL);
	params->print = malloc(sizeof(pthread_mutex_t));
	if (params->print == NULL)
		return (NULL);
	params->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (params->fork == NULL)
		return (NULL);
	params->ttd = ft_atoi(argv[2]);
	params->tte = ft_atoi(argv[3]);
	params->check_tme = 0;
	params->tts = ft_atoi(argv[4]);
	params->eated = 0;
	if (argv[5])
	{
		params->check_tme = 1;
		params->tme = ft_atoi(argv[5]);
	}
	params->num_p = ft_atoi(argv[1]);
	params->ready = 0;
	params->over = 0;
	return (params);
}
