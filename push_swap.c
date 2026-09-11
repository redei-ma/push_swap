#include "push_swap.h"

void	ft_sort(t_node **head_a, t_node **head_b)
{
	int	size;

	size = ft_lstsize_push(*head_a);
	if (size == 2)
		return (ft_sa(head_a));
	while (size-- > 3)
		ft_pb(head_a, head_b);
	sort_three(head_a);
	while (*head_b)
		ft_algo(head_a, head_b);
	tidy_up(head_a);
}

int	main(int ac, char **av)
{
	t_node	*head_a;
	t_node	*head_b;

	if (ac < 2)
		return (1);
	head_a = ft_lstcreation(av);
	head_b = NULL;
	if (!head_a)
		return (write(2, "Error\n", 6));
	if (checkduplicate(head_a) == 0)
		return (ft_freelst(&head_a, &head_b), write(2, "Error\n", 6));
	if (check_finish(head_a, head_b) == 1)
		return (ft_freelst(&head_a, &head_b));
	ft_sort(&head_a, &head_b);
	if (check_finish(head_a, head_b) == 0)
		write(2, "Error\n", 6);
	ft_freelst(&head_a, &head_b);
	return (0);
}
