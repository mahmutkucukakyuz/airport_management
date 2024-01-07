#include "airport_management.h"

void ft_list_airlines(t_list *list)
{
    lseek(list->airline_fd, 0, SEEK_SET);
    char *line = get_next_line(list->airline_fd);
    line = get_next_line(list->airline_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0])
        {
            printf("ID: %s Airline name: %s\n", result[0],result[1]);
        }
        line = get_next_line(list->airline_fd);
    }
    lseek(list->airline_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_list_airlines_country(t_list *list)
{
    lseek(list->airline_fd, 0, SEEK_SET);
    char *line = get_next_line(list->airline_fd);
    line = get_next_line(list->airline_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0])
        {
            printf("Airline name: %s Country: %s", result[1],result[2]);
        }
        line = get_next_line(list->airline_fd);
    }
    printf("\n");
    lseek(list->airline_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_add_airlines(t_list *list)
{
    lseek(list->airline_fd, 0, SEEK_SET);
    char name[50];
    char country[50];
    int new_id;
    printf("Enter airline name: ");
    scanf("%49s", name);
    printf("Enter airline country name: ");
    scanf("%49s", country);
    new_id = get_new_id(list->airline_fd);
    char *arr[3] = {ft_itoa(new_id), name, country};
    ft_write_text(list->airline_fd, arr , 3);
    printf("Added successfully.\n");
    lseek(list->airline_fd, 0, SEEK_SET);
}

void ft_del_airlines(t_list *list)
{
    lseek(list->airline_fd, 0, SEEK_SET);
    int select;
    printf("Enter airline id, enter 0 to list ids: ");
    scanf("%d", &select);
    if (select == 0) {
        ft_list_airlines(list);
        ft_del_airlines(list);
    } else if (is_it_has(list->airline_fd, select)) {
        lseek(list->airline_fd, 0, SEEK_SET);
        int temp_fd = open("temp.csv", O_RDWR | O_CREAT, 0777);
        char *line = get_next_line(list->airline_fd);
        write(temp_fd, line, ft_strlen(line));
        char **result = ft_split(line, ',');
        free(line);
        while ((line = get_next_line(list->airline_fd))) {
            result = ft_split(line, ',');
            if (result[0] && ft_atoi(result[0]) != select) {
                write(temp_fd, line, ft_strlen(line));
            }
            free_split(result);
            free(line);
        }
        close(list->airline_fd);
        remove("airline.csv");
        rename("temp.csv", "airline.csv");
        list->airline_fd = open("airline.csv", O_RDWR);
        if (list->airline_fd == -1) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
        printf("Deleted successfully.\n");
    } else {
        printf("Wrong id\n");
    }
}

void ft_filter_airlines_bycountry(t_list *list)
{
    lseek(list->airline_fd, 0, SEEK_SET);
    int counter = 0;
    char country[50];
    printf("Enter airline country name:");
    scanf("%49s", country);
    char *line = get_next_line(list->airline_fd);
    line = get_next_line(list->airline_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0] && !ft_strcmp2(country,result[2]))
        {
            printf("Airline name: %s\n",result[1]);
            counter++;
        }
        line = get_next_line(list->airline_fd);
    }
    if (counter == 0)
    {
        printf("This country does not have an airline.\n");
    }
    lseek(list->airline_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}