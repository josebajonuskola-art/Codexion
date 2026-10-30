/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:46:26 by juskola-          #+#    #+#             */
/*   Updated: 2026/07/28 17:21:28 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// structs and enums
typedef enum e_scheduler_type t_scheduler_type;
typedef struct s_config t_config;
typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;
typedef struct s_simulation t_simulation;
typedef struct s_monitor t_monitor;

// scheduler policies
typedef enum e_scheduler_type
{
	FIFO,
	EDF

} t_scheduler_type;

// typedef struct
typedef struct s_request
{
	t_coder *coder;
	int arrival_number;
	long long time_remaining;

} t_request;

typedef struct s_heap
{
	t_request *requests;
	int size;
	int capacity;
	pthread_mutex_t heap_mutex;
	pthread_cond_t heap_cond;
	pthread_t heap_sorter_thread;
} t_heap;

// configuration
typedef struct s_config
{
	long long time_to_burnout;
	long long time_to_compile;
	long long time_to_debug;
	long long time_to_refactor;
	long long dongle_cooldown;

	int number_of_coders;
	int number_of_compiles_requiered;

	t_scheduler_type scheduler;

} t_config;

// the struct used for coders
typedef struct s_coder
{
	int n_coder;
	int n_compiles_done;
	int actual_step;
	int can_process;

	long long last_compile;

	t_dongle *right_dongle;
	t_dongle *left_dongle;

	pthread_mutex_t coder_mutex;

	pthread_t coder_thread;

	t_simulation *sim;

} t_coder;

// the struct used for the dongles
//  Still have to check if the t_coder *coder data is used in the program or not,
//  if the data is not used, it must be deleted.
typedef struct s_dongle
{
	int n_dongle;
	int is_connected;
	int is_chilled;

	long long cooldown_starting_time;

	t_coder *user;

	pthread_mutex_t dongle_mutex;
} t_dongle;

typedef struct s_heap_sorter
{
	pthread_t heap_sorter_thread;
} t_heap_sorter;

// the struct used fot the simulation
typedef struct s_simulation
{
	int is_finished;
	int	n_available_coders;
	int n_not_available_coders;
	long long start_time;

	t_coder *coders;

	t_dongle *dongles;

	t_config *config;

	t_heap *heap;

	int arrival_counter;

	// tengo que crear un struct que sea el scheduler. que no se me
	// olvide inicializarlo en simulation/init_simulation.c

	t_monitor *monitor;

	t_heap_sorter *heap_sorter;

	t_request	*available_coders;
	t_request *not_available_coders;

	pthread_mutex_t print_mutex;
	pthread_mutex_t simulation_mutex;

} t_simulation;

// the struct used for the monitor
typedef struct s_monitor
{
	pthread_t monitor_thread;
} t_monitor;



// used functions
int check_burnout(t_simulation *sim, int coder);
int check_compiles_done(t_simulation *sim);
int check_values(char **argv);
int check_num_format(char *argv);
int has_better_neighbours(t_simulation *sim, t_coder *coder);
int non_value_checker(t_config *config);
int is_heap_top(t_simulation *sim, t_coder *coder);

int init_coders(t_simulation *sim);
int init_dongles(t_simulation *sim);
int init_heap(t_simulation *sim);
int run_simulation(t_simulation *simulation);
int has_to_heapify(t_simulation *sim,
				   t_request *request_top, t_request *request_bottom);
int start_to_compile(t_simulation *sim, t_coder *coder);
int start_to_debug(t_simulation *sim, t_coder *coder);
int start_to_refactor(t_simulation *sim, t_coder *coder);
int coder_process(t_simulation *sim, t_coder *coder);
int usable_dongle(t_simulation *sim, t_dongle *dongle);
int usable_dongles(t_simulation *sim, t_coder *coder);

long long init_threads(t_simulation *simulation);
long long get_smaller_time(t_simulation *sim, t_coder *coder);
long long get_time_ms(void);

char *ft_strdup(const char *s1);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_itoa(int n);

size_t ft_strlcpy(char *dest, const char *src, size_t size);
size_t ft_strlen(const char *str);

void available_or_not_scheduler(t_simulation *sim, t_request coder_request);
void wake_up_coders(t_simulation *sim);
void usage_info_printer(void);
void bigger_than_0_message(void);
void coder_runner_and_schedule_reseter(t_simulation *sim);
void heap_adder(t_simulation *sim, t_request request);
void heap_adder_fifo(t_simulation *sim, t_request request);

void heap_push(t_simulation *sim, t_request request);
void heap_add_fifo(t_simulation *sim, t_request request);

void heapify_up(t_simulation *sim, t_heap *heap);
void heapify_down(t_simulation *sim);
void swap_requests(t_simulation *sim);
void swapper(t_request *request_top, t_request *request_bottom);
void init_mutex_destroy(int selector, int i, t_simulation *sim);
void *init_monitoring(void *value);
void *init_coders_threads(void *value);
void *init_heap_thread(void *value);
void join_threads(t_simulation *sim);
void sim_garbage_collector(t_simulation *simulation);
void request_verify(t_simulation *sim, t_coder *coder);
void run_coders(t_simulation *sim, t_coder *coder);
void coder_request(t_simulation *sim, t_coder *coder);
void check_and_grab_dongles(t_simulation *sim);
void print_take_dongles(t_simulation *sim, t_coder *coder);
void print_heap(t_heap *heap);
void use_dongles(t_coder *coder);
void *ft_memset(void *str, int c, size_t n);

t_config *config_creator(char **argv);

t_simulation *sim_creator(t_config *config);

t_coder *choose_coder(t_simulation *sim);
t_coder *choose_coder_fifo(t_simulation *sim);
t_coder *choose_coder_edf(t_simulation *sim);
t_coder *find_left_neighbour(t_simulation *sim, t_coder *coder);
t_coder *find_right_neighbour(t_simulation *sim, t_coder *coder);


t_request *find_request(t_simulation *sim, t_coder *coder);
t_request heap_pop(t_simulation *sim);

#endif
