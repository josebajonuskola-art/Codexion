/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_choose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 13:03:22 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/24 18:38:34 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	*choose_coder(t_simulation *sim)
{
	t_coder	*coder;

	if (sim->config->scheduler == FIFO)
		coder = choose_coder_fifo(sim);
	else if (sim->config->scheduler == EDF)
		coder = choose_coder_edf(sim);
	return (coder);
}

//This function isn't done yet. just filled to compile
//I've copied the edf version here just to keep forward with the proyect
t_coder	*choose_coder_fifo(t_simulation *sim)
{
	int		i;
	t_coder	*coder;

	i = 0;
	coder = &sim->coders[i];
	while (i < sim->config->number_of_coders)
	{
		if (sim->coders[i].last_compile > coder->last_compile)
			coder = &sim->coders[i];
		i++;
	}
	return (coder);

}

t_coder	*choose_coder_edf(t_simulation *sim)
{
	int		i;
	t_coder	*coder;

	i = 0;
	coder = &sim->coders[i];
	while (i < sim->config->number_of_coders)
	{
		if (sim->coders[i].last_compile > coder->last_compile)
			coder = &sim->coders[i];
		i++;
	}
	return (coder);
}
