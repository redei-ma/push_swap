#include "push_swap.h"

void	tidy_up(t_node **head_a)
{
	int	min;
	int	pos;
	int	i;
	int	size;

	i = 0;
	size = ft_lstsize_push(*head_a);
	min = ft_minor(*head_a);
	pos = pos_calc(*head_a, min, size);
	while (i < ft_abs(pos))
	{
		if (pos > 0)
			ft_ra(head_a);
		else
			ft_rra(head_a);
		i++;
	}
}

/**
 * Signed number of rotations that brings num to the top of the stack.
 *
 * @param size: the stack length, passed in rather than recomputed here
 *
 * Positive means rotate forward, negative means rotate backward: an element
 * past the midpoint is reported as i - size, the distance the short way
 * round. Callers act on the sign, so returning the raw index would silently
 * make every lower-half element cost the long way.
 *
 * Returns 404 if num is not in the stack. Callers never trigger it, since
 * they only ask for values they have just read from this same stack; it is a
 * sentinel for a broken invariant, not an error code to handle.
 */
int	pos_calc(t_node	*head, int num, int size)
{
	int		i;
	t_node	*tmp;

	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->value == num && i <= size / 2)
			return (i);
		else if (tmp->value == num && i > size / 2)
			return (i - size);
		i++;
		tmp = tmp->next;
	}
	return (404);
}

void	set_weights(int *moves, int *tmp_moves)
{
	moves[0] = tmp_moves[0];
	moves[1] = tmp_moves[1];
	moves[2] = ft_abs(tmp_moves[2]);
}
