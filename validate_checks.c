/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_positive(int argc, char **argv)
{
	int	i;
	int	result;

	i = 1;
	while (i < argc)
	{
		result = atoi(argv[i]);
		if (result < 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_digit(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
