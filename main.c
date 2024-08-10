/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:37:31 by cravegli          #+#    #+#             */
/*   Updated: 2024/08/10 12:06:44 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		printf("%p\n", philos[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		ft_init_info(&info, argv, argc);
		ft_init_philo(&info);
		ft_delete_philos(&info);
	}
	return (0);
}
