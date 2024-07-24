/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:24:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/24 06:33:29 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taken_forks_and_eat(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "has taken a fork";
	pthread_mutex_lock(philo->fork_l);
	time_ms = 0;
	ft_print(philo, str, time_ms);
	if (philo->info->nop != 1)
	{
		pthread_mutex_lock(philo->fork_r);
		time_ms = 0;
		ft_print(philo, str, time_ms);
		ft_print(philo, "is eating", time_ms);
		pthread_mutex_lock(&philo->info->meals);
		philo->last_eat = get_time();
		philo->nbr_eat += 1;
		if (philo->nbr_eat == philo->info->notepme)
			philo->info->t_eat += 1;
		pthread_mutex_unlock(&philo->info->meals);
		sleep_time(philo->info->tte);
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
	time_ms = 0;
	ft_print(philo, str, time_ms);
	sleep_time(philo->info->tts);
	return (0);
}

int	thinking_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "is thinking";
	time_ms = 0;
	ft_print(philo, str, time_ms);
	return (0);
}

int	died_philo(t_philo *philo)
{
	char			*str;
	size_t			time_ms;

	str = "died";
	time_ms = get_time() - philo->start_eat;
	printf("%lu %d \033[0;31m%s\033[0m\n", time_ms, philo->id_philo, str);
	return (0);
}
