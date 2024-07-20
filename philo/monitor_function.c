/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:49:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/20 00:40:18 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_time(size_t time_ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time_ms)
		usleep(500);
}

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo[0].info->dead);
	if (philo[0].info->died_philo != 0)
		return (pthread_mutex_unlock(&philo[0].info->dead), -1);
	pthread_mutex_unlock(&philo[0].info->dead);
	return (0);
}

int	check_philo(t_philo *philo)
{
	int				i;
	size_t				time_ms;

	i = -1;
	pthread_mutex_lock(&philo[0].info->dead);
	if (philo[0].info->nop == 1)
	{
		taken_forks_and_eat(philo);
		sleep_time(philo[0].info->ttd);
		died_philo(philo);
		philo[0].info->died_philo = -1;
		return (pthread_mutex_unlock(&philo[0].info->dead), -1);
	}
	while (++i < philo[0].info->nop)
	{
		time_ms = get_time();
		if (time_ms - philo[i].last_eat >= philo[0].info->ttd)
		{
			died_philo(&philo[i]);
			philo[i].info->died_philo = -1;
			return (pthread_mutex_unlock(&philo[0].info->dead), -1);
		}
	}
	pthread_mutex_unlock(&philo[0].info->dead);
	return (0);
}

int	check_nbr_eat(t_philo *philo)
{
	int	i;
	int	nbr_eat;

	i = -1;
	if (philo->info->notepme == -1)
		return (0);
	nbr_eat = philo->info->notepme;
	pthread_mutex_lock(&philo->info->meals);
	while (++i < philo->info->nop)
	{
		if (nbr_eat != philo[i].nbr_eat)
			return (pthread_mutex_unlock(&philo->info->meals), 0);
	}
	philo->info->died_philo = -1;
	pthread_mutex_unlock(&philo->info->meals);
	return (-1);
}