/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:48:44 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/17 16:01:35 by cravegli         ###   ########.fr       */
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
		philo->mutex_right = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo->mutex_right)
			ft_error("mutex  error");
		if (pthread_mutex_init(philo->mutex_right, NULL))
			ft_error("mutex  error");
	}
	else if (philo->id != 0)
		philo->mutex_right = philos[0]->mutex_left;
	if (philo->id != 0)
		philo->mutex_left = philos[philo->id - 1]->mutex_right;
	else if (info->num_philo != 1)
	{
		philo->mutex_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo->mutex_left)
			ft_error("mutex  error");
		if (pthread_mutex_init(philo->mutex_left, NULL))
			ft_error("mutex  error");
	}
}

void	ft_start_philo(t_philo *philo, t_info *info)
{
	philo->die = 0;
	philo->stop = 0;
	philo->number_eat = 0;
	philo->last_meat = info->time_zero;
	philo->number_eat_total = info->number_eat;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_think = info->time_to_think;
	if (pthread_create(&philo->thread, NULL, ft_routine, philo))
		ft_error("thread error");
}

void	ft_init_philo(t_info *info)
{
	int				i;
	t_philo			**philos;

	philos = (t_philo **)malloc(sizeof(t_philo *) + info->num_philo + 1);
	i = 0;
	while (i < info->num_philo)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		philos[i]->action = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philos[i]->action, NULL))
			ft_error("mutex  error");
		philos[i]->philos = philos;
		philos[i]->id = i;
		ft_give_forks(philos[i], philos, info);
		philos[i]->time_zero = info->time_zero;
		ft_start_philo(philos[i], info);
		i++;
	}
	info->philos = philos;
}
