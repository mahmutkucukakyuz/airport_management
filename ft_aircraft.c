#include "airport_management.h"

int ft_find_airlines_aircraft(t_list *list, int a)
{
    int airlines;
    int i = 0;
    printf("Enter the owner of the aircraft id if you want to see the id of the airlines, enter 0:");
    scanf("%d", &airlines);
    if (airlines == 0) {
        ft_list_airlines(list);
        i = ft_find_airlines_aircraft(list, a);
    }
    else if (is_it_has(list->airline_fd, airlines)){
        system("clear");
        ft_find_id_print(list->airline_fd, airlines);
        printf("\n");
        char *line = get_next_line(list->aircraft_fd);
        char **result = ft_split(line, ',');
        while (line)
        {
            result = ft_split(line, ',');
            if (result[0] && airlines == ft_atoi(result[3]))
            {
                if (a == -1)
                    printf("%s\n", result[1]);
                else
                    i++;
            }
            line = get_next_line(list->aircraft_fd);
        }
        lseek(list->aircraft_fd, 0, SEEK_SET);
        lseek(list->airline_fd, 0, SEEK_SET);
        free_split(result);
        if (line)
            free(line);
    }
    else 
    {
        printf("Wrong id\n");
    }
    return(i);
}

void ft_add_aircraft(t_list *list)
{
    char name[50];
    char airlines[50];
    int capacity;
    int new_id;
    printf("Enter aircraft name:");
    scanf("%49s", name);
    printf("Enter aircraft capacity:");
    scanf("%d", &capacity);
    printf("Enter the owner of the aircraft:");
    scanf("%49s", airlines);
    new_id = get_new_id(list->aircraft_fd);
    int airlines_id = 0;
    airlines_id = match_id(list->airline_fd, airlines, 0, 1);
    if (airlines_id)
    {
        char *arr[4] = {ft_itoa(new_id), name, ft_itoa(capacity), ft_itoa(airlines_id)};
        ft_write_text(list->aircraft_fd, arr , 4);
        printf("Added successfully.\n");
    }
    else
    {
        system("clear");
        printf("Wrong airlines name\n");
    }
    lseek(list->aircraft_fd, 0, SEEK_SET);
}

// void ft_list(int fd, int *i)
// {
//     lseek(fd, 0, SEEK_SET);
//     char *line = get_next_line(fd);
//     line = get_next_line(fd);
//     char **result;
//     while (line)
//     {
//         result = ft_split(line, ',');
//         if (result[1] && result[0])
//         {
//             printf("%s %s\n", result[0],result[1]);
//         }
//         line = get_next_line(fd);
//     }
//     lseek(fd, 0, SEEK_SET);
//     free_split(result);
//     if (line)
//         free(line);
// }

void ft_list_aircraft(t_list *list)
{
    lseek(list->aircraft_fd, 0, SEEK_SET);
    char *line = get_next_line(list->aircraft_fd);
    line = get_next_line(list->aircraft_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[1] && result[0])
        {
            printf("ID: %s Model name: %s\n", result[0],result[1]);
        }
        line = get_next_line(list->aircraft_fd);
    }
    lseek(list->aircraft_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_del_aircraft(t_list *list) {
    lseek(list->aircraft_fd, 0, SEEK_SET);
    int select;
    printf("Enter aircraft id, enter 0 to list ids: ");
    scanf("%d", &select);
    if (select == 0) {
        ft_list_aircraft(list);
        ft_del_aircraft(list);
    } else if (is_it_has(list->aircraft_fd, select)) {
        lseek(list->aircraft_fd, 0, SEEK_SET);
        int temp_fd = open("temp.csv", O_RDWR | O_CREAT, 0777);
        char *line = get_next_line(list->aircraft_fd);
        write(temp_fd, line, ft_strlen(line));
        char **result = ft_split(line, ',');
        free(line);
        while ((line = get_next_line(list->aircraft_fd))) {
            result = ft_split(line, ',');
            if (result[0] && ft_atoi(result[0]) != select) {
                write(temp_fd, line, ft_strlen(line));
            }
            free_split(result);
            free(line);
        }
        close(list->aircraft_fd);
        remove("aircraft.csv");
        rename("temp.csv", "aircraft.csv");
        list->aircraft_fd = open("aircraft.csv", O_RDWR);
        if (list->aircraft_fd == -1) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
        printf("Deleted successfully.\n");
    } else {
        printf("Wrong id\n");
    }
}

void ft_filter_greater_than(int fd, int num)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[2] && result[1] && ft_atoi(result[2]) > num)
        {
            printf("Aircraft name: %s, Capacity: %s\n", result[1], result[2]);
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_less_than(int fd, int num)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[2] && result[1] && ft_atoi(result[2]) < num)
        {
            printf("Aircraft name: %s, Capacity: %s\n", result[1], result[2]);
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_beetween(int fd, int num1, int num2)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[2] && result[1] && ft_atoi(result[2]) > num1 && ft_atoi(result[2]) < num2)
        {
            printf("Aircraft name: %s, Capacity: %s\n", result[1], result[2]);
        }
        line = get_next_line(fd);
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}



void ft_filter_aircraft_capacity(t_list *list)
{
    printf("Select operation\n");
        printf("1-)Values greater than\n");
        printf("2-)Values less than\n");
        printf("3-)Values between\n");
        printf("Enter 0 to return previous menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            int num1;
            printf("Greater than ");
            scanf("%d", &num1);
            ft_filter_greater_than(list->aircraft_fd, num1);

        }
        else if (select == 2)
        {
            system("clear");
            int num1;
            printf("Less than ");
            scanf("%d", &num1);
            ft_filter_less_than(list->aircraft_fd, num1);
        }
        else if (select == 3)
        {
            system("clear");
            int num1;
            int num2;
            printf("Lower limit: ");
            scanf("%d", &num1);
            printf("Upper limit: ");
            scanf("%d", &num2);
            ft_filter_beetween(list->aircraft_fd, num1, num2);
        }
        else if (select == 0)
        {
            system("clear");
            return;
        }
        else{
            printf("wrong input\n");
            ft_filter_aircraft_capacity(list);
        }
}
