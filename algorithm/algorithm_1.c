#include "push_swap.h"

/**
 * Signed cost of bringing element i of stack b to the top.
 *
 * @param head_b: the node AT index i, not the head of b
 * @param i: that node's index, counted from the top
 *
 * The caller walks b and hands over the current node, so the size of the
 * whole stack is no longer visible from here: a node only sees what follows
 * it. Adding i back to the length of that tail recovers it.
 *
 * Positive means rb, negative means rrb. Elements in the lower half are
 * reported as negative because reaching them backwards costs less.
 */
int	ft_weight_b(t_node *head_b, int i)
{
	int		weight;
	int		size_b;

	weight = 0;
	size_b = ft_lstsize_push(head_b) + i;
	if (i <= size_b / 2)
		weight = i;
	else if (i < size_b)
		weight = i - size_b;
	return (weight);
}

/**
 * Signed cost of rotating a so that val_b's insertion point is on top.
 *
 * @param head_a: stack a, sorted up to a rotation
 * @param val_b: the value that would be pushed back
 *
 * Relies on a being sorted up to a rotation, which holds for the whole drain
 * of b: such a stack has exactly one descent, so the pair that val_b fits
 * between is unique and the first match is the right one.
 *
 * Two cases do not look like the others. The last node is compared against
 * the head, which covers a value falling in the wrap between the largest and
 * the smallest. And a value outside the whole range — below the minimum or
 * above the maximum — matches no pair at all, leaving the loop with a NULL
 * cursor; it belongs just above the minimum, which is where the stack wraps.
 */
int	ft_weight_a(t_node *head_a, int val_b)
{
	int		weight;
	t_node	*tmp_a;

	tmp_a = head_a;
	while (tmp_a)
	{
		if (tmp_a->next)
		{
			if (val_b > tmp_a->value && val_b < tmp_a->next->value)
			{
				weight = pos_calc(head_a, tmp_a->next->value,
						ft_lstsize_push(head_a));
				break ;
			}
		}
		else if (val_b > tmp_a->value && val_b < head_a->value)
		{
			weight = pos_calc(head_a, head_a->value, ft_lstsize_push(head_a));
			break ;
		}
		tmp_a = tmp_a->next;
	}
	if (tmp_a == NULL)
		weight = pos_calc(head_a, ft_minor(head_a), ft_lstsize_push(head_a));
	return (weight);
}

void	ft_algo(t_node **head_a, t_node **head_b)
{
	int		moves[3];
	int		i;
	t_node	*tmp_b;

	tmp_b = *head_b;
	i = 0;
	moves[2] = -1;
	while (tmp_b)
	{
		ft_weight_tot(head_a, &tmp_b, moves, i);
		i++;
		tmp_b = tmp_b->next;
	}
	make_move(moves, head_a, head_b);
}

/**
 * Prices one candidate and keeps it in moves if it is the cheapest so far.
 *
 * @param moves: best cost seen, as {rotations on a, on b, total}
 * @param i: index in b of the candidate being priced
 *
 * The total is not the sum of the two costs. When both point the same way the
 * rotations happen together as rr or rrr, so the pair costs whichever is
 * larger, paid once. Only when the signs disagree must the stacks be turned
 * separately, and the costs add up.
 *
 * moves[2] starts at -1 to mean "nothing priced yet", which is why the
 * comparison tests for it instead of relying on a large initial value.
 */
void	ft_weight_tot(t_node **head_a, t_node **head_b, int *moves, int i)
{
	int	tmp_moves[3];

	tmp_moves[0] = ft_weight_a(*head_a, (*head_b)->value);
	tmp_moves[1] = ft_weight_b(*head_b, i);
	if (tmp_moves[0] >= 0 && tmp_moves[1] >= 0)
	{
		if (tmp_moves[0] > tmp_moves[1])
			tmp_moves[2] = tmp_moves[0];
		else
			tmp_moves[2] = tmp_moves[1];
	}
	else if (tmp_moves[0] < 0 && tmp_moves[1] < 0)
	{
		if (tmp_moves[0] < tmp_moves[1])
			tmp_moves[2] = tmp_moves[0];
		else
			tmp_moves[2] = tmp_moves[1];
	}
	else
		tmp_moves[2] = ft_abs(tmp_moves[0]) + ft_abs(tmp_moves[1]);
	if (ft_abs(tmp_moves[2]) < moves[2] || moves[2] == -1)
		set_weights(moves, tmp_moves);
}
