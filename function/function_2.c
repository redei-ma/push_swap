#include "push_swap.h"

void	ft_pa(t_node **head_a, t_node **head_b)
{
	t_node	*tmp;

	if (*head_b)
	{
		tmp = *head_b;
		if ((*head_b)->next)
		{
			*head_b = (*head_b)->next;
			(*head_b)->prev = NULL;
		}
		else
		{
			(*head_b)->next = NULL;
			(*head_b)->prev = NULL;
			*head_b = NULL;
		}
		if (*head_a)
			(*head_a)->prev = tmp;
		tmp->next = *head_a;
		*head_a = tmp;
	}
	write(1, "pa\n", 3);
}

void	ft_pb(t_node **head_a, t_node **head_b)
{
	t_node	*tmp;

	if (*head_a)
	{
		tmp = *head_a;
		if ((*head_a)->next)
		{
			*head_a = (*head_a)->next;
			(*head_a)->prev = NULL;
		}
		else
			*head_a = NULL;
		if (*head_b)
			(*head_b)->prev = tmp;
		tmp->next = *head_b;
		*head_b = tmp;
	}
	write(1, "pb\n", 3);
}
