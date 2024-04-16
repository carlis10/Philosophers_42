/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:37 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/16 18:44:30 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calc_die(void *philo_void)
{
	long long	t;
	t_philo		*philo;

	t = ft_get_time();
	philo = (t_philo *)philo_void;
	while ((t - philo->last_meat) < philo->time_to_die)
		t = ft_get_time();
	philo->die = 1;
	printf("%i Died...", (philo->id + 1));
	ft_stop_philos(philo->philos);
	return (NULL);
}

void	*ft_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	pthread_create(&philo->live, NULL, ft_calc_die, philo);
	while (philo->die == 0)
	{
		pthread_mutex_lock(&philo->mutex_right);
		pthread_mutex_lock(&philo->mutex_left);
		philo->last_meat = ft_get_time();
		printf("%i is eating...\n", (philo->id + 1));
		ft_process(philo->time_to_eat);
		pthread_mutex_unlock(&philo->mutex_right);
		pthread_mutex_unlock(&philo->mutex_left);
		printf("%i is sleeping...\n", (philo->id + 1));
		ft_process(philo->time_to_sleep);
		printf("%i is thinking...\n", (philo->id + 1));
	}
	return (NULL);
}
