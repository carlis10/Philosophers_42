/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:38:15 by cravegli          #+#    #+#             */
/*   Updated: 2024/09/12 13:02:59 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				number_eat;
	int				start;
	int				over;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*action;
}				t_info;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		live;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*action;
	int				num_philos;
	int				id;
	t_info			*info;
	long long		last_meat;
	long long		time_zero;
	int				number_eat;
	int				die;

}				t_philo;

long long	ft_get_time(void);
void		ft_process(long long time);
void		*ft_routine(void *philo_void);
void		ft_error(char *str);
void		ft_init_info(t_info *info, char **argv, int argc);
void		ft_init_philo(t_info *info);
int			ft_atoi(const char *str);
int			ft_isnum(char *str);
int			ft_check_args(char **argv, int argc);
void		ft_delete_philos(t_philo *iphilo);
void		ft_action(t_philo *philo, char *action, char *color);
void		ft_someone_died(t_philo *philo);

#endif