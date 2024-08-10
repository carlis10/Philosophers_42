/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:36:27 by cravegli          #+#    #+#             */
/*   Updated: 2024/08/10 15:26:08 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stop_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < philos[0]->num_philos)
	{
		philos[i]->stop = 1;
		i++;
	}
}

void	ft_delete_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->action[i]);
		i++;
	}
	free(info->philos);
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	ft_process(long long time, long long time_zero)
{
	long long	t;
	long long	start;

	t = ft_get_time();
	start = t;
	while ((t - start) < time)
		t = ft_get_time();
	return (t - time_zero);
}
