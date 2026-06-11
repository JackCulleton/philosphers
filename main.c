/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jculleto <jculleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:38:48 by jculleto          #+#    #+#             */
/*   Updated: 2026/06/11 17:38:48 by jculleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	int	result;

	if (argc != 5 && argc != 6)
	{
		printf("invalid amount of arguments\n");
		return (1);
	}
	result = validate(argc, argv);
	if (result == 0)
	{
		printf("invalid arguments\n");
		return (1);
	}
	return (0);
}
