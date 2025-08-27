/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:26:51 by juwang            #+#    #+#             */
/*   Updated: 2025/08/27 10:20:09 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	int N = 5;
	Zombie *horde = zombieHorde(N, "Foo");

	for (int i = 0; i < N; i++)
		horde[i].announce();
	delete[] horde;
	return (0);
}
