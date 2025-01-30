/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortmann <aortmann@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:17:37 by aortmann          #+#    #+#             */
/*   Updated: 2024/01/07 18:14:00 by aortmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Adds the node ’new’ at the end of the list
void ft_lstadd_back(t_list **lst, t_list *new)*/
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	head = *lst;
	while (head->next != 0)
		head = head->next;
	head->next = new;
}
