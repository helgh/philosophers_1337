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
	pthread_mutex_lock(&philo->info->write);
	if (philo->info->died_philo == 0)
		printf("%lums %d %s\n", time_ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->info->write);
}

void	*routine_function(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *) philo;
	usleep(8 * philos[0].info->nop + (philos[0].info->nop * 2));
	if (philos->id_philo % 2 == 0)
		usleep(100);
	while (check_if_dead(philo) == 0)
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
		if (pthread_create(&philo[i].thread, NULL,
				routine_function, (void*) &philo[i]) != 0)
			return (-1);
	while (1)
		if (check_philo(philo) != 0 || check_nbr_eat(philo) != 0)
			break ;
	i = -1;
	while (++i < philo[0].info->nop)
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
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
