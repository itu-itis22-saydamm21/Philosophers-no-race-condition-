/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaydam <msaydam@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:24:38 by msaydam           #+#    #+#             */
/*   Updated: 2023/04/27 13:24:38 by msaydam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ========================================================================= //
//                                   Library                                 //
// ========================================================================= //

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

# define INT_MAX 2147483647
# define SLEEP 1
# define EAT 2
# define THINK 3
# define LOCK_FORK 4
# define DIE 5

// ========================================================================= //
//                                 Define Color                              //
// ========================================================================= //

# define PINK "\033[95m"
# define END "\033[0m"
# define YELLOW "\033[93m"
# define RED "\033[91m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"

// ========================================================================= //
//                                 Structure                                 //
// ========================================================================= //

typedef struct s_data
{
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				max_eat;
	int				die;
	long			time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	check_max_eat;
	pthread_mutex_t	check_last_eat;
	pthread_mutex_t	check_die;
}	t_data;

typedef struct s_philo
{
	struct s_data	*data_ptr;
	int				id;
	int				nb_meal;
	long			last_eat;
	pthread_t		philo_thread;
}	t_philo;

// ========================================================================= //
//                               Initialization                              //
// ========================================================================= //

// Check if all parameters are only int, and if argc is valid
int		ft_check_arg(int argc, char **argv);
// Check if all parameters are not or less 0
int		ft_check_input_value(int argc, char **argv, t_data *data);
// If input is valid, fill the data structure with value
int		ft_fill_data_struct(int argc, char **argv, t_data *data);
// Init a mutex array called fork, in data strucutre, and other secondary mutex
int		ft_init_fork_and_mutex(t_data *data);
// Create an array of t_philo, one per philo, with info about eatch philo inside
t_philo	*ft_fill_philo_struct(t_data *data);
// Creat a thread per philo, with ft_loop in function, and t_philo in params
int		ft_init_thread(t_data *data, t_philo *philo);

// ========================================================================= //
//                                About routine                              //
// ========================================================================= //

// Principal function to synchronize the launch of all philo
void	*ft_loop(t_philo *philo);
// Function to call routine function
void	ft_eat_and_more(t_philo *philo);
// Check if all the philosophers have not eaten more times than the max
int		ft_check_max_eat(t_philo *philo);
// Function to eat
void	ft_eat(t_philo *philo);
// Function to sleep
void	ft_sleep(t_philo *philo, long long tts);
// Function to think
void	ft_think(t_philo *data);
//  Function to tcheck and set a variable if the time_to_eat is to exceed
void	ft_death(t_data *data, t_philo *philo);
// Function to print message
void	ft_write(t_philo *philo, int what_message);
// Function to lock fork on the left and right side
void	ft_lock_fork(t_philo *philo);
// Function ton unlock fork
void	ft_unlock_fork(t_philo *philo);
// Function to check if a philo is die
int		ft_check_die(t_philo *philo);
// Function to usleep without sleep message, 50ms
void	ft_usleep(t_philo *philo, long long time);

// ========================================================================= //
//                                    Utils                                  //
// ========================================================================= //

// Convert ascii to int
int		ft_atoi(const char *str);
// Get time in ms
long	ft_get_time(void);
// Function to destroy and free all memory allocated by mutex
void	ft_destroy(t_data *data);

#endif