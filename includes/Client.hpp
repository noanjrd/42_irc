/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2025/11/27 15:28:33 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

class Client
{
private:
	std::string nickname;
	std::string username;
	int id;
    int authenticated;

public:
	Client();
	~Client();
};