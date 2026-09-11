#include "push_swap.h"

void	ft_ra(t_node **head_a)
{
	int		tmp;
	t_node	*head;

	head = *head_a;
	if ((*head_a) && (*head_a)->next)
	{
		tmp = (*head_a)->value;
		while ((*head_a)->next)
		{
			(*head_a)->value = (*head_a)->next->value;
			(*head_a) = (*head_a)->next;
		}
		(*head_a)->value = tmp;
		write(1, "ra\n", 3);
	}
	*head_a = head;
}

void	ft_rb(t_node **head_b)
{
	int		tmp;
	t_node	*head;

	head = *head_b;
	if ((*head_b) && (*head_b)->next)
	{
		tmp = (*head_b)->value;
		while ((*head_b)->next)
		{
			(*head_b)->value = (*head_b)->next->value;
			(*head_b) = (*head_b)->next;
		}
		(*head_b)->value = tmp;
		write(1, "rb\n", 3);
	}
	*head_b = head;
}

void	ft_rr(t_node **head_a, t_node **head_b)
{
	int		tmp;
	t_node	*head;

	if ((*head_a) && (*head_a)->next && (*head_b) && (*head_b)->next)
	{
		head = *head_a;
		tmp = (*head_a)->value;
		while ((*head_a)->next)
		{
			(*head_a)->value = (*head_a)->next->value;
			(*head_a) = (*head_a)->next;
		}
		(*head_a)->value = tmp;
		*head_a = head;
		head = *head_b;
		tmp = (*head_b)->value;
		while ((*head_b)->next)
		{
			(*head_b)->value = (*head_b)->next->value;
			(*head_b) = (*head_b)->next;
		}
		(*head_b)->value = tmp;
		*head_b = head;
		write(1, "rr\n", 3);
	}
}
