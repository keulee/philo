#include "includes/philo.h"

int	argument_check(char *str)
{
	int			i;
	int			neg;
	long long	arg;

	i = 0;
	neg = 1;
	arg = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			neg = neg * -1;
		if (str[i] == '\0' || str[i] == '0')
			return (0);
	}
	if (!ft_only_digit(&str[i]))
		return (0);
	if (str[i] == '0' && ft_digit(str[i + 1]))
		return (0);
	while (ft_digit(str[i]))
		arg = arg * 10 + (str[i++] - 48);
	if (neg == -1)
		arg *= -1;
	if (arg > 2147483647 || arg < -2147483648 || arg < 0)
		return (0);
	return (arg);
}

int	ft_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}