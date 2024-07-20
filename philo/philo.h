/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:40:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/20 04:02:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_Gen_info
{
	int				nop;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	int				notepme;
	int				died_philo;
	pthread_mutex_t	dead;
	pthread_mutex_t	meals;
	pthread_mutex_t	write;
}				t_Gen_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				id_philo;
	int				nbr_eat;
	size_t			last_eat;
	size_t			start_eat;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	t_Gen_info		*info;
}					t_philo;

/*--------------------------parsing_function--------------------------*/

int		check_args(int argc, char **argv);

/*--------------------------action_function--------------------------*/

void	print_action(char *str, t_philo *info, int time);
int		sleeping_philo(t_philo *info);
int		taken_forks_and_eat(t_philo *philo);
int		thinking_philo(t_philo *info);
int		died_philo(t_philo *info);
int		check_philo(t_philo *philo);
int		check_if_dead(t_philo *philo);
size_t	get_time(void);
void	sleep_time(size_t time_ms);
void	ft_print(t_philo *philo, char *str, size_t time_ms);
int		check_nbr_eat(t_philo *philo);

#endif