#include "includes/philo.h"

int	parse_arg(int ac, char **av, int *i, t_info *info)
{
	if (*i == 1)
	{
		info->num_philo = argument_check(av[*i]);
		if (info->num_philo > 200)
		{
			printf("Error: Number of philosopher must be up to 200\n");
			return (0);
		}
	}
	else if (*i == 2)
		info->living_time = argument_check(av[*i]);
	else if (*i == 3)
		info->eating_time = argument_check(av[*i]);
	else if (*i == 4)
		info->sleeping_time = argument_check(av[*i]);
	if (ac == 6)
		info->max_eatcount = argument_check(av[*i]);
	else
		info->max_eatcount = 0;
	return (1);
}

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
			return (-1);
	}
	if (!ft_only_digit(&str[i]))
		return (-1);
	if (str[i] == '0' && ft_digit(str[i + 1]))
		return (-1);
	while (ft_digit(str[i]))
		arg = arg * 10 + (str[i++] - 48);
	if (neg == -1)
		arg *= -1;
	if (arg > 2147483647 || arg < -2147483648 || arg < 0)
		return (-1);
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

int	rtn_err_msg(char *str)
{
	printf("%s\n", str);
	return (0);
}
