/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:04:20 by cravegli          #+#    #+#             */
/*   Updated: 2024/04/16 18:01:41 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	s;

	r = 0;
	s = 1;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r *= 10;
		r += str[i] - '0';
		i++;
	}
	r *= s;
	return (r);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] > 47 && str[i] < 58))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_args(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (-1);
		i++;
	}
	return (0);
}
