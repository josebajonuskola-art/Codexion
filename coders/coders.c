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

void	run_coders(t_simulation *sim, t_coder *coder)
{

	coder_request(sim, coder);
	//while (coder->n_compiles_done < sim->config->number_of_compiles_requiered)
	while (sim->is_finished == 0)
	{
		if (sim->is_finished == 1)
			break;
		request_verify(sim, coder);
		if (sim->is_finished == 1)
			break;
		if (coder_process(coder->sim, coder) == 1)
			continue ;
	}
	printf("Run coders terminado: coder %d\n", coder->n_coder);
}

void	*init_coders_threads(void *value)
{
	t_coder	*coder;

	coder = (t_coder *)value;
	run_coders(coder->sim, coder);
	//printf("Run coders terminado\n");
	//printf("simulation is finished: %d\n", coder->sim->is_finished);
	return (NULL);
}
