/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaydam <msaydam@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:24:57 by msaydam           #+#    #+#             */
/*   Updated: 2023/04/27 13:24:57 by msaydam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(\
		&philo->data_ptr->fork[philo->data_ptr->nb_philo - 1]);
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
		ft_write(philo, LOCK_FORK);
		ft_write(philo, LOCK_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 2]);
		ft_write(philo, LOCK_FORK);
		ft_write(philo, LOCK_FORK);
	}
}

void	ft_unlock_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_unlock(\
		&philo->data_ptr->fork[philo->data_ptr->nb_philo - 1]);
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 2]);
	}
}
