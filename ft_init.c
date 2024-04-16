/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:48:44 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/16 18:52:38 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_info(t_info *info, char **argv, int argc)
{
	if (!ft_check_args(argv, argc))
		ft_error("Not valid args");
	info->num_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_eat = ft_atoi(argv[5]);
	info->time_zero = ft_get_time();
}

void	ft_give_forks(t_philo *philo, t_philo **philos, t_info *info)
{
	if (philo->id != (info->num_philo - 1))
	{
		if (pthread_mutex_init(&philo->mutex_right, NULL))
			ft_error("mutex  error");
	}
	else if (philo->id != 0)
		philo->mutex_right = philos[0]->mutex_left;
	if (philo->id != 0)
		philo->mutex_left = philos[philo->id - 1]->mutex_right;
	else if (philo->id != 0)
	{
		if (pthread_mutex_init(&philo->mutex_left, NULL))
			ft_error("mutex  error");
	}
}

void	ft_init_philo(t_info *info)
{
	int		i;
	t_philo	**philos;

	philos = (t_philo **)malloc(sizeof(t_philo *) + info->num_philo + 1);
	i = 0;
	while (i < info->num_philo)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		philos[i]->id = i;
		philos[i]->die = 0;
		philos[i]->last_meat = info->time_zero;
		philos[i]->number_eat = 0;
		philos[i]->number_eat_total = info->number_eat;
		philos[i]->time_to_die = info->time_to_die;
		philos[i]->time_to_eat = info->time_to_eat;
		philos[i]->time_to_sleep = info->time_to_sleep;
		philos[i]->time_to_think = info->time_to_think;
		ft_give_forks(philos[i], philos, info);
		philos[i]->philos = philos;
		if (pthread_create(&philos[i]->thread, NULL, ft_routine, philos[i]))
			ft_error("thread error");
		i++;
	}
	info->philos = philos;
}
