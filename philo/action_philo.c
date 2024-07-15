/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:24:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/15 00:37:54 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping_philo(t_Gen_info *info)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	usleep(info->tts);
	print_action("is sleeping", info, &time);
	return (0);
}

int	thinking_philo(t_Gen_info *info)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	print_action("is thinikng", info, &time);
	return (0);
}

int	died_philo(t_Gen_info *info)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	print_action("is died", info, &time);
	return (0);
}

// int	eating_philo(t_Gen_info *info)
// {

// }