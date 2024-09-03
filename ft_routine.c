/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:37 by cravegli          #+#    #+#             */
/*   Updated: 2024/09/03 14:48:27 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_action(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(philo->action);
	if (philo->info->over != 1)
		printf("%s%lli, %i is %s...\n", color, ft_get_time() - philo->time_zero,
			(philo->id + 1), action);
	pthread_mutex_unlock(philo->action);
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id & 1)
	{
		pthread_mutex_lock(philo->mutex_left);
		pthread_mutex_lock(philo->mutex_right);
	}
	else
	{
		pthread_mutex_lock(philo->mutex_right);
		pthread_mutex_lock(philo->mutex_left);
	}
}

void	ft_someone_died(t_philo *philo)
{
	ft_action(philo, "death", "\x1B[31m");
	philo->info->over = 1;
}

void	ft_wait(t_philo *philo)
{
	while (philo->info->start != 1)
		continue ;
	philo->time_zero = ft_get_time();
	philo->last_meat = philo->time_zero;
	if (philo->id & 1)
		ft_process(philo->info->time_to_eat * 0.9 + 1);
}

void	*ft_routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo *)philo_void;
	ft_wait(philo);
	while (philo->info->over != 1)
	{
		ft_take_forks(philo);
		philo->last_meat = ft_get_time();
		ft_action(philo, "eating", "\x1B[33m");
		ft_process(philo->info->time_to_eat);
		philo->number_eat ++;
		pthread_mutex_unlock(philo->mutex_right);
		pthread_mutex_unlock(philo->mutex_left);
		ft_action(philo, "sleeping", "\x1B[34m");
		ft_process(philo->info->time_to_sleep);
		ft_action(philo, "thinking", "\x1B[32m");
	}
	return (NULL);
}
