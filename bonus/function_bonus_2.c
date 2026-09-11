#include "push_swap_bonus.h"

int	ft_rotate(t_node **head)
{
	int		num;
	t_node	*start;

	start = *head;
	if ((*head) && (*head)->next)
	{
		num = (*head)->value;
		while ((*head)->next)
		{
			(*head)->value = (*head)->next->value;
			(*head) = (*head)->next;
		}
		(*head)->value = num;
	}
	*head = start;
	return (1);
}

int	ft_rotate_double(t_node **head_a, t_node **head_b)
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
	}
	return (1);
}

int	ft_rrotate(t_node **head)
{
	t_node	*tmp;

	if ((*head) && (*head)->next)
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->prev->next = NULL;
		tmp->prev = NULL;
		tmp->next = *head;
		(*head)->prev = tmp;
		*head = tmp;
	}
	return (1);
}

int	ft_rrotate_double(t_node **head_a, t_node **head_b)
{
	t_node	*tmp;

	if ((*head_a) && (*head_a)->next && (*head_b) && (*head_b)->next)
	{
		tmp = *head_a;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->prev->next = NULL;
		tmp->prev = NULL;
		tmp->next = *head_a;
		(*head_a)->prev = tmp;
		*head_a = tmp;
		tmp = *head_b;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->prev->next = NULL;
		tmp->prev = NULL;
		tmp->next = *head_b;
		(*head_b)->prev = tmp;
		*head_b = tmp;
	}
	return (1);
}
