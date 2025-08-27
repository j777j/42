#include "get_next_line.h" // 假设h文件只包含主函数原型和宏
#include <unistd.h>

static char	*ft_strjoin_and_free(char *s1, const char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	new_str = (char *)malloc(i + j + 1);
	if (!new_str)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	return (free(s1), new_str);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*nl_ptr;
	int		i;
	int		i;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	nl_ptr = NULL;
	if (stash) // check if stash already has a newline
	{
		i = -1;
		while (stash[++i])
			if (stash[i] == '\n')
				nl_ptr = stash; // Just a non-null ptr to stop loop
	}
	bytes_read = 1;
	while (!nl_ptr && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_and_free(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
		i = -1;
		while (buffer[++i])
			if (buffer[i] == '\n')
				nl_ptr = buffer; // Just a non-null ptr to stop loop
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char *stash[1024];
	char *line;
	char *new_stash;
	int i;
	int j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd] || !stash[fd][0])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	i = 0;
	while (stash[fd][i] && stash[fd][i] != '\n')
		i++;
	if (stash[fd][i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	j = -1;
	while (++j < i)
		line[j] = stash[fd][j];
	line[j] = '\0';
	j = 0;
	while (stash[fd][i + j])
		j++;
	new_stash = (char *)malloc(j + 1);
	if (!new_stash)
		return (free(stash[fd]), stash[fd] = NULL, free(line), NULL);
	j = -1;
	while (stash[fd][i + ++j])
		new_stash[j] = stash[fd][i + j];
	new_stash[j] = '\0';
	return (free(stash[fd]), stash[fd] = new_stash, line);
}
