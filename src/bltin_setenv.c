/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elebouch <elebouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:56:42 by elebouch          #+#    #+#             */
/*   Updated: 2018/05/03 18:50:01 by elebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(char ***env, char *var, char *value)
{
	int		index;
	char	*tmp;
	char	**envi;

	index = get_index_fromenv(*env, var);
	tmp = NULL;
	if (!value || !*env || !(tmp = ft_strjoin("=", value)))
		return ;
	envi = *env;
	if (envi[index])
	{
		free(envi[index]);
		envi[index] = (value) ? ft_strjoin(var, tmp) : ft_strjoin(var, "=");
	}
	else
	{
		envi = realloc_env(envi, index + 1);
		envi[index] = (value) ? ft_strjoin(var, tmp) : ft_strjoin(var, "=");
	}
	*env = envi;
	free(tmp);
}

int		bltin_setenv(char **args, char ***env)
{
	if (!env)
		return (0);
	if (!args[1])
	{
		bltin_env(args, env);
		return (1);
	}
	if (args[2])
	{
		if (args[3])
		{
			ft_putendl_fd("setenv: Too many arguments.", 2);
			return (1);
		}
		change_env(env, args[1], args[2]);
	}
	else
		ft_putendl_fd("setenv: Too few arguments.", 2);
	return (1);
}
