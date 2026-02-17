/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:24:39 by naankour          #+#    #+#             */
/*   Updated: 2026/02/17 16:19:16 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

//SIGINT Ctrl+C
//SIGTERM kill pid
//SIGPIPE ecriture sur un socket ferme 
 
volatile sig_atomic_t g_running = 1;

void handleSignal(int sig)
{
	(void)sig;
	g_running = 0;
	std::cout << "\nSignal reçu, arrêt du serveur..." << std::endl;
}