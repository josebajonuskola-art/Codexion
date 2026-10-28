/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:32:18 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/24 18:34:34 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function initializes the time of the coder for getting burnout, before
// the first compilation.
/* void	run_coders_first_time(t_simulation *sim, t_coder *coder)
{
	long long actual_time;

	actual_time = get_time_ms();
	sim->coders->last_compile = actual_time;
} */

//change the name of the func
void	run_coders(t_simulation *sim, t_coder *coder)
{
	int	i;

	i = 0;
	coder_request(sim, coder);
/* 	while (sim->is_finished == 0)
	{
		request_verify(sim, coder);
		if (coder_process(coder->sim, coder) == 1)
			continue ;
		i++;
	} */
	while (coder->n_compiles_done < sim->config->number_of_compiles_requiered)
	{
		request_verify(sim, coder);
		if (coder_process(coder->sim, coder) == 1)
			continue ;
		i++;
	}
	printf("Run coders terminado: coder %d\n", coder->n_coder);
}

void	*init_coders_threads(void *value)
{
	t_coder	*coder;

	coder = (t_coder *)value;
	run_coders(coder->sim, coder);
	return (NULL);
}
