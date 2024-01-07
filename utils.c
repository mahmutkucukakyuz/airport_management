#include "airport_management.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void ft_find_id_print(int fd, int id)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0] && id == ft_atoi(result[0]))
        {
            printf("%s", result[1]);
            return;
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_find_iata_print(int fd, char *id)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0] && !ft_strcmp2(id, result[0]))
        {
            printf("%s\n", result[1]);
            return;
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
    return;
}




// int is_it_has(int fd, int select)
// {
    
//     char *line = get_next_line(fd);
//     char **result = ft_split(line, ',');
//     while (line)
//     {
//         line = get_next_line(fd);
//         result = ft_split(line, ',');
//         if (ft_atoi(result[0]) == select)
//         {
//             return(1);
//         }
//     }
//     free_split(result);
//     if (line)
//         free(line);
//     return(0);
// }

int is_it_has(int fd, int select) {
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    char **result = ft_split(line, ',');
    while (line) {
        result = ft_split(line, ',');
        if (result[0] && ft_atoi(result[0]) == select) {
            free_split(result);
            free(line);
            return 1;
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
    return 0;
}

int is_it_has_char(int fd, char *select) {
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    char **result = ft_split(line, ',');
    while (line) {
        result = ft_split(line, ',');
        if (result[0] && ft_strcmp2(select, result[0])) {
            free_split(result);
            free(line);
            return 1;
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
    return 0;
}

int get_new_id(int fd)
{
    int new_id;
    new_id = 0;
    char *line = get_next_line(fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        line = get_next_line(fd);
        if (new_id <= ft_atoi(result[0]))
        {
            new_id = ft_atoi(result[0]) + 1;
        }
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
    return (new_id);
}

int match_id(int fd, char input_string[50], int id_col, int source_col)
{
    int id = 0;
    char *line = get_next_line(fd);
    char **result;
    line = get_next_line(fd);
    line = get_next_line(fd);
    while (line)
    {
        result = ft_split(line, ',');
        if (!ft_strcmp(input_string, result[source_col])) //1
        {
            id = ft_atoi(result[id_col]); //0
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    if (line)
    {
        free(line);
    }
    free_split(result);
    return(id);
}

void ft_write_text(int fd, char **a, int i)
{
    lseek(fd, 0, SEEK_END);
    write(fd, "\n", 1);
    int j = 0;
    while (i > j)
    {
        write(fd,a[j], ft_strlen(a[j]));
        if (j != i - 1)
        {
            write(fd,",", 1);
        }
        j++;
    }
    lseek(fd, 0, SEEK_END);
}