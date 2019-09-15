
#include "lem_in.h"

void	printqueu2(char *title, t_list *q)
{
	int		i;

	i = 0;
	while (q)
	{
		if ((t_data *)(q->content))
			ft_printf("%d : %s (%s, %d, %c)\n", i, title, ((t_data *)(q->content))->name, ((t_data *)(q->content))->level, ((t_data *)(q->content))->role);
		else
			ft_printf("%d : empty list node...(%s)\n", i, title);
		q = q->next;
		i += 1;
	}
}

