/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2025/12/02 15:00:19 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Chanel
{
private:
	std::string name;
	std::string topic;
	// int user_limit;
	std::string password;
	// int id;
	// Client tabclient[];

public:
	Chanel();
	Chanel(std::string name);
	~Chanel();
	std::string& getName();
};