/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:49:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/25 06:57:50 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	size_t			time_ms;
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_ms);
}

void	sleep_time(size_t time_ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time_ms)
		usleep(500);
}

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead);
	if (philo->info->died_philo != 0)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (-1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

int	check_philo(t_philo *philo)
{
	int				i;
	size_t			time_ms;

	i = -1;
	if (check_nbr_eat(philo) != 0)
		return (-1);
	if (philo->info->nop == 1)
	{
		taken_forks_and_eat(philo);
		sleep_time(philo->info->ttd);
		died_philo(philo);
		return (-1);
	}
	time_ms = get_time();
	if (time_ms - philo->last_eat >= philo->info->ttd)
	{
		pthread_mutex_lock(&philo->info->dead);
		died_philo(philo);
		philo->info->died_philo = -1;
		//pthread_mutex_unlock(&philo->info->dead);
		return (-1);
	}
	return (0);
}

int	check_nbr_eat(t_philo *philo)
{
	int	nbr_eat;

	if (philo->info->notepme == -1)
		return (0);
	nbr_eat = philo->info->nop;
	if (nbr_eat == philo->info->t_eat)
	{
		pthread_mutex_lock(&philo->info->dead);
		philo->info->died_philo = -1;
		//pthread_mutex_unlock(&philo->info->dead);
		return (-1);
	}
	return (0);
}
