#include "push_swap_bonus.h"

int	ft_swap(t_node **head)
{
	int	tmp;

	if ((*head) && (*head)->next)
	{
		tmp = (*head)->value;
		(*head)->value = (*head)->next->value;
		(*head)->next->value = tmp;
	}
	return (1);
}

int	ft_swap_double(t_node **head_a, t_node **head_b)
{
	int	tmp;

	if ((*head_a) && (*head_a)->next && (*head_b) && (*head_b)->next)
	{
		tmp = (*head_a)->value;
		(*head_a)->value = (*head_a)->next->value;
		(*head_a)->next->value = tmp;
		tmp = (*head_b)->value;
		(*head_b)->value = (*head_b)->next->value;
		(*head_b)->next->value = tmp;
	}
	return (1);
}

int	ft_push_a(t_node **head_a, t_node **head_b)
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
	return (1);
}

int	ft_push_b(t_node **head_a, t_node **head_b)
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
	return (1);
}
