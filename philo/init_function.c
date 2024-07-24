/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:16:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/24 00:03:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_fork(int nop)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	if (nop == 0)
		return (NULL);
	fork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nop);
	if (!fork)
		return (NULL);
	while (++i < nop)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork[i]);
			return (free(fork), NULL);
		}
	}
	return (fork);
}

t_Gen_info	*init_mutex(void)
{
	t_Gen_info	*info;

	info = malloc(sizeof(t_Gen_info));
	if (!info)
		return (NULL);
	if (pthread_mutex_init(&info->dead, NULL) != 0)
		return (free(info), NULL);
	if (pthread_mutex_init(&info->meals, NULL) != 0)
		return (pthread_mutex_destroy(&info->dead), free(info), NULL);
	return (info);
}

t_Gen_info	*init_gen_info(char **argv, int argc)
{
	t_Gen_info	*info;

	info = init_mutex();
	if (!info)
		return (NULL);
	info->nop = a_to_i(argv[1]);
	info->ttd = a_to_i(argv[2]);
	if (info->nop == 0 || info->nop > 200 || info->ttd < 1)
		return (free(info), NULL);
	info->tte = a_to_i(argv[3]);
	info->tts = a_to_i(argv[4]);
	if (info->tte < 1 || info->tts < 1)
		return (free(info), NULL);
	if (argc == 6)
	{
		info->notepme = a_to_i(argv[5]);
		if (info->notepme == 0)
			return (free(info), NULL);
	}
	else
		info->notepme = -1;
	info->died_philo = 0;
	info->t_eat = 0;
	return (info);
}

t_philo	*init_struct(int argc, char **argv, pthread_mutex_t *fork)
{
	t_philo			*philos;
	t_Gen_info		*info;
	int				i;

	i = -1;
	info = init_gen_info(argv, argc);
	if (!info)
		return (NULL);
	philos = (t_philo *) malloc(sizeof(t_philo) * info->nop);
	if (!philos)
		return (free(info), NULL);
	while (++i < info->nop)
	{
		philos[i].info = info;
		philos[i].id_philo = i + 1;
		philos[i].nbr_eat = 0;
		philos[i].last_eat = get_time();
		philos[i].start_eat = get_time();
		philos[i].fork_l = &fork[i];
		if (i == 0)
			philos[i].fork_r = &fork[info->nop - 1];
		else
			philos[i].fork_r = &fork[i - 1];
	}
	return (philos);
}
