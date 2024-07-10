/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:40:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:29 by hael-ghd         ###   ########.fr       */
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
	pthread_t		thread;
	int				id_philo;
	int				nbr_eat;
	size_t			last_eat;
	size_t			start_eat;
	t_Gen_info		*general_info;
}					t_philo;

typedef struct s_Gen_info
{
	int				nop;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	int				notepme;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	writing;
	t_philo			**philo;
}				t_Gen_info;

/*--------------------------parsing_function--------------------------*/

int	check_args(int argc, char **argv);

#endif