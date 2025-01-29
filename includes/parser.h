/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjbogisc <bjbogisc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:10:47 by bjbogisc          #+#    #+#             */
/*   Updated: 2024/12/11 12:55:11 by bjbogisc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_token_types
{
	T_WORD,			// " ls " " -l " " grep " " a " " file "
	T_PIPE,			// " | "
	T_INPUT,		// " < "
	T_OUTPUT,		// " > "
	T_HEREDOC,		// " << "
	T_APPEND,		// " >> "
	T_SINGLEQUOTE,	// " '' "
	T_DOUBLEQUOTE,	// " "" "
}			t_token_types;





#endif