/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:15:41 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/22 10:47:19 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (invalid_input(argc, argv))
		return (EXIT_FAILURE);
	if (init_simulation(&philo, argc, argv))
		return (end_simulation(&philo), EXIT_FAILURE);
	if (run_simulation(&philo))
		return (end_simulation(&philo), EXIT_FAILURE);
	return (end_simulation(&philo), EXIT_SUCCESS);
}
