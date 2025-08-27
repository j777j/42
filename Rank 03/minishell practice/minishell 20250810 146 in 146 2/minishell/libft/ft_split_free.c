#include "libft.h"

void	ft_split_free(char **split_array)
{
	int	i;

	if (!split_array)
		return;
	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}
