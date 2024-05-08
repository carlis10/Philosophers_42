/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:38:15 by cravegli          #+#    #+#             */
/*   Updated: 2024/05/08 16:31:54 by cravegli         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		live;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*action;
	struct s_philo	**philos;
	int				id;
	long long		last_meat;
	long long		time_zero;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				number_eat_total;
	int				number_eat;
	int				die;
	int				stop;

}				t_philo;

typedef struct s_info
{
	int			num_philo;
	long long	time_zero;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_think;
	int			time_to_sleep;
	int			number_eat;
	t_philo		**philos;
}				t_info;

long long	ft_get_time(void);
long long	ft_process(long long time, long long time_zero);
void		*ft_routine(void *philo_void);
void		ft_error(char *str);
void		ft_init_info(t_info *info, char **argv, int argc);
void		ft_init_philo(t_info *info);
int			ft_atoi(const char *str);
int			ft_isnum(char *str);
int			ft_check_args(char **argv, int argc);
void		ft_stop_philos(t_philo **philos);
void		ft_delete_philos(t_philo **philos);

#endif