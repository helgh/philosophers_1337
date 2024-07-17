/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:24:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/17 04:22:55 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taken_forks_and_eat(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "has taken a fork";
	time_ms = get_time() - philo->start_eat;
	pthread_mutex_lock(philo->fork_l);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	if (philo[0].info->nop != 1)
	{
		pthread_mutex_lock(philo->fork_r);
		time_ms = get_time() - time_ms;
		printf("%lums %d %s\n", time_ms, philo->id_philo, str);
		printf("%lums %d %s\n", time_ms, philo->id_philo, "is eating");
		usleep(philo[0].info->tte);
		philo->last_eat = time_ms;
		philo->nbr_eat = 1;
		pthread_mutex_unlock(philo->fork_r);
	}
	pthread_mutex_unlock(philo->fork_l);
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "is sleeping";
	time_ms = get_time() - philo->start_eat;
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	usleep(philo->info->tts);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}

int	thinking_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "is thinking";
	time_ms = get_time() - philo->start_eat;
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}

int	died_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "is died";
	time_ms = get_time() - philo->start_eat;
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}
