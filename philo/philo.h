/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:40:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/01 19:24:24 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id_philo;
	int				fork;
	pthread_t		thread;
	struct s_philo	*next;
}					t_philo;

typedef struct s_info
{
	int		nop;
	int		ttd;
	int		tte;
	int		tts;
	int		notepme;
	t_philo	*philo;
}				t_info;

/*--------------------------parsing_function--------------------------*/

int	check_args(int argc, char **argv);

#endif