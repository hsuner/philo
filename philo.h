/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:38:03 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/11 16:18:27 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>

# define ARG_ERR "Incompatible argument(s)!\n"
# define PH_COUNT_ERR "Invalid number of philosophers! (0 < ph < 201)\n"
# define RULE_VL "Rule values cannot be lower than 60!\n"

# define FORK_CREATE_ERR "Failed to create forks\n"
# define PHILO_CREATE_ERR "Philosophers could not be created\n"
# define MUTEX_INIT_ERR "Mutex failed to initialize\n"
# define MUTEX_CREATE_ERR "Could not create mutex\n"

# define FORK "\033[0;37m%5d| \033[1;36m%3d. \033[0;35mphilo \
taken a fork (%s)\033[0m 🍴\n"
# define EAT "\033[0;37m%5d| \033[1;36m%3d. \033[0;32mphilo \
is eating.\033[0m            🍝\n"
# define SLEEP "\033[0;37m%5d| \033[1;36m%3d. \033[0;34mphilo \
is sleeping.\033[0m          💤\n"
# define THINK "\033[0;37m%5d| \033[1;36m%3d. \033[0;37mphilo \
is thinking.\033[0m          🤔\n"
# define DIE "\033[0;37m%5d| \033[1;36m%3d. \033[0;31mphilo \
is died!\033[0m              💀\n"

typedef struct s_data
{
	unsigned int		first_call;
	unsigned int		previous_difference;
}		t_data;

typedef struct s_rl
{
	unsigned int		nop; //num_of_philo
	unsigned int		ttd; //time_to_die
	unsigned int		tte; //time_to_eat
	unsigned int		tts; //time_to_sleep
	unsigned char		eat_limit;
}		t_rl;

typedef struct s_mutex
{
	pthread_mutex_t		print_m;
	pthread_mutex_t		ctrl_m;
	pthread_mutex_t		ctrl_2_m;
	pthread_mutex_t		*fork_m;
}		t_mutex;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned char		id;
	unsigned char		l_fork;
	unsigned char		r_fork;
	uint64_t			last_eat;
	unsigned char		num_of_eat;
	struct s_program	*x;
}		t_philo;

typedef struct s_die
{
	pthread_t			die_t;
	pthread_mutex_t		die_m;
	unsigned char		is_die;
	unsigned int		die_time;
}		t_die;

typedef struct s_others
{
	uint64_t			start_time;
	unsigned char		ctrl_eat_limit;
	unsigned char		finished;
}		t_others;

typedef struct s_program
{
	t_rl				rl; //rules
	t_philo				*philo;
	t_mutex				mutex;
	t_die				die;
	t_others			others;
}		t_program;

int			arg_check(char **argv);
int			create_rl(int ac, char **av, t_program *x);
int			alloc_philo(t_program *x);
int			philo_init(t_program *x);
int			run_simulation(t_program *x);

int			free_malloc(t_program *x);
int			init_error_fork(t_program *x, int idx);
int			create_error_fork(t_program *x, int idx);
int			destroy(t_program *x);
int			finish_destroy(t_program *x);

uint64_t	get_time(void);
int			instant_time(t_program *x);
void		impr_usl(u_int64_t time);
int			check_eat(t_program *x);
int			calc_dif(t_data *data, int init_v, \
				int sub_v, int third_v);
int			ft_atoi(char *str);

void		p_fork(t_philo *philo, char *fork);
void		p_eat(t_philo *philo);
void		p_sleep(t_philo *philo);
void		p_think(t_philo *philo, t_data *data);
void		*die(void *tmp_program);
void		*life(void *tmp_philo);

#endif
