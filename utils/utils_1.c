#include "push_swap.h"

int	ft_minor(t_node *head)
{
	int		min;
	t_node	*tmp;

	tmp = head;
	min = tmp->value;
	while (tmp)
	{
		if (tmp->value < min)
			min = tmp->value;
		tmp = tmp->next;
	}
	return (min);
}

int	check_finish(t_node *head_a, t_node *head_b)
{
	t_node	*tmp_a;

	tmp_a = head_a;
	if (!head_b)
	{
		while (tmp_a && tmp_a->next)
		{
			if (tmp_a->next->value < tmp_a->value)
				return (0);
			tmp_a = tmp_a->next;
		}
		return (1);
	}
	else
		return (0);
}

int	checkduplicate(t_node *lst)
{
	t_node	*node;
	t_node	*test;

	node = lst;
	while (node)
	{
		test = node->next;
		while (test)
		{
			if (node->value == test->value)
				return (0);
			test = test->next;
		}
		node = node->next;
	}
	return (1);
}
