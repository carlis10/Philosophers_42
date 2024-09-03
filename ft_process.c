/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:36:27 by cravegli          #+#    #+#             */
/*   Updated: 2024/09/03 12:44:07 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_delete_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo->num_philos)
	{
		pthread_mutex_destroy(philo[i].mutex_left);
		i++;
	}
	pthread_mutex_destroy(philo->action);
	free(philo->mutex_left);
	free(philo->action);
	free(philo);
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_process(long long time)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(150);
}
