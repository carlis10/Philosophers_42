/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:38:15 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/16 18:34:43 by cravegli         ###   ########.fr       */
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
	int				id;
	pthread_t		thread;
	pthread_t		live;
	pthread_mutex_t	mutex_right;
	pthread_mutex_t	mutex_left;
	long long		last_meat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				number_eat_total;
	int				number_eat;
	int				die;
	struct s_philo	**philos;

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
void		ft_process(long long time);
void		*ft_routine(void *philo_void);
void		ft_error(char *str);
void		ft_init_info(t_info *info, char **argv, int argc);
void		ft_init_philo(t_info *info);
int			ft_atoi(const char *str);
int			ft_isnum(char *str);
int			ft_check_args(char **argv, int argc);
void		ft_stop_philos(t_philo **philos);

#endif