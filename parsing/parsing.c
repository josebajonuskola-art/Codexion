/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:05:14 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/27 20:39:32 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../codexion.h"

// This function verifies that the received string contains only
// numeric characters and does not begin with a '+' or '-' sign.
//
// The 'argv' pointer references the string to validate.
int	check_num_format(char *argv)
{
	int	j;

	j = 0;
	if((argv[0] == '-') || (argv[0] == '+'))
	{
		printf("ERROR: Config numbers must be always without '-' or '+' signs.\n");
		usage_info_printer();
		return(1);
	}
	while(argv[j])
	{
		if(argv[j] < '0' || argv[j] > '9')
		{
			printf("ERROR: This parameter must be filled with numbers.\n");
			usage_info_printer();
			return(1);
		}
		j++;
	}
	return(0);
}

// This function verifies that the received numeric string
// represents a value within the range of an integer.
//
// The 'argv' pointer references the string containing the
// numeric value to validate
int	max_int_checker(char *argv)
{
	int	atoi_number;
	char	*supposed_real_number;

	atoi_number = atoi(argv);
	supposed_real_number = ft_itoa(atoi_number);
	if(strcmp(argv, supposed_real_number) != 0)
	{
		printf("ERROR: At least a number is outside the int limits.\n");
		free(supposed_real_number);
		return(1);
	}
	free(supposed_real_number);
	return(0);

}

// This function validates the command-line arguments before the
// configuration is created. It verifies that the numeric arguments
// have a valid format, do not exceed the maximum integer value, and
// that the selected scheduler is valid.
//
// The 'argv' parameter is an array of strings containing the
// command-line arguments to validate.
int	check_values(char **argv)
{
	int	i;

	i = 1;
	if(strcmp(argv[1], "1") == 0)
	{
		printf("ERROR: The program should have more than one coder.\n");
		return(1);
	}
	while(i < 8)
	{
		if(check_num_format(argv[i]) == 1)
			return(1);
		if(max_int_checker(argv[i]) ==  1)
			return(1);
		i++;
	}
        if(strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
        {
                printf("ERROR: Invalid schedule.\n");
                usage_info_printer();
                return(1);
        }
        return (0);
}

// This function creates and initializes a configuration structure
// using the command-line arguments provided to the program.
//
// The 'argv' parameter is an array of strings containing the
// command-line arguments used to initialize the configuration.
t_config	*config_creator(char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if(!config)
		return(NULL);
	config->number_of_coders = atoi(argv[1]);
	config->time_to_burnout = atoi(argv[2]);
	config->time_to_compile = atoi(argv[3]);
	config->time_to_debug = atoi(argv[4]);
	config->time_to_refactor = atoi(argv[5]);
	config->number_of_compiles_requiered = atoi(argv[6]);
	config->dongle_cooldown = atoi(argv[7]);
	if(strcmp(argv[8], "fifo") == 0)
		config->scheduler = FIFO;
	if(strcmp(argv[8], "edf") == 0)
		config->scheduler = EDF;
	return (config);
}
