#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	i;
	int	len;
	int	*range;

	i = 0;
	if (start <= end)
		len = end - start + 1;
	else
		len = start - end + 1;
	range = malloc(sizeof(int) * len);
	if (!range)
		return (NULL);
	while (i < len)
	{
		if (start <= end)
			range[i] = start++;
		else
			range[i] = start--;
		i++;
	}
	return (range);
}

// wtf i want to have this new one after 5th try of exam
#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	i;
	int	*s;

	i = 0;
	if (start <= end)
		i = end - start + 1;
	else
		i = start - end + 1;
	s = (int *)malloc(sizeof(int) * i);
	if (!s)
		return (NULL);
	while (--i >= 0)
	{
		if (start <= end)
			s[i] = end--;
		else
			s[i] = end++;
	}
	return (s);
}
