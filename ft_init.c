/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:48:44 by cravegli          #+#    #+#             */
/*   Updated: 2024/09/12 14:48:21 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->action = malloc(sizeof(pthread_mutex_t));
	if (!info->action)
		ft_error("malloc error, mutex_action");
	if (pthread_mutex_init(info->action, NULL) == -1)
		ft_error("init mutex error, mutex_action");
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->fork)
		ft_error("malloc error, mutex_fork");
	while (i < info->num_philo)
	{
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
	info->start = 0;
	info->over = 0;
}

t_philo	ft_start_philo(t_philo philo, t_info *info, int id)
{
	philo.action = info->action;
	philo.num_philos = info->num_philo;
	philo.id = id;
	philo.mutex_left = &info->fork[id];
	philo.die = 0;
	philo.number_eat = 0;
	philo.info = info;
	return (philo);
}

void	ft_check_philo(t_philo *philo, t_info *info)
{
	int	i;
	int	count;

	info->start = 1;
	ft_process(1);
	while (info->over != 1)
	{
		i = 0;
		count = 0;
		while (i < info->num_philo)
		{
			if ((ft_get_time() - philo[i].last_meat) > info->time_to_die)
				ft_someone_died(&philo[i]);
			if (philo[i].number_eat >= info->number_eat \
				&& info->number_eat != -1)
				count++;
			if (count == info->num_philo)
				info->over = 1;
			i++;
		}
	}
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
	ft_check_philo(philo, info);
	ft_delete_philos(philo);
}
