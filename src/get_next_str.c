#include "so_long.h"

char	*get_next_str(int fd)
{
	char	*str;
	size_t	len;

	str = get_next_line(fd);
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}
