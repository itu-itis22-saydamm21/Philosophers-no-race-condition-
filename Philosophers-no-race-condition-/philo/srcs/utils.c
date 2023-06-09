/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaydam <msaydam@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:25:14 by msaydam           #+#    #+#             */
/*   Updated: 2023/04/27 13:25:14 by msaydam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

int	ft_check_max_eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data_ptr->check_max_eat);
	if (philo->data_ptr->max_eat == -1)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
		return (0);
	}
	while (i < philo->data_ptr->nb_philo)
	{
		if (philo[i].nb_meal < philo->data_ptr->max_eat)
		{
			pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
	return (1);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	i = 0;
	free(data->fork);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->check_max_eat);
	pthread_mutex_destroy(&data->check_last_eat);
	pthread_mutex_destroy(&data->check_die);
}

int	ft_check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->check_die);
	if (!philo->data_ptr->die)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_die);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->check_die);
	return (1);
}

void	ft_usleep(t_philo *philo, long long time)
{
	long long	start_time;

	start_time = ft_get_time();
	while (((ft_get_time() - start_time) * 1000) < time
		&& !ft_check_die(philo) && !ft_check_max_eat(philo - (philo->id - 1)))
		usleep(50);
}
