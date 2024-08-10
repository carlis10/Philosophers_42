/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:48:44 by cravegli          #+#    #+#             */
/*   Updated: 2024/08/10 15:23:54 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->action = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->action)
		ft_error("malloc error, mutex_action");
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->fork)
		ft_error("malloc error, mutex_fork");
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&info->action[i], NULL) == -1)
			ft_error("init mutex error, mutex_action");
		if (pthread_mutex_init(&info->fork[i], NULL) == -1)
			ft_error("init mutex error, mutex_action");
		i++;
	}
}

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
	else
		info->number_eat = -1;
	if (info->num_philo > 0)
		ft_create_mutex(info);
	info->time_zero = ft_get_time();
}

t_philo	ft_start_philo(t_philo philo, t_info *info, int id)
{
	philo.action = &info->action[id];
	philo.num_philos = info->num_philo;
	philo.id = id;
	philo.mutex_left = &info->fork[id];
	philo.time_zero = info->time_zero;
	philo.die = 0;
	philo.stop = 0;
	philo.number_eat = 0;
	philo.last_meat = info->time_zero;
	philo.number_eat_total = info->number_eat;
	philo.time_to_die = info->time_to_die;
	philo.time_to_eat = info->time_to_eat;
	philo.time_to_sleep = info->time_to_sleep;
	philo.time_to_think = info->time_to_think;
	return (philo);
}

void	ft_init_philo(t_info *info)
{
	int				i;
	t_philo			*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	i = 0;
	while (i < info->num_philo)
	{
		philo[i] = ft_start_philo(philo[i], info, i);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		philo[i].mutex_right = philo[(i + 1) % info->num_philo].mutex_left;
		if (pthread_create(&philo[i].thread, NULL, ft_routine, &philo[i]) == -1)
			ft_error("thread error");
		i++;
	}
	info->philos = philo;
}
