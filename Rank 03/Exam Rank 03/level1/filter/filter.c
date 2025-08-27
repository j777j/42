#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

static size_t	process_buffer(char *work_buf, size_t work_len,
	const char *search, size_t search_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i + search_len <= work_len)
	{
		if (ft_strncmp(work_buf + i, search, search_len) == 0)
		{
			j = 0;
			while (j++ < search_len)
				printf("*");
			i += search_len;
		}
		else
		{
			printf("%c", work_buf[i]);
			i++;
		}
	}
	return (i);
}

int	main(int argc, char *argv[])
{
	char		read_buf[4096];
	char		*work_buf;
	char		*overlap_buf;
	ssize_t		bytes_read;
	size_t		search_len;
	size_t		overlap_len;
	size_t		processed_len;

	if (argc != 2 || !argv[1] || !argv[1][0])
		return (1);
	search_len = ft_strlen(argv[1]);
	overlap_buf = (char *)calloc(search_len, sizeof(char));
	if (!overlap_buf)
	{
		perror("Error");
		return (1);
	}
	overlap_len = 0;
	while ((bytes_read = read(0, read_buf, 4096)) > 0)
	{
		work_buf = (char *)malloc(overlap_len + bytes_read);
		if (!work_buf)
		{
			perror("Error");
			free(overlap_buf);
			return (1);
		}
		ft_memcpy(work_buf, overlap_buf, overlap_len);
		ft_memcpy(work_buf + overlap_len, read_buf, bytes_read);
		processed_len = process_buffer(work_buf, overlap_len + bytes_read,
				argv[1], search_len);
		overlap_len = (overlap_len + bytes_read) - processed_len;
		ft_memcpy(overlap_buf, work_buf + processed_len, overlap_len);
		free(work_buf);
	}
	if (bytes_read < 0)
	{
		perror("Error");
		free(overlap_buf);
		return (1);
	}
	write(1, overlap_buf, overlap_len);
	free(overlap_buf);
	return (0);
}