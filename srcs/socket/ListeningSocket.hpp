/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:49:40 by achantra          #+#    #+#             */
/*   Updated: 2025/05/15 13:13:15 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LISTENINGSOCKET_HPP
# define LISTENINGSOCKET_HPP

# include "BindingSocket.hpp"

class ListeningSocket: public BindingSocket{
    private:
        int _backlog;
        int _listening;
    public :
        // Constructor & Destructor
        ListeningSocket(void);
        ListeningSocket(int domain, int service, int protocol,
            int port, u_long interface, int backlog);
        ~ListeningSocket();
        ListeningSocket(const ListeningSocket& s);
        ListeningSocket& operator=(const ListeningSocket& s);
        
        //Getter
        int get_backlog() const;
        int get_listening() const;
    };      

#endif