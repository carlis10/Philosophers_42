/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:37:31 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/24 17:41:45 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_test(t_info *info)
{
	int		i;

	i = 0;
	while (info->philos[i]->die == 0)
	{
		i++;
		if (i == info->num_philo)
			i = 0;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		ft_init_info(&info, argv, argc);
		ft_init_philo(&info);
		ft_test(&info);
		ft_stop_philos(info.philos);
	}
	return (0);
}
