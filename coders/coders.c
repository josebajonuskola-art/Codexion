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
	sim->coders->time_in_process = actual_time;
} */

//change the name of the func
void	run_coders(t_simulation *sim, t_coder *coder)
{
	int i;

	i = 0;
	coder_request(sim, coder);

	//run_coders_first_time(sim, coder);
	while (/*sim->is_finished == 0*/i < 5)
	{
		request_verify(sim, coder);
		//coder = choose_coder(sim);
		if(coder_process(coder->sim, coder) == 1)
			continue;
		i++;
	}
}

void	*init_coders_threads(void *value)
{
	t_coder *coder;

	coder = (t_coder *)value;
	run_coders(coder->sim, coder);
	return NULL;
}
