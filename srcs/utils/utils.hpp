/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:38:23 by achantra          #+#    #+#             */
/*   Updated: 2025/05/24 15:38:18 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include <cstdlib>
# include <stdio.h>
# include <unistd.h>



void    test_error(int item, char *error);
void    init_timer(int sec, int usec, struct timeval *timer);


#endif