#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include "push_swap.h"


int		ft_swap(t_node **head);
int		ft_swap_double(t_node **head_a, t_node **head_b);
int		ft_push_a(t_node **head_a, t_node **head_b);
int		ft_push_b(t_node **head_a, t_node **head_b);

int		ft_rotate(t_node **head);
int		ft_rotate_double(t_node **head_a, t_node **head_b);
int		ft_rrotate(t_node **head);
int		ft_rrotate_double(t_node **head_a, t_node **head_b);

#endif
