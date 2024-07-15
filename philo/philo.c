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
	exit(EXIT_FAILURE);
}

static int	check_ov(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (result > 9223372036854775807)
		return (check_ov(sign));
	return (result * sign);
}

static int	help_func(int len_str, char **str)
{
	int	i;
	int	s;
	int	l;

	s = 1;
	while (s < len_str)
	{
		l = 1;
		i = 0;
		while (str[s][i] != 0)
		{
			if (str[s][i] >= 48 && str[s][i] <= 57)
				l = 0;
			if (str[s][i] != 43)
				if (str[s][i] < 48 || str[s][i] > 57)
					return (-1);
			i++;
		}
		if (l == 1)
			return (-1);
		s++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	s;

	i = 1;
	if (help_func(argc, argv) == -1)
		return (-1);
	while (i < argc)
	{
		s = 0;
		while (argv[i][s] != 0)
		{
			if (argv[i][s] == 43 && s - 1 >= 0)
				return (-1);
			if (argv[i][s] == 43)
				if (argv[i][++s] == 43 || argv[i][s] == 0)
					return (-1);
			s++;
		}
		i++;
	}
	if (i == argc)
		return (0);
	return (-1);
}

pthread_mutex_t	*init_fork(int nop)
{
	pthread_mutex_t	*fork;
	int	i;

	i = 0;
	fork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nop);
	if (!fork)
		return (NULL);
	while (i++ < nop)
		pthread_mutex_init(&fork[i], NULL);
	return (fork);
}

t_Gen_info	*init_gen_info(char **argv, int argc)
{
	t_Gen_info	*info;

	info = malloc(sizeof(t_Gen_info));
	if (!info)
		return (NULL);
	if (pthread_mutex_init(&info->mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (NULL);
	info->nop = ft_atoi(argv[1]);
	info->ttd = ft_atoi(argv[2]);
	if (info->nop == 0 || info->nop > 200 || info->ttd < 1)
		return (NULL);
	info->tte = ft_atoi(argv[3]);
	info->tts = ft_atoi(argv[4]);
	if (info->tte < 1 || info->tts < 1)
		return (NULL);
	if (argc == 6)
	{
		info->notepme = ft_atoi(argv[5]);
		if (info->notepme == 0)
			return (NULL);
	}
	else
		info->notepme = -1;
	info->died_philo = 0;
	return (info);
}

t_philo	*init_struct(int argc, char **argv)
{
	pthread_mutex_t	*fork;
	t_philo			*philos;
	t_Gen_info		*info;
	int				i;

	i = -1;
	fork = init_fork(ft_atoi(argv[1]));
	info = init_gen_info(argv, argc);
	if (!info || !fork)
		return (NULL);
	philos = (t_philo *) malloc(sizeof(t_philo) * info->nop);
	if (!philos)
		return (NULL);
	while (++i < info->nop)
	{
		philos[i].id_philo = i + 1;
		philos[i].nbr_eat = 0;
		philos[i].last_eat = 0;
		philos[i].start_eat = 0;
		philos[i].fork_l = &fork[i];
		if (i == 0)
			philos[i].fork_r = &fork[info->nop - 1];
		else
			philos[i].fork_r = &fork[i - 1];
		philos[i].info = info;
	}
	return (philos);
}

// void	print_action(char *str, t_philo *philo, int time)
// {
// 	pthread_mutex_lock(&philo[i].info.write);
// 	printf("%dms %d %s\n", time, philo[i].id_philo, str);
// 	pthread_mutex_unlock(&&philo[i].info.write);
// }

// void	*routine_function(void *info)
// {
// 	t_Gen_info *inf = (t_Gen_info *) info;
// 	struct timeval	time;
// 	if (inf->philo->id_philo % 2 == 0)
// 		sleep(2);
// 	gettimeofday(&time, NULL);
// 	// while (check_philo(inf) == 0 && check_nbr_eat(inf) == 0)
// 	// {

// 	// }
// 	// return (NULL);
// 	print_action("is sleping", inf, time.tv_sec + (time.tv_usec / 1000000));
// 	return (info);
// }

// void	*checker(void *info)
// {
// 	t_Gen_info *inf = (t_Gen_info *) info;

// 	while (1)
// 	{
// 		if (check_philo(inf) != 0 || check_nbr_eat(inf) != 0)
// 			break ;
// 	}
// 	return (info);
// }

// int	create_thread(t_philo *philo)
// {
// 	int	i;
// 	int	id_thread;
// 	// pthread_t	gene;

// 	i = 0;
// 	id_thread = 0;
// 	// if (pthread_create(&gene, NULL, checker, (void *) info) != 0)
// 	// 	return (-1);
// 	while (i < info->nop)
// 	{
// 		if (pthread_create(&info->philo[i].thread, NULL, routine_function, (void*) info) != 0)
// 			return (-1);
// 		i++;
// 	}
// 	// if (pthread_join(gene, NULL) != 0)
// 	// 	return (-1);
// 	i = 0;
// 	while (i < info->nop)
// 	{
// 		if (pthread_join(info->philo[i].thread, NULL) != 0)
// 			return (-1);
// 	}
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_philo		*philo;

	if (ac != 5 && ac != 6)
		print_error(NULL, "Error: invalid arguments number");
	// info = (t_Gen_info *) malloc (sizeof(t_Gen_info));
	// if (info == NULL)
	// 	print_error(NULL, "Error: Failed to allocate memory");
	if (check_args(ac, av) == -1)
		print_error(NULL, "Error: invalid arguments");
	philo = init_struct(ac, av);
	if (!philo)
		print_error(philo, "Error: invalid arguments");
	printf("%d\n", philo[0].id_philo);
	printf("%d\n", philo[1].id_philo);
	printf("%d\n", philo[2].id_philo);
	printf("%d\n", philo[3].id_philo);
	// create_thread(philo);
}
