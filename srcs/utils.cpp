/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:46:49 by njard             #+#    #+#             */
/*   Updated: 2025/12/02 16:54:41 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"

int count_words(std::string s)
{
    int words = 0;
    int i  = 0;
	bool letter = 0;
    while(s[i])
    {
		if (!std::isspace(s[i]) && letter == 0)
		{
			words++;
			letter = 1;
		}
		if (std::isspace(s[i]))
		{
			letter = 0;
		}
        i++;
    }
	if (i >= 1 && !std::isspace(s[i-1]))
	{
		words++;
	}
	return words;
}
