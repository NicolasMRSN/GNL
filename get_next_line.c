#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char			*my_realloc(char *line, size_t size_reallocated_line)
{
  char			*reallocated_line;
  unsigned short	index = 0;

  reallocated_line = malloc(sizeof(char) * (size_reallocated_line));
  if (!reallocated_line)
    return (NULL);
  while(line[index])
    {
      reallocated_line[index] = line[index];
      ++index;
    }
  reallocated_line[index] = 0;
  free(line);
  return (reallocated_line);
}

static char		get_char_by_char(const int fd)
{
  static char		*line = NULL;
  static unsigned short	ret_read = 0;
  unsigned char		character = 0;

  if (ret_read == 0)
    {
      line = malloc(sizeof(char) * READ_SIZE);
      if (!line)
	return (0);
      ret_read = read(fd, line, READ_SIZE);
      if(ret_read == 0)
	return (0);
    }
  character = *line;
  ++line;
  --ret_read;
  return (character);
}

char			*get_next_line(const int fd)
{
  unsigned char		character = 0;
  char			*line = NULL;
  unsigned short	index = 0;

  line = malloc(sizeof(char) * (READ_SIZE + 1));
  if (!line || fd < 0)
    return (NULL);
  character = get_char_by_char(fd);
  if (character == 0)
    return (NULL);
  while(character != '\n' && character != '\0')
    {
      line[index] = character;
      character = get_char_by_char(fd);
      ++index;
      if (index % (READ_SIZE + 1) == 0)
	line = my_realloc(line, index + (READ_SIZE + 1));
    }
  line[index] = 0;
  return (line);
}
