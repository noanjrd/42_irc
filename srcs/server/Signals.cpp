/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:24:39 by naankour          #+#    #+#             */
/*   Updated: 2026/02/25 12:14:33 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"
 
volatile sig_atomic_t g_running = 1;

void handleSignal(int sig)
{
	(void)sig;
	g_running = 0;
	std::cout << "\nSignal received, stopping the server..." << std::endl;
}