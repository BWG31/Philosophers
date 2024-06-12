/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:16:51 by bgolding          #+#    #+#             */
/*   Updated: 2024/02/20 16:11:13 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monitor	monitor;

	if (invalid_input(argc, argv))
		return (1);
	if (init_simulation(&monitor, argc, argv))
		return (terminate_simulation(&monitor));
	if (run_simulation(&monitor))
		return (terminate_simulation(&monitor));
	print_simulation_report(&monitor);
	terminate_simulation(&monitor);
	return (0);
}

void	print_simulation_report(t_monitor *monitor)
{
	size_t			i;
	static char		*color[] = {RED, GRN, YEL, CYN, MAG, BLU};

	printf("= = = = = = = = = = = = = = = = = = = = =\n");
	printf("=	END OF SIMULATION REPORT	=\n");
	printf("= = = = = = = = = = = = = = = = = = = = =\n");
	printf("Philo ID	Meal count	Dead?\n");
	i = 0;
	while (i < monitor->seats)
	{
		printf("%s", color[(monitor->philo[i].id - 1) % 6]);
		printf("%zu		%zu		", monitor->philo[i].id, \
									monitor->philo[i].meal_count.value);
		if (monitor->philo[i].state.value == DEAD)
			printf("YES\n"RST);
		else
			printf("NO\n"RST);
		i++;
	}
}
