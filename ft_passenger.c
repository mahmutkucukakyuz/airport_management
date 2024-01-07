#include "airport_management.h"

void ft_list_passenger(t_list *list)
{
    lseek(list->passenger_fd, 0, SEEK_SET);
    char *line = get_next_line(list->passenger_fd);
    line = get_next_line(list->passenger_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[2] && result[1] && result[0])
        {
            printf("ID: %s Passenger name: %s surname: %s", result[0],result[1],result[2]);
        }
        line = get_next_line(list->passenger_fd);
    }
    printf("\n");
    lseek(list->passenger_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_add_passenger(t_list *list)
{
    lseek(list->passenger_fd, 0, SEEK_SET);
    char name[50];
    char surname[50];
    int new_id;
    printf("Enter passenger name: ");
    scanf("%49s", name);
    printf("Enter passenger surname: ");
    scanf("%49s", surname);
    new_id = get_new_id(list->passenger_fd);
    char *arr[3] = {ft_itoa(new_id), name, surname};
    ft_write_text(list->passenger_fd, arr , 3);
    printf("Added successfully.\n");
    lseek(list->passenger_fd, 0, SEEK_SET);
}

void ft_del_passenger(t_list *list)
{
    lseek(list->passenger_fd, 0, SEEK_SET);
    int select;
    printf("Enter passenger id, enter 0 to list ids: ");
    scanf("%d", &select);
    if (select == 0) {
        ft_list_passenger(list);
        ft_del_passenger(list);
    } else if (is_it_has(list->passenger_fd, select)) {
        lseek(list->passenger_fd, 0, SEEK_SET);
        int temp_fd = open("temp.csv", O_RDWR | O_CREAT, 0777);
        char *line = get_next_line(list->passenger_fd);
        write(temp_fd, line, ft_strlen(line));
        char **result = ft_split(line, ',');
        free(line);
        while ((line = get_next_line(list->passenger_fd))) {
            result = ft_split(line, ',');
            if (result[0] && ft_atoi(result[0]) != select) {
                write(temp_fd, line, ft_strlen(line));
            }
            free_split(result);
            free(line);
        }
        close(list->passenger_fd);
        remove("passenger.csv");
        rename("temp.csv", "passenger.csv");
        list->passenger_fd = open("passenger.csv", O_RDWR);
        if (list->passenger_fd == -1) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
        printf("Deleted successfully.\n");
    } else {
        printf("Wrong id\n");
    }
}

void ft_find_passenger_by_id(t_list *list, int i, int fd)
{
    lseek(list->passenger_fd, 0, SEEK_SET);
    int id;
    int check = 0;
    id = i;
    if(i == 0){
        printf("Enter passenger id: ");
        scanf("%d", &id);
    }
    char *line = get_next_line(list->passenger_fd);
    line = get_next_line(list->passenger_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[2] && result[1] && result[0] && ft_atoi(result[0]) == id)
        {
            dprintf(fd,"Passenger name: %s surname: %s", result[1],result[2]);
            check++;
        }
        line = get_next_line(list->passenger_fd);
    }
    if (check == 0)
    {
        dprintf(fd,"Id did not match. Wrong id!\n");
    }
    lseek(list->passenger_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}
