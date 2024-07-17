/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:49:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/17 04:40:46 by hael-ghd         ###   ########.fr       */
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
	{
		died_philo(philo);
		return (pthread_mutex_unlock(&philo[0].info->dead), -1);
	}
	pthread_mutex_unlock(&philo[0].info->dead);
	return (0);
}

int	check_philo(t_philo *philo)
{
	int				i;
	int				time_ms;
	struct timeval 	time;

	i = -1;
	pthread_mutex_lock(&philo[0].info->dead);
	if (philo[0].info->nop == 1)
	{
		taken_forks_and_eat(philo);
		sleep_time(philo[0].info->ttd);
		printf("%zu here\n", philo[0].info->ttd);
		died_philo(philo);
		philo[0].info->died_philo = -1;
		return (-1);
	}
	while (++i < philo[0].info->nop)
	{
		gettimeofday(&time, NULL);
		time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		if (time_ms - philo[i].last_eat >= philo[0].info->ttd)
		{
			philo[i].info->died_philo = 1;
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo[0].info->dead);
	return (0);
}

// int	check_nbr_eat(t_philo *philo)
// {
	
// }