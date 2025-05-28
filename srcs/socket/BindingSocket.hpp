/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:45:17 by achantra          #+#    #+#             */
/*   Updated: 2025/05/16 11:36:59 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGSOCKET_HPP
# define BINDINGSOCKET_HPP

# include "Socket.hpp"

class BindingSocket: public Socket{
    protected:
        int _binding;

        // Constructor 
        BindingSocket(void);
        BindingSocket(int domain, int service, int protocol,
            int port, u_long interface);
        BindingSocket(const BindingSocket& s);
        BindingSocket& operator=(const BindingSocket& s);
        
     public :
        //Destructor
        ~BindingSocket();
    };      

#endif