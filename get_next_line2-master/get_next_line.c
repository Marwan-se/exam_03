
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	*ft_calloc(size_t	count, size_t	size);
int	ft_strlen(char *s);
char	*ft_strndup(const char *s, int n);
char	*find_new_line(char *s);
void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t	count, size_t	size)
{
	void	*mem;

	mem = (void *)malloc(count * size);
	if (mem != NULL)
		ft_bzero(mem, count * size);
	return (mem);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (*s++)
			i++;
	}
	return (i);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*src;
	char	*dst;

	src = (char *)s;
	dst = ft_calloc(n + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*find_new_line(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}

char	*ft_reallocate(char *buffer, int size, char *last_origin)
{
	char	*actual_buffer;

	actual_buffer = ft_strndup(buffer, size);
	if (last_origin)
		free(last_origin);
	else
		free (buffer);
	return (actual_buffer);
}

char	*ft_retline(char *new_line, char **ptr, int counter)
{
	char	*line;

	line = ft_strndup(*ptr, (new_line + 1) - *ptr);
	*ptr = ft_reallocate(new_line + 1, counter + BUFFER_SIZE, *ptr);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*ptr;
	static int		counter;
	char			*line;

	if (!ptr)
		if (!counter)
			ptr = ft_calloc (BUFFER_SIZE + 1, sizeof (char));
	if (fd < 0 || BUFFER_SIZE < 1)
		return (free(ptr), NULL);
	while (!find_new_line(ptr) && ptr && read(fd, &ptr[ft_strlen(ptr)], BUFFER_SIZE) > 0)
		ptr = ft_reallocate(ptr, (counter += BUFFER_SIZE) + BUFFER_SIZE, NULL);
	if (find_new_line(ptr))
		return (ft_retline(find_new_line(ptr), &ptr, counter));
	if (ptr && counter)
		if (*ptr)
			return (line = ptr, ptr = NULL, line);
	free (ptr);
	ptr = NULL;
	return (NULL);
}
