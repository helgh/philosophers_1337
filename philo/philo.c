/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:50:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/01 17:04:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(void *ptr, char *str)
{
	if (ptr)
		free(ptr);
	printf("%s\n", str);
}

void	ft_print(t_philo *philo, char *str, size_t time_ms)
{
	pthread_mutex_lock(&philo->info->dead);
	time_ms = get_time() - philo->start_eat;
	if (philo->info->died_philo == 0)
		printf("%lu %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->dead);
}

void	*routine_function(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *) philo;
	if (philos->id_philo % 2 == 0)
		usleep(300);
	while (check_if_dead(philos) == 0 && philos->info->nop > 1)
	{
		taken_forks_and_eat(philos);
		sleeping_philo(philos);
		thinking_philo(philos);
	}
	return (philo);
}

int	create_thread(t_philo *philo)
{
	int			i;

	i = -1;
	while (++i < philo->info->nop)
	{
		if (pthread_create(&philo[i].thread, NULL,
				routine_function, (void*) &philo[i]) != 0)
			return (-1);
		if (pthread_detach(philo[i].thread) != 0)
			return (-1);
	}
	i = -1;
	while (++i < philo->info->nop)
	{
		pthread_mutex_lock(&philo->info->meals);
		if (check_philo(&philo[i]) != 0)
			break ;
		pthread_mutex_unlock(&philo->info->meals);
		if (i == philo->info->nop - 1)
			i = -1;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (ac != 5 && ac != 6)
		return (print_error(NULL, "Error: invalid arguments number"), 1);
	if (check_args(ac, av) == -1)
		return (print_error(NULL, "Error: invalid arguments"), 1);
	fork = init_fork(a_to_i(av[1]));
	if (!fork)
		return (print_error(NULL, "Error: invalid arguments"), 1);
	philo = init_struct(ac, av, fork);
	if (!philo)
		return (print_error(fork, "Error: invalid arguments"), 1);
	create_thread(philo);
	destroy_mutex_and_free(philo);
}
