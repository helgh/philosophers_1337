/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:50:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/28 05:00:03 by hael-ghd         ###   ########.fr       */
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

int	init_struct(t_philo **philo, int argc, char **argv)
{
	(*philo)->nop = ft_atoi(argv[1]);
	(*philo)->ttd = ft_atoi(argv[2]);
	if ((*philo)->nop == 0 || (*philo)->ttd == 0)
		return (-1);
	(*philo)->tte = ft_atoi(argv[3]);
	(*philo)->tts = ft_atoi(argv[4]);
	if ((*philo)->tte == 0 || (*philo)->tts == 0)
		return (-1);
	if (argc == 6)
	{
		(*philo)->notepme = ft_atoi(argv[5]);
		if ((*philo)->notepme == 0)
			return (-1);
	}
	else
		(*philo)->notepme = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		print_error(NULL, "Error: invalid arguments number");
	philo = (t_philo *) malloc (sizeof(t_philo));
	if (philo == NULL)
		print_error(NULL, "Error: Failed to allocate memory");
	if (check_args(ac, av) == -1 || init_struct(&philo, ac, av) == -1)
		print_error(philo, "Error: invalid arguments");
}
