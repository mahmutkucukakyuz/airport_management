#include "airport_management.h"
#include <stdio.h>


void ft_list_reservation(t_list *list)
{
    lseek(list->reservation_fd, 0, SEEK_SET);
    char *line = get_next_line(list->reservation_fd);
    line = get_next_line(list->reservation_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[4] && result[3] && result[2] && result[1] && result[0])
        {
            printf("Reservation id: %s\n", result[0]);
            ft_find_passenger_by_id(list, ft_atoi(result[1]),1);
            printf("Flight id: %s\nSeat number: %s\nReservation date: %s", result[2], result[3], result[4]);
            printf("\n");
        }
        line = get_next_line(list->reservation_fd);
    }
    lseek(list->reservation_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_add_reservation(t_list *list)
{
    lseek(list->reservation_fd, 0, SEEK_SET);
    int output;
    int fd;
    char seat_number[10];
    char reservation_date[11];
    int passenger_id;
    int flight_id = 0;
    int new_id;
    int select;
    time_t current_time;
    struct tm *local_time;
    current_time = time(NULL);
    local_time = localtime(&current_time);
    strftime(reservation_date, sizeof(reservation_date), "%Y-%m-%d", local_time);
    printf("If the passenger is registered, enter his ID.\n");
    printf("If the passenger is registered but does not know his ID, enter 0.\n");
    printf("If the passenger is not registered, enter -1.\n");
    scanf("%d", &select);
    if (select == 0)
    {
        system("clear");
        ft_list_passenger(list);
        ft_add_reservation(list);
        return;
    }
    else if (select == -1)
    {
        system("clear");
        ft_add_passenger(list);
        ft_add_reservation(list);
        return;
    }
    else if (is_it_has(list->passenger_fd,select))
    {
        passenger_id = select;
    }
    else
    {
        printf("Wrong input");
        return;
    }
    while (flight_id == 0)
    {
        printf("Enter your flight ID. If you do not know, enter 0.\n");
        scanf("%d", &flight_id);
        system("clear");
        if (flight_id == 0)
        {
                    ft_list_flight(list);
        }
    }
    printf("Enter seat number: ");
    scanf("%9s", seat_number);

    new_id = get_new_id(list->reservation_fd);
    char *arr[5] = {ft_itoa(new_id),ft_itoa(passenger_id),ft_itoa(flight_id), seat_number, reservation_date};
    ft_write_text(list->reservation_fd, arr , 5);
    printf("If you want to print the reservation information as a txt file, enter 1; otherwise, enter 0.\n");
    scanf("%d", &output);
    if (output == 1)
    {
        fd = open(ft_strjoin(ft_strjoin(ft_itoa(new_id), reservation_date), ".txt"), O_WRONLY | O_CREAT , 0777);
        dprintf(fd, "Reservation id: %d\n", new_id);
        ft_find_passenger_by_id(list, passenger_id,fd);
        dprintf(fd, "Flight id: %d\nSeat number: %s\nReservation date: %s", flight_id, seat_number, reservation_date);
    }
    printf("Added successfully.\n");
    lseek(list->reservation_fd, 0, SEEK_SET);
}


void ft_del_reservation(t_list *list, int i)
{
    lseek(list->reservation_fd, 0, SEEK_SET);
    int select;
    select = i;
    if (i == 0)
    {
        printf("Enter reservation id, enter 0 to list ids: ");
        scanf("%d", &select);
    }
    if (select == 0) {
        ft_list_reservation(list);
        ft_del_reservation(list, 0);
    } else if (is_it_has(list->reservation_fd, select)) {
        lseek(list->reservation_fd, 0, SEEK_SET);
        int temp_fd = open("temp.csv", O_RDWR | O_CREAT, 0777);
        char *line = get_next_line(list->reservation_fd);
        write(temp_fd, line, ft_strlen(line));
        char **result = ft_split(line, ',');
        free(line);
        while ((line = get_next_line(list->reservation_fd))) {
            result = ft_split(line, ',');
            if (result[0] && ft_atoi(result[0]) != select) {
                write(temp_fd, line, ft_strlen(line));
            }
            free_split(result);
            free(line);
        }
        close(list->reservation_fd);
        remove("reservation.csv");
        rename("temp.csv", "reservation.csv");
        list->reservation_fd = open("reservation.csv", O_RDWR);
        if (list->reservation_fd == -1) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
        printf("Deleted successfully.\n");
    } else {
        printf("Wrong id\n");
    }
}

void ft_update_reservation_by_id(t_list *list)
{
    int id;
    printf("Enter reservation id: ");
    scanf("%d", &id);
    if (is_it_has(list->reservation_fd, id))
    {
        ft_del_reservation(list, id);
        ft_add_reservation(list);
    }
    else
        printf("Wrong id!");
}

void ft_find_reservation_by_id(t_list *list, int i)
{
    lseek(list->reservation_fd, 0, SEEK_SET);
    int id;
    int check = 0;
    id = i;
    if(i == 0){
        printf("Enter reservation id: ");
        scanf("%d", &id);
    }
    char *line = get_next_line(list->reservation_fd);
    line = get_next_line(list->reservation_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[4] && result[3] && result[2] && result[1] && result[0] && ft_atoi(result[0]) == id)
        {
            printf("Reservation id: %s\n", result[0]);
            ft_find_passenger_by_id(list, ft_atoi(result[1]),1);
            printf("Flight id: %s\nSeat number: %s\nReservation date: %s", result[2], result[3], result[4]);
            check++;
        }
        line = get_next_line(list->reservation_fd);
    }
    if (check == 0)
    {
        printf("Id did not match. Wrong id!\n");
    }
    lseek(list->reservation_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_find_reservation_by_flight(t_list *list, int i)
{
    lseek(list->reservation_fd, 0, SEEK_SET);
    int id;
    int check = 0;
    id = i;
    while (id == 0)
    {
        printf("Enter your flight ID. If you do not know, enter 0.\n");
        scanf("%d", &id);
        system("clear");
        if (id == 0)
        {
                    ft_list_flight(list);
        }
    }
    char *line = get_next_line(list->reservation_fd);
    line = get_next_line(list->reservation_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[4] && result[3] && result[2] && result[1] && result[0] && ft_atoi(result[2]) == id)
        {
            printf("Reservation id: %s\n", result[0]);
            ft_find_passenger_by_id(list, ft_atoi(result[1]),1);
            printf("Flight id: %s\nSeat number: %s\nReservation date: %s", result[2], result[3], result[4]);
            check++;
        }
        line = get_next_line(list->reservation_fd);
    }
    if (check == 0)
    {
        printf("Id did not match. Wrong id!\n");
    }
    lseek(list->reservation_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_greater_res_date(t_list *list, int fd, char *input)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    int k[100];
    int j = 0;
    char **date_in = ft_split(input, '-');
    char **result;
    char **date;
    while (line)
    {
        result = ft_split(line, ',');
        date = ft_split(result[4],'-');
        if (result[4] && result[3] && result[2] && result[1] && result[0] &&
             (ft_atoi(date[0]) > ft_atoi(date_in[0]) || (ft_atoi(date[0]) == ft_atoi(date_in[0]) && ft_atoi(date[1]) > ft_atoi(date_in[1])) || 
             (ft_atoi(date[0]) == ft_atoi(date_in[0]) && ft_atoi(date[1]) == ft_atoi(date_in[1]) && ft_atoi(date[1]) > ft_atoi(date_in[1]))))
        {
            k[j++]= ft_atoi(result[0]);
        }
        line = get_next_line(fd);
    }
    int l = 0;
    while (l < j)
    {
        ft_find_reservation_by_id(list, k[l]);
        printf("\n");
        l++;
    }
    if(j == 0)
    {
        printf("No matching reservation found.");
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_less_res_date(t_list *list, int fd, char *input)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    int k[100];
    int j = 0;
    char **date_in = ft_split(input, '-');
    char **result;
    char **date;
    while (line)
    {
        result = ft_split(line, ',');
        date = ft_split(result[4],'-');
        if (result[4] && result[3] && result[2] && result[1] && result[0] &&
             (ft_atoi(date[0]) < ft_atoi(date_in[0]) || (ft_atoi(date[0]) == ft_atoi(date_in[0]) && ft_atoi(date[1]) < ft_atoi(date_in[1])) || 
             (ft_atoi(date[0]) == ft_atoi(date_in[0]) && ft_atoi(date[1]) == ft_atoi(date_in[1]) && ft_atoi(date[1]) < ft_atoi(date_in[1]))))
        {
            k[j++]= ft_atoi(result[0]);
        }
        line = get_next_line(fd);
    }
    int l = 0;
    while (l < j)
    {
        ft_find_reservation_by_id(list, k[l]);
        printf("\n");
        l++;
    }
    if(j == 0)
    {
        printf("No matching reservation found.");
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_beetween_res_date(t_list *list, int fd, char *input, char *input2)
{
    lseek(fd, 0, SEEK_SET);
    char *line = get_next_line(fd);
    line = get_next_line(fd);
    int k[100];
    int j = 0;
    char **date_in2 = ft_split(input, '-');
    char **date_in = ft_split(input2, '-');
    char **result;
    char **date;
    while (line)
    {
        result = ft_split(line, ',');
        date = ft_split(result[4],'-');
        if (result[4] && result[3] && result[2] && result[1] && result[0] &&
             (ft_atoi(date[0]) < ft_atoi(date_in[0]) || (ft_atoi(date[0]) == ft_atoi(date_in[0]) && ft_atoi(date[1]) < ft_atoi(date_in[1])) || 
             (ft_atoi(date[0]) == ft_atoi(date_in[0]) && ft_atoi(date[1]) == ft_atoi(date_in[1]) && ft_atoi(date[1]) < ft_atoi(date_in[1]))) && 
             (ft_atoi(date[0]) > ft_atoi(date_in2[0]) || (ft_atoi(date[0]) == ft_atoi(date_in2[0]) && ft_atoi(date[1]) > ft_atoi(date_in2[1])) || 
             (ft_atoi(date[0]) == ft_atoi(date_in2[0]) && ft_atoi(date[1]) == ft_atoi(date_in2[1]) && ft_atoi(date[1]) > ft_atoi(date_in2[1]))))
        {
            k[j++]= ft_atoi(result[0]);
        }
        line = get_next_line(fd);
    }
    int l = 0;
    while (l < j)
    {
        ft_find_reservation_by_id(list, k[l]);
        printf("\n");
        l++;
    }
    if(j == 0)
    {
        printf("No matching reservation found.");
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_reservation_date(t_list *list)
{
    printf("Select operation\n");
        printf("1-)After this date\n");
        printf("2-)Before this date\n");
        printf("3-)Between these dates\n");
        printf("Enter 0 to return previous menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            char date1[50];
            printf("Date is (YYYY-MM-DD):");
            scanf("%49s", date1);
            ft_filter_greater_res_date(list,list->reservation_fd, date1);

        }
        else if (select == 2)
        {
            system("clear");
            char date1[50];
            printf("Date is (YYYY-MM-DD):");
            scanf("%49s", date1);
            ft_filter_less_res_date(list, list->reservation_fd, date1);
        }
        else if (select == 3)
        {
            system("clear");
            char date1[50];
            char date2[50];
            printf("Starting date is (YYYY-MM-DD):");
            scanf("%49s", date1);
            printf("Ending date is (YYYY-MM-DD):");
            scanf("%49s", date2);
            ft_filter_beetween_res_date(list, list->reservation_fd, date1, date2);
        }
        else if (select == 0)
        {
            system("clear");
            return;
        }
        else{
            printf("wrong input\n");
            ft_filter_reservation_date(list);
        }
}