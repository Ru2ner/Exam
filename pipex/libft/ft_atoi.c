/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:28:58 by tmarion           #+#    #+#             */
/*   Updated: 2024/11/28 14:29:00 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	sign;
	int	count;

	i = 0;
	a = 0;
	count = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	while (str[i] == 43 || str[i] == 45)
	{
		count++;
		if (str[i] == 45)
			sign = sign * (-1);
		i++;
	}
	while (str[i] > 47 && str[i] < 58 && count < 2)
	{
		a = a * 10 + (str[i] - 48);
		i++;
	}
	return (a * sign);
}

/*int	main(void)
{
	char i[] = "\t\v\f\r\n \f-06050";
	
	printf("%d\n", ft_atoi(i));
}*/