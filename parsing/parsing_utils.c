/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:34:59 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/16 13:49:05 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function prints the expected command-line format for
// running the program.
void	usage_info_printer(void)
{
	printf("The output should look like the next one:\n");
	printf("codexion.c 1 23 40 42 6 1 7 fifo\n");
}

// This function prints an error message indicating that the
// first six numeric parameters must be greater than zero.
void	bigger_than_0_message(void)
{
	printf("ERROR: Numbers in the first 6 parameters");
	printf(" must be greater than '0'\n.");
}

// This function verifies that all required configuration values
// are greater than zero.
//
// The 'config' pointer references the configuration structure
// whose values are validated.
int	non_value_checker(t_config *config)
{
	int	error;

	error = 0;
	if(config->number_of_coders <= 0)
		error = 1;
	if(config->number_of_compiles_requiered <= 0)
		error = 1;
	if(config->time_to_burnout <= 0)
		error = 1;
	if(config->time_to_compile <= 0)
		error = 1;
	if(config->time_to_debug <= 0)
		error = 1;
	if(config->time_to_refactor <= 0)
		error = 1;
	if(error == 1)
	{
		bigger_than_0_message();
		usage_info_printer();
		return(1);
	}
	return(0);
}
