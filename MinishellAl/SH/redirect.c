/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:53:41 by aortmann          #+#    #+#             */
/*   Updated: 2025/01/26 22:14:07 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// Implement stru->exes (| character). The output of each command in the stru->exeline is
// connected to the input of the nstru->exet command via a stru->exe.

bool check_redirect(t_str *stru)
{
    if (!stru)
        return (0);
    if (!stru->xpipe->re)
        return (0);
    // if (!stru->xpipe->redirectors[0])
    //     return (0);
    printf("REDIRECTOR NOT EMPTY!!!!!!\n");
    printf("%s IS REDIRECTOR 1\n", stru->xpipe->re);
    return (1);
}


