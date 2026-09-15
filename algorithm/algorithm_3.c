#include "push_swap.h"

/**
 * Puts the last three elements of a into rotational order.
 *
 * Not into ascending order: the contract is weaker on purpose. Everything
 * downstream only needs a to have a single descent — ft_weight_a finds the
 * insertion point by looking for it, and tidy_up brings the minimum to the
 * top once b is empty. So [2, 3, 1] and [3, 1, 2] are already done, and
 * emitting moves for them would be waste.
 *
 * Hence the first branch, which looks redundant and is not: an already
 * ascending stack is the one case needing no move at all, and without the
 * early return it falls into the branch below, whose condition only says
 * "the top is the smallest" and which would answer ra sa — correct for
 * [1, 3, 2], destructive for [1, 2, 3].
 *
 * Assumes three nodes. ft_sort handles the shorter stacks before calling.
 */
void	sort_three(t_node **head_a)
{
	t_node	*tmp;

	tmp = *head_a;
	if (tmp->value < tmp->next->value
		&& tmp->next->value < tmp->next->next->value)
		return ;
	if (tmp->value > tmp->next->value
		&& tmp->value < tmp->next->next->value)
		return (ft_sa(head_a));
	else if (tmp->value < tmp->next->value
		&& tmp->value < tmp->next->next->value)
		return (ft_ra(head_a), ft_sa(head_a));
	else if (tmp->value > tmp->next->value
		&& tmp->next->value > tmp->next->next->value)
		return (ft_sa(head_a));
	else
		return ;
}

static void	move_single(int *moves, t_node **head_a, t_node **head_b)
{
	if (moves[0] > 0)
	{
		ft_ra(head_a);
		moves[0]--;
	}
	else if (moves[0] < 0)
	{
		ft_rra(head_a);
		moves[0]++;
	}
	else if (moves[1] > 0)
	{
		ft_rb(head_b);
		moves[1]--;
	}
	else if (moves[1] < 0)
	{
		ft_rrb(head_b);
		moves[1]++;
	}
}

static void	move_double(int *moves, t_node **head_a, t_node **head_b)
{
	if (moves[0] > 0 && moves[1] > 0)
	{
		ft_rr(head_a, head_b);
		moves[0]--;
		moves[1]--;
	}
	else if (moves[0] < 0 && moves[1] < 0)
	{
		ft_rrr(head_a, head_b);
		moves[0]++;
		moves[1]++;
	}
	else
		move_single(moves, head_a, head_b);
}

void	make_move(int *moves, t_node **head_a, t_node **head_b)
{
	while (moves[0] != 0 && moves[1] != 0)
		move_double(moves, head_a, head_b);
	while (moves[0] != 0 || moves[1] != 0)
		move_single(moves, head_a, head_b);
	ft_pa(head_a, head_b);
}
