/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elebouch <elebouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:04:58 by elebouch          #+#    #+#             */
/*   Updated: 2018/03/12 16:53:50 by elebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bin(char *cmd, char *paths)
{
	char		**split;
	char		*tmp;
	struct stat	stats;
	int			i;
	int			status;

	i = -1;
	if (!paths)
		return (ft_strdup(cmd));
	if (!(split = ft_strsplit(paths, ':')))
		return (ft_strdup(cmd));
	while (split[++i])
	{
		tmp = (split[i][ft_strlen(split[i]) - 1] == '/') ? ft_strdup(split[i]) :
			ft_strjoin(split[i], "/");
		if (!tmp || !(tmp = ft_strcleanjoin(tmp, cmd)))
			exit(EXIT_FAILURE);
		if (!(status = stat(tmp, &stats)))
			break ;
		else
			free(tmp);
	}
	freearr(&split);
	return ((status == -1) ? ft_strdup(cmd) : tmp);
}

t_cmd	*get_path(char **env, char *cmd)
{
	int		i;
	t_cmd	*data;

	i = -1;
	if (!(data = (t_cmd*)malloc(sizeof(t_cmd))))
		exit(EXIT_FAILURE);
	if (env)
		while (env[++i])
			if (!ft_strncmp(env[i], "PATH=", 5))
				break ;
	data->path = (env && env[i]) ? ft_strsub(env[i], 5, ft_strlen(env[i])) :
		NULL;
	data->bin = get_bin(cmd, data->path);
	if (!(data->cmd = ft_strdup(cmd)))
		return (NULL);
	return (data);
}

int		execute(t_args *args, char ***env)
{
	static char	*bltin_str[] = {"echo", "cd", "env", "setenv",
		"unsetenv", "exit"};
	static int	(*bltin_func[]) (char **, char ***) = { &bltin_echo, &bltin_cd,
		&bltin_env, &bltin_setenv, &bltin_unsetenv, &bltin_exit};
	int			i;
	t_cmd		*data;

	i = -1;
	if (!args || !args->argc || !args->argv[0])
		return (1);
	while (++i < 6)
		if (!ft_strcmp(args->argv[0], bltin_str[i]))
			return (bltin_func[i](args->argv, env));
	if (!(data = get_path(*env, args->argv[0])))
		return (1);
	return (cmd_launch(data, args->argv, *env));
}
