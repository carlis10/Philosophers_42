/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:37 by cravegli          #+#    #+#             */
/*   Updated: 2024/05/08 17:49:49 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_action(t_philo *philo, char *action, char *color, long long time)
{
	pthread_mutex_lock(philo->action);
	if (philo->die != 1 && philo->stop != 1)
		printf("%s%lli, %i is %s...\n", color, time, (philo->id + 1), action);
	if (action[0] == 'd')
	{
		philo->die = 1;
		ft_stop_philos(philo->philos);
	}
	pthread_mutex_unlock(philo->action);
}

void	*ft_calc_die(void *philo_void)
{
	long long	t;
	t_philo		*philo;

	t = ft_get_time();
	philo = (t_philo *)philo_void;
	while ((t - philo->last_meat) < philo->time_to_die && philo->stop == 0)
		t = ft_get_time();
	t -= philo->time_zero;
	if (philo->stop == 0)
		ft_action(philo, "die", "\x1B[31m", t);
	return (NULL);
}

void	ft_take_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
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

void	*ft_routine(void *philo_void)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)philo_void;
	pthread_create(&philo->live, NULL, ft_calc_die, philo);
	while (philo->die == 0 && philo->stop == 0 \
			&& philo->number_eat != philo->number_eat_total)
	{
		ft_take_forks(philo);
		philo->last_meat = ft_get_time();
		time = philo->last_meat - philo->time_zero;
		if (philo->number_eat_total != -1)
			philo->number_eat ++;
		ft_action(philo, "eating", "\x1B[33m", time);
		time = ft_process(philo->time_to_eat, philo->time_zero);
		pthread_mutex_unlock(philo->mutex_left);
		pthread_mutex_unlock(philo->mutex_right);
		ft_action(philo, "sleeping", "\x1B[34m", time);
		time = ft_process(philo->time_to_sleep, philo->time_zero);
		ft_action(philo, "thinking", "\x1B[32m", time);
	}
	philo->stop = 1;
	pthread_join(philo->live, NULL);
	return (NULL);
}
