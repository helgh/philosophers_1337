/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:24:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/19 23:57:45 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taken_forks_and_eat(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "has taken a fork";
	pthread_mutex_lock(philo->fork_l);
	time_ms = get_time() - philo->start_eat;
	ft_print(philo, str, time_ms);
	if (philo[0].info->nop != 1)
	{
		pthread_mutex_lock(philo->fork_r);
		time_ms = get_time() - philo->start_eat;
		ft_print(philo, str, time_ms);
		ft_print(philo, "is eating", time_ms);
		pthread_mutex_lock(&philo->info->meals);
		philo->nbr_eat += 1;
		pthread_mutex_unlock(&philo->info->meals);
		philo->last_eat = get_time();
		sleep_time(philo[0].info->tte);
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
	ft_print(philo, str, time_ms);
	sleep_time(philo->info->tts);
	return (0);
}

int	thinking_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "is thinking";
	time_ms = get_time() - philo->start_eat;
	ft_print(philo, str, time_ms);
	return (0);
}

int	died_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "is died";
	time_ms = get_time() - philo->start_eat;
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d \033[0;31m%s\033[0m\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}
