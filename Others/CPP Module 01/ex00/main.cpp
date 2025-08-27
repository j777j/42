/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 06:45:44 by juwang            #+#    #+#             */
/*   Updated: 2025/08/27 10:19:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	*zombie;
	delete	zombie;

	zombie = newZombie("Heap Zombie");
	zombie->announce();
	randomChump("Stack Zombie");
	return (0);
}
