/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:21:52 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/05 23:55:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// This function converts an integer into its string representation,
// handling positive, negative, and zero values.
//
// The 'n' parameter is the integer to convert. The 'exp' parameter
// specifies the initial power of 10 used during the conversion.
// The 'number' pointer references the allocated string where the
// result is stored.
char	*ft_deintegrer(int n, int exp, char *number)
{
	int		i;
	char	*s;

	i = 0;
	if (n > 0)
	{
		number = ft_deintegrer2(n, exp, i, number);
	}
	else if (n < 0)
	{
		n = n * (-1);
		s = ft_deintegrer2(n, exp, i, number);
		number = ft_strjoin("-", s);
		free(s);
	}
	else
	{
		number[i++] = '0';
		number[i] = '\0';
	}
	return (number);
}

// This function converts an integer into its string representation
// using the provided power of 10.
//
// The 'n' parameter is the integer to convert. The 'exp' parameter
// specifies the initial power of 10 used to extract each digit.
// The 'i' parameter indicates the starting index in the output
// string. The 'number' pointer references the string where the
// converted number is stored.
char	*ft_deintegrer2(int n, int exp, int i, char *number)
{
	int		newn;
	char	*answer;

	answer = number;
	newn = 0;
	while (exp != 0)
	{
		newn = n / exp;
		n = n % exp;
		answer[i++] = newn + '0';
		exp = exp / 10;
	}
	answer[i] = '\0';
	return (answer);
}

// This function converts an integer into a newly allocated string.
//
// The 'n' parameter is the integer to be converted.
char	*ft_itoa(int n)
{
	int		count;
	int		exp;
	char	*number;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_decim(n);
	exp = ft_exp(count);
	number = (char *)malloc((count + 1) * sizeof(char));
	if (!number)
		return (NULL);
	if (n > 0)
		number = ft_deintegrer(n, exp, number);
	else if (n < 0)
		number = ft_deintegrer(n, exp, number);
	else
		number = ft_deintegrer(n, exp, number);
	return (number);
}

// This function counts the number of decimal digits in an integer.
//
// The 'n' parameter is the integer whose number of digits is
// calculated.
int	ft_decim(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

// This function calculates the power of 10 corresponding to the
// number of digits received.
//
// The 'count' parameter specifies the number of decimal digits.
int	ft_exp(int count)
{
	int	exp;

	exp = 1;
	while (count > 1)
	{
		exp = exp * 10;
		count--;
	}
	return (exp);
}
