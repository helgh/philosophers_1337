/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:24:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/16 21:33:39 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taken_forks(t_philo *philo)
{
	struct timeval	time;
	char			*str;
	size_t			time_ms;

	str = "has taken a fork";
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_lock(&philo->fork_l);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_lock(&philo->fork_r);
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - time_ms;
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	struct timeval	time;
	char			*str;
	size_t			time_ms;

	str = "is sleeping";
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	usleep(philo->info->tts);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}

int	thinking_philo(t_philo *philo)
{
	struct timeval	time;
	char			*str;
	size_t			time_ms;

	str = "is thinking";
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}

int	died_philo(t_philo *philo)
{
	struct timeval	time;
	char			*str;
	size_t			time_ms;

	str = "is died";
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_lock(&philo->info->write);
	printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}

// int	eating_philo(t_Gen_info *info)
// {

// }