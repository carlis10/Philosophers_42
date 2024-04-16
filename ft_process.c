/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:36:27 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/16 18:39:24 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stop_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_join(philos[i]->thread, NULL);
		pthread_join(philos[i]->live, NULL);
		pthread_mutex_destroy(&philos[i]->mutex_right);
		free(philos[i]);
		i++;
	}
	free(philos);
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_process(long long time)
{
	long long	t;
	long long	start;

	t = ft_get_time();
	start = t;
	while ((t - start) < time)
		t = ft_get_time();
}
