/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:59:18 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/29 13:16:07 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RST "\033[0m"    // reset to default color
# define RED "\033[1;31m" // bold red
# define G "\033[1;32m"   // bold green
# define Y "\033[1;33m"   // bold Yellow
# define B "\033[1;34m"   // bold blue
# define M "\033[1;35m"   // bold magenta
# define C "\033[1;36m"   // bold cyan
# define W "\033[1;37m"   // bold white

// true || (false && echo hi)
// false && (true || echo A)

#endif