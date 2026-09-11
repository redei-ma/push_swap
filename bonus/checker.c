#include "push_swap_bonus.h"

int	custom_move(t_node **head_a, t_node **head_b, char *line, int *check)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		return (ft_swap(head_a));
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		return (ft_swap(head_b));
	else if (ft_strncmp(line, "ss\n", 3) == 0)
		return (ft_swap_double(head_a, head_b));
	else if (ft_strncmp(line, "pa\n", 3) == 0)
		return (ft_push_a(head_a, head_b));
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		return (ft_push_b(head_a, head_b));
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		return (ft_rotate(head_a));
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		return (ft_rotate(head_b));
	else if (ft_strncmp(line, "rr\n", 3) == 0)
		return (ft_rotate_double(head_a, head_b));
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		return (ft_rrotate(head_a));
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		return (ft_rrotate(head_b));
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
		return (ft_rrotate_double(head_a, head_b));
	*check = write(2, "Error\n", 6);
	return (0);
}

void	write_finish(t_node *head_a, t_node *head_b)
{
	if (check_finish(head_a, head_b) == 0)
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
}

int	main(int ac, char **av)
{
	char	*line;
	t_node	*head_a;
	t_node	*head_b;
	int		check;

	if (ac < 2)
		return (1);
	head_a = ft_lstcreation(av);
	head_b = NULL;
	check = 0;
	if (!head_a)
		return (write(2, "Error\n", 6));
	if (checkduplicate(head_a) == 0)
		return (ft_freelst(&head_a, &head_b), write(2, "Error\n", 6));
	line = get_next_line(0);
	while (line && custom_move(&head_a, &head_b, line, &check))
	{
		free(line);
		line = get_next_line(0);
	}
	free(line);
	if (check == 0)
		write_finish(head_a, head_b);
	ft_freelst(&head_a, &head_b);
	return (0);
}
