/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:55:25 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/19 18:33:12 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_environ
{
	char	**env;

}	t_env;


int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}


extern char	**environ;

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	i = 0;
	if (src == NULL)
		return (NULL);
	str = (char *)malloc(ft_strlen(src) + 1);
	if (str == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_env_value(char *path, char **envp)
{
	;
}

int	contains_slash(char *cmd)
{
	while (cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}
/*
char    *find_executable_path(char *cmd, char **envp)
{
	char	*path_env;
	int	i;

	i = 0;
    // 1. Check if 'cmd' contains a slash. If yes, treat it as
    //    an absolute or relative path and just test it.
	if (contains_slash(cmd))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value("PATH=", envp);
	
    // 2. If it doesn't contain a slash, search the PATH
    //    environment variable.
	
    // 3. Return a newly allocated string if found, or NULL if not.
}


int	exec_external(char *cmd, char **args)
{
	char	*fullpath;
	int		status;
	pid_t	pid;

	fullpath = find_fullPath();
	if (!fullpath)
	{
		// Command not found in PATH
		//ft_fprintf(stderr, "minishell: command not found: %s\n", args[0]);
		return (127);
	}
	pid = fork;
	if (pid = 0)
	{
		execve(fullpath, args[0], environ);
		perror("execve");
		exit(1);
	}
	else
		waitpid(pid, status, 0);
	
}*/


int	is_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (1);
	else if (ft_strcmp(cmd, "cd"))
		return (1);
	else if (ft_strcmp(cmd, "pwd"))
		return (1);
	else if (ft_strcmp(cmd, "export"))
		return (1);
	else if (ft_strcmp(cmd, "unset"))
		return (1);
	else if (ft_strcmp(cmd, "env"))
		return (1);
	else if (ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

void	init_env(t_env *envi)
{
	int count;
	int i;
	int len;
	int j;

	// 1. Count how many env variables we have
	count = 0;
	while (environ[count])
		count++;
	// 2. Allocate enough pointers (plus one for NULL terminator)
	envi->env = malloc(sizeof(char *) * (count + 1));
	if (!envi->env)
		return ;  // handle allocation error if needed
	// 3. Copy each environment string
	i = 0;
	while (i < count)
	{
		// measure the length of environ[i]
		len = 0;
		while (environ[i][len])
			len++;
		// allocate space for the copy
		envi->env[i] = malloc(sizeof(char) * (len + 1));
		if (!envi->env[i])
		{
			// handle allocation error
			// ideally free what was allocated so far
			return ;
		}
		// copy the string
		j = 0;
		while (j < len)
		{
			envi->env[i][j] = environ[i][j];
			j++;
		}
		envi->env[i][j] = '\0';
		i++;
	}
	// 4. Null-terminate the array of pointers
	envi->env[i] = NULL;
}


void	print_env(t_env *envi)
{
	int	i;

	i = 0;
	while (envi->env[i])
	{
		printf("%s", envi->env[i]);
		printf("\n");
		i++;
	}
	return ;
}

void	exec(char *arg, char **args)
{
	t_env envi;

	init_env(&envi);
	
	
	if (is_built_in(arg) == 1)
	{
		//execBuiltin
	}
	else
	{
		//exec_external(arg, args);
	}
}

int main()
{
	char **arr;
	t_env envi;

	arr = NULL;
	init_env(&envi);
	print_env(&envi);
	//exec("test", arr);
	return(0);
}