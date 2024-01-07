#include "airport_management.h"

void ft_list_flight(t_list *list)
{
    lseek(list->flight_fd, 0, SEEK_SET);
    char *line = get_next_line(list->flight_fd);
    line = get_next_line(list->flight_fd);
    char **result;
    char **timedep;
    char **timearr;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[5] && result[4] && result[3] && result[2] && result[1] && result[0])
        {
            timedep = ft_split(result[2], '/');
            timearr = ft_split(result[3], '/');
            printf("Flight id: %s\nDeparture airport name:", result[0]);
            ft_find_iata_print(list->airport_fd, result[4]);
            printf("Date: %s Time: %s\nArrival Airport name: ", timedep[0], timedep[1]);
            ft_find_iata_print(list->airport_fd, result[5]);
            printf("Date: %s Time: %s\nAircraft name: ", timearr[0], timearr[1]);
            ft_find_id_print(list->aircraft_fd, ft_atoi(result[1]));
            printf("\n");
        }
        line = get_next_line(list->flight_fd);
    }
    lseek(list->flight_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_add_flight(t_list *list)
{
    lseek(list->flight_fd, 0, SEEK_SET);
    int new_id;
    int aircraft_id;
    char departureTime[100];
    char arrivalTime[100];
    char departureAirport[100] = "0";
    char arrivalAirport[100] = "0";
    new_id = get_new_id(list->flight_fd);
    printf("Enter aircraft id, enter 0 to list ids: ");
    scanf("%d", &aircraft_id);
    if (aircraft_id == 0)
    {
        system("clear");
        ft_list_aircraft(list);
        ft_add_flight(list);
        return;
    }
    printf("Enter your departure time in this format (YYYY-MM-DD/HH:mm:ss)");
    scanf("%99s", departureTime);
    while (!ft_strcmp("0", departureAirport))
    {
        printf("Enter departure airport IATA, enter 0 to list IATA: ");
        scanf("%99s", departureAirport);
        system("clear");
        if (!ft_strcmp("0", departureAirport))
        {
                    ft_list_airport(list);
        }
    }
    printf("Enter your departure time in this format (YYYY-MM-DD/HH:mm:ss)");
    scanf("%99s", arrivalTime);
    while (!ft_strcmp("0", arrivalAirport))
    {
        printf("Enter departure airport IATA, enter 0 to list IATA: ");
        scanf("%99s", arrivalAirport);
        system("clear");
        if (!ft_strcmp("0", arrivalAirport))
        {
                    ft_list_airport(list);
        }
    }
    if (!is_it_has(list->aircraft_fd,aircraft_id))
    {
        printf("Wrong aircraft id!");
        return;
    }
    if (!is_it_has_char(list->airport_fd,departureAirport))
    {
        printf("Wrong departure airport IATA!");
        return;
    }
    if (!is_it_has_char(list->airport_fd,arrivalAirport))
    {
        printf("Wrong arrival airport IATA!");
        return;
    }
    char *arr[6] = {ft_itoa(new_id), ft_itoa(aircraft_id), departureTime, arrivalTime, departureAirport, arrivalAirport};
    ft_write_text(list->flight_fd, arr , 6);
    printf("Added successfully.\n");
    lseek(list->flight_fd, 0, SEEK_SET);
}

void ft_del_flight(t_list *list)
{
    lseek(list->flight_fd, 0, SEEK_SET);
    int select;
    printf("Enter flight id, enter 0 to list ids: ");
    scanf("%d", &select);
    if (select == 0) {
        ft_list_flight(list);
        ft_del_flight(list);
    } else if (is_it_has(list->flight_fd, select)) {
        lseek(list->flight_fd, 0, SEEK_SET);
        int temp_fd = open("temp.csv", O_RDWR | O_CREAT, 0777);
        char *line = get_next_line(list->flight_fd);
        write(temp_fd, line, ft_strlen(line));
        char **result = ft_split(line, ',');
        free(line);
        while ((line = get_next_line(list->flight_fd))) {
            result = ft_split(line, ',');
            if (result[0] && ft_atoi(result[0]) != select) {
                write(temp_fd, line, ft_strlen(line));
            }
            free_split(result);
            free(line);
        }
        close(list->flight_fd);
        remove("flight.csv");
        rename("temp.csv", "flight.csv");
        list->flight_fd = open("flight.csv", O_RDWR);
        if (list->flight_fd == -1) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
        printf("Deleted successfully.\n");
    } else {
        printf("Wrong id\n");
    }
}

void ft_find_flight_by_id(t_list *list, int boolean)
{
    lseek(list->flight_fd, 0, SEEK_SET);
    int id;
    int check = 0;
    char **timedep;
    char **timearr;
    id = boolean;
    if (!boolean)
    {
        printf("Enter flight id: ");
        scanf("%d", &id);
    }
    char *line = get_next_line(list->flight_fd);
    line = get_next_line(list->flight_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[5] && result[4] && result[3] && result[2] && result[1] && result[0] && ft_atoi(result[0]) == id)
        {
            timedep = ft_split(result[2], '/');
            timearr = ft_split(result[3], '/');
            printf("Departure airport name:");
            ft_find_iata_print(list->airport_fd, result[4]);
            printf("Date: %s Time: %s\nArrival Airport name: ", timedep[0], timedep[1]);
            ft_find_iata_print(list->airport_fd, result[5]);
            printf("Date: %s Time: %s\nAircraft name: ", timearr[0], timearr[1]);
            ft_find_id_print(list->aircraft_fd, ft_atoi(result[1]));
            printf("\n");
            check++;
        }
        line = get_next_line(list->flight_fd);
    }
    if (check == 0)
    {
        printf("Id did not match. Wrong id!\n");
    }
    if (!boolean)
    {
        lseek(list->flight_fd, 0, SEEK_SET);
    }
    free_split(result);
    if (line)
        free(line);
}

void ft_find_flight_by_aircraft(t_list *list, int boolean)
{
    int id;
    int check = 0;
    char **timedep;
    char **timearr;
    id = boolean;
    lseek(list->flight_fd, 0, SEEK_SET);
    if (!boolean)
    {
        printf("Enter aircraft id: ");
        scanf("%d", &id);
    }
    char *line = get_next_line(list->flight_fd);
    line = get_next_line(list->flight_fd);
    char **result;
    while (line)
    {
        result = ft_split(line, ',');
        if (result[5] && result[4] && result[3] && result[2] && result[1] && result[0] && ft_atoi(result[1]) == id)
        {
            timedep = ft_split(result[2], '/');
            timearr = ft_split(result[3], '/');
            printf("Departure airport name:");
            ft_find_iata_print(list->airport_fd, result[4]);
            printf("Date: %s Time: %s\nArrival Airport name: ", timedep[0], timedep[1]);
            ft_find_iata_print(list->airport_fd, result[5]);
            printf("Date: %s Time: %s\nAircraft name: ", timearr[0], timearr[1]);
            ft_find_id_print(list->aircraft_fd, ft_atoi(result[1]));
            printf("\n");
            check++;
        }
        line = get_next_line(list->flight_fd);
    }
    if (check == 0 && boolean == 0)
    {
        printf("Id did not match. Wrong id!\n");
    }
    lseek(list->flight_fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_find_flight_by_airline(t_list *list)
{
    int airlines;
    printf("Enter the owner of the aircraft id if you want to see the id of the airlines, enter 0:");
    scanf("%d", &airlines);
    if (airlines == 0) {
        ft_list_airlines(list);
        ft_find_flight_by_airline(list);
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
                ft_find_flight_by_aircraft(list, ft_atoi(result[0])); 
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
        printf("Wrong airline id\n");
    }
    return;
}

void ft_filter_greater_date(t_list *list, int fd, char *input, int i)
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
        date = ft_split(result[2+i],'-');
        if (result[5] && result[4] && result[3] && result[2] && result[1] && result[0] &&
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
        ft_find_flight_by_id(list, k[l]);
        printf("\n");
        l++;
    }
    if(j == 0)
    {
        printf("No matching flights found.");
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_less_date(t_list *list, int fd, char *input, int i)
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
        date = ft_split(result[2+i],'-');
        if (result[5] && result[4] && result[3] && result[2] && result[1] && result[0] &&
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
        ft_find_flight_by_id(list, k[l]);
        printf("\n");
        l++;
    }
    if(j == 0)
    {
        printf("No matching flights found.");
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_beetween_date(t_list *list, int fd, char *input, char *input2, int i)
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
        date = ft_split(result[2+i],'-');
        if (result[5] && result[4] && result[3] && result[2] && result[1] && result[0] &&
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
        ft_find_flight_by_id(list, k[l]);
        printf("\n");
        l++;
    }
    if(j == 0)
    {
        printf("No matching flights found.");
    }
    lseek(fd, 0, SEEK_SET);
    free_split(result);
    if (line)
        free(line);
}

void ft_filter_flight_date(t_list *list, int i)
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
            ft_filter_greater_date(list,list->flight_fd, date1, i);

        }
        else if (select == 2)
        {
            system("clear");
            char date1[50];
            printf("Date is (YYYY-MM-DD):");
            scanf("%49s", date1);
            ft_filter_less_date(list, list->flight_fd, date1, i);
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
            ft_filter_beetween_date(list, list->flight_fd, date1, date2, i);
        }
        else if (select == 0)
        {
            system("clear");
            return;
        }
        else{
            printf("wrong input\n");
            ft_filter_flight_date(list, i);
        }
}
