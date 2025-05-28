/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:31:57 by achantra          #+#    #+#             */
/*   Updated: 2025/05/24 15:38:09 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"

void test_error(int item, char *error){
    if (item < 0){
        perror(error);
        exit(EXIT_FAILURE);
    }
}

void init_timer(int sec, int usec, struct timeval *timer){
        timer->tv_sec = sec;
        timer->tv_usec = usec;
}
