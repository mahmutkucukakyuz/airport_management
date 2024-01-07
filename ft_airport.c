#include "airport_management.h"

void ft_list_airport(t_list *list)
{
    lseek(list->airport_fd, 0, SEEK_SET);
    char *line = get_next_line(list->airport_fd);
    line = get_next_line(list->airport_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0])
        {
            printf("IATA: %s Airport name: %s\n", result[0],result[1]);
        }
        line = get_next_line(list->airport_fd);
    }
    lseek(list->airport_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_list_all_airport(t_list *list)
{
    lseek(list->airport_fd, 0, SEEK_SET);
    char *line = get_next_line(list->airport_fd);
    line = get_next_line(list->airport_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[3] && result[2] && result[1] && result[0])
        {
            printf("IATA: %s Airport name: %s City: %s Country: %s", result[0],result[1], result[2], result[3]);
        }
        line = get_next_line(list->airport_fd);
    }
    printf("\n");
    lseek(list->airport_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_airport_bycity(t_list *list)
{
    lseek(list->airport_fd, 0, SEEK_SET);
    int counter = 0;
    char city[50];
    printf("Enter airport city name:");
    scanf("%49s", city);
    char *line = get_next_line(list->airport_fd);
    line = get_next_line(list->airport_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[3] && result[2] && result[1] && result[0] && !ft_strcmp2(city,result[2]))
        {
            printf("Airport name: %s\n",result[1]);
            counter++;
        }
        line = get_next_line(list->airport_fd);
    }
    if (counter == 0)
    {
        printf("This city does not have an airport.\n");
    }
    lseek(list->airport_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_airport_bycountry(t_list *list)
{
    lseek(list->airport_fd, 0, SEEK_SET);
    int counter = 0;
    char country[50];
    printf("Enter airport country name:");
    scanf("%49s", country);
    char *line = get_next_line(list->airport_fd);
    line = get_next_line(list->airport_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[3] && result[2] && result[1] && result[0] && !ft_strcmp2(country,result[3]))
        {
            printf("Airporte name: %s\n",result[1]);
            counter++;
        }
        line = get_next_line(list->airport_fd);
    }
    if (counter == 0)
    {
        printf("This country does not have an airport.\n");
    }
    lseek(list->airport_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_add_airport(t_list *list)
{
    lseek(list->airport_fd, 0, SEEK_SET);
    char iata[50];
    char name[50];
    char city[50];
    char country[50];
    printf("Enter IATA: ");
    scanf("%49s", iata);
    printf("Enter airport name: ");
    scanf("%49s", name);
    printf("Enter city name: ");
    scanf("%49s", city);
    printf("Enter country name: ");
    scanf("%49s", country);
    char *arr[4] = {iata, name, city, country};
    ft_write_text(list->airport_fd, arr , 4);
    printf("Added successfully.\n");
    lseek(list->airport_fd, 0, SEEK_SET);
}

void ft_del_airport(t_list *list)
{
    lseek(list->airport_fd, 0, SEEK_SET);
    char select[50];
    printf("Enter airport IATA, enter 0 to list IATAs: ");
    scanf("%s", select);
    if (!ft_strcmp2(select, "0")) {
        ft_list_airport(list);
        ft_del_airport(list);
    } else if (is_it_has_char(list->airport_fd, select)) {
        lseek(list->airport_fd, 0, SEEK_SET);
        int temp_fd = open("temp.csv", O_RDWR | O_CREAT, 0777);
        char *line = get_next_line(list->airport_fd);
        write(temp_fd, line, ft_strlen(line));
        char **result = ft_split(line, ',');
        free(line);
        while ((line = get_next_line(list->airport_fd))) {
            result = ft_split(line, ',');
            if (result[0] && ft_strcmp2(select, result[0])) {
                write(temp_fd, line, ft_strlen(line));
            }
            free_split(result);
            free(line);
        }
        close(list->airport_fd);
        remove("airport.csv");
        rename("temp.csv", "airport.csv");
        list->airport_fd = open("airport.csv", O_RDWR);
        if (list->airport_fd == -1) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
        printf("Deleted successfully.\n");
    } else {
        printf("Wrong id\n");
    }
}