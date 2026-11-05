/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:45:30 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/23 17:18:40 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// This is the program's entry point. It receives the command-line
// arguments and performs basic validation, such as checking the
// number of arguments. It is also responsible for initializing the
// simulation.
//
// The 'argc' parameter contains the number of command-line arguments.
// The 'argv' parameter is an array of strings containing the values
// of those arguments.
int	main(int argc, char **argv)
{
	t_config		*config;
	t_simulation	*sim;

	if (argc != 9)
	{
		printf("ERROR: Number of arguments must be 8.\n");
		usage_info_printer();
		return (1);
	}
	if (check_values(argv) == 1)
		return (1);
	config = config_creator(argv);
	if (non_value_checker(config) == 1)
		return (1);
	sim = sim_creator(config);
	run_simulation(sim);
	free(config);
	garbage_collector(sim);
	return (0);
}
