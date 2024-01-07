#include "airport_management.h"

void ft_aircraft(t_list *list)
{
    while (1)
    {
        printf("Select operation\n");
        printf("1-)List all aircraft\n");
        printf("2-)Add aircraft\n");
        printf("3-)Dell aircraft\n");
        printf("4-)Aircraft capacity filter menu\n");
        printf("5-)Aircraft owned by airlines\n");
        printf("6-)Number of aircraft owned by airlines\n");
        printf("Enter 0 to return main menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_list_aircraft(list);

        }
        else if (select == 2)
        {
            system("clear");
            ft_add_aircraft(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_del_aircraft(list);
        }
        else if (select == 4)
        {
            system("clear");
            ft_filter_aircraft_capacity(list);
        }
        else if (select == 5)
        {
            system("clear");
            ft_find_airlines_aircraft(list, -1);
        }
        else if (select == 6)
        {
            system("clear");
            int ret = ft_find_airlines_aircraft(list, 0);
            if (ret != 0)
                printf("Number of aircraft owned: %d\n",ret);
        }
        else if (select == 0)
        {
            system("clear");
            break;
        }
        else
            printf("wrong input\n");
    }
}

void ft_airline(t_list *list)
{
    while (1)
    {
        printf("Select operation\n");
        printf("1-)List all alirlines\n");
        printf("2-)Add airline\n");
        printf("3-)Dell airline\n");
        printf("4-)List all airlines with country\n");
        printf("5-)Filter airlines by country\n");
        printf("Enter 0 to return main menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_list_airlines(list);

        }
        else if (select == 2)
        {
            system("clear");
            ft_add_airlines(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_del_airlines(list);
        }
        else if (select == 4)
        {
            system("clear");
            ft_list_airlines_country(list);
        }
        else if (select == 5)
        {
            system("clear");
            ft_filter_airlines_bycountry(list);
        }
        else if (select == 0)
        {
            system("clear");
            break;
        }
        else
            printf("wrong input\n");
    }
}

void ft_airport(t_list *list)
{
    while (1)
    {
        printf("Select operation\n");
        printf("1-)List all airports\n");
        printf("2-)Add airport\n");
        printf("3-)Dell airport\n");
        printf("4-)List all airports with cities and countries\n");
        printf("5-)Filter airport by city\n");
        printf("6-)Filter airport by country\n");
        printf("Enter 0 to return main menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_list_airport(list);

        }
        else if (select == 2)
        {
            system("clear");
            ft_add_airport(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_del_airport(list);
        }
        else if (select == 4)
        {
            system("clear");
            ft_list_all_airport(list);
        }
        else if (select == 5)
        {
            system("clear");
            ft_filter_airport_bycity(list);
        }
        else if (select == 6)
        {
            system("clear");
            ft_filter_airport_bycountry(list);
        }
        else if (select == 0)
        {
            system("clear");
            break;
        }
        else
            printf("wrong input\n");
    }
}

void ft_flight(t_list *list)
{
    while (1)
    {
        printf("Select operation\n");
        printf("1-)List all flight\n");
        printf("2-)Add flight\n");
        printf("3-)Dell flight\n");
        printf("4-)Finding flight by id\n");   
        printf("5-)Finding flight by aircraft\n");
        printf("6-)Finding flight by airline\n");
        printf("7-)Filter by departure date\n");
        printf("8-)Filter by landing date\n");
        printf("Enter 0 to return main menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_list_flight(list);

        }
        else if (select == 2)
        {
            system("clear");
            ft_add_flight(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_del_flight(list);
        }
        else if (select == 4)
        {
            system("clear");
            ft_find_flight_by_id(list,0);
        }
        else if (select == 5)
        {
            system("clear");
            ft_find_flight_by_aircraft(list, 0);
        }
        else if (select == 6)
        {
            system("clear");
            ft_find_flight_by_airline(list);
        }
        else if (select == 7)
        {
            system("clear");
            ft_filter_flight_date(list,0);
        }
        else if (select == 8)
        {
            system("clear");
            ft_filter_flight_date(list,1);
        }
        else if (select == 0)
        {
            system("clear");
            break;
        }
        else
            printf("wrong input\n");
    }
}

void ft_passenger(t_list *list)
{
    while (1)
    {
        printf("Select operation\n");
        printf("1-)List all passenger\n");
        printf("2-)Add passenger\n");
        printf("3-)Dell passenger\n");
        printf("4-)Finding passengers by id\n");        
        printf("Enter 0 to return main menu\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_list_passenger(list);

        }
        else if (select == 2)
        {
            system("clear");
            ft_add_passenger(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_del_passenger(list);
        }
        else if (select == 4)
        {
            system("clear");
            ft_find_passenger_by_id(list, 0, 1);
        }
        else if (select == 0)
        {
            system("clear");
            break;
        }
        else
            printf("wrong input\n");
    }
}

void ft_reservation(t_list *list)
{
    while (1)
    {
        printf("Select operation\n");
        printf("1-)List all reservation\n");
        printf("2-)Add reservation\n");
        printf("3-)Dell reservation\n");
        printf("4-)Update reservation info\n");
        printf("5-)Finding reservation by id\n");
        printf("6-)Finding reservation by flight\n");
        printf("7-)Filter by reservation date\n");
        printf("Enter 0 to return main menu\n");

        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_list_reservation(list);

        }
        else if (select == 2)
        {
            system("clear");
            ft_add_reservation(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_del_reservation(list, 0);
        }
        else if (select == 4)
        {
            system("clear");
            ft_update_reservation_by_id(list);
        }
        else if (select == 5)
        {
            system("clear");
            ft_find_reservation_by_id(list, 0);
        }
        else if (select == 6)
        {
            system("clear");
            ft_find_reservation_by_flight(list, 0);
        }
        else if (select == 7)
        {
            system("clear");
            ft_filter_reservation_date(list);
        }
        else if (select == 0)
        {
            system("clear");
            break;
        }
        else
            printf("wrong input\n");
    }
}




int main(void)
{
    t_list	*list;
    list = malloc (sizeof(t_list));
    
    system("clear");
    printf("Hi welcome database manegment.\n");
    list->aircraft_fd = open("aircraft.csv", O_RDWR);
    list->airline_fd = open("airline.csv", O_RDWR);
    list->airport_fd = open("airport.csv", O_RDWR);
    list->flight_fd = open("flight.csv", O_RDWR);
    list->passenger_fd = open("passenger.csv", O_RDWR);
    list->reservation_fd = open("reservation.csv", O_RDWR);
    //printf("%d %d %d %d %d %d", list->aircraft_fd, list->airline_fd, list->airport_fd, list->flight_fd, list->passenger_fd, list->reservation_fd);
    if (list->aircraft_fd < 0 || list->airline_fd < 0 || list->airport_fd < 0
        || list->flight_fd < 0 || list->passenger_fd < 0 || list->reservation_fd < 0)
    {
        printf("eksik ya da hatalı dosya ismi");
        return (0);
    }
    char id[50];
    char password[50];
    int cnt;
    while (1)
    {
        printf("Enter your id ");
        scanf("%49s", id);
        while (ft_strcmp("205", id) == 0)
        {
            printf("Enter your password ");
            scanf("%49s", password);
            if (ft_strcmp("Comp", password) == 0)
            {
                break;
            }
            else
            {
                printf("Your password is not correct\nIf you want try agin enter 0, if you don't want enter 1\n");
                scanf("%d", &cnt);
                if (cnt == 1)
                {
                    return (0);
                }
                system("clear");
            }
        }
        if (ft_strcmp("Comp", password) == 0)
        {
            break;
        }
        
        printf("Your id is not correct\nIf you want try agin enter 0 if you don't want enter 1\n");
        scanf("%d", &cnt);
            if (cnt == 1)
            {
                return (0);
            }
        system("clear");
    }
    system("clear");
    printf("Succesful\n");
    usleep(800000);
    system("clear");
    
    while (1)
    {
        //kendi printf'ini koy buraya
        printf("Select operation\n");
        printf("1-)Airlines operation\n");
        printf("2-)Aircraft operation\n");
        printf("3-)Airport operation\n");
        printf("4-)Flight operation\n");
        printf("5-)Passenger operation\n");
        printf("6-)Reservation operation\n");
        printf("Enter 0 to exit\n");
        int select;
        scanf("%d", &select);
        if (select == 1)
        {
            system("clear");
            ft_airline(list);
        }
        else if (select == 2)
        {
            system("clear");
            
            ft_aircraft(list);
        }
        else if (select == 3)
        {
            system("clear");
            ft_airport(list);
        }
        else if (select == 4)
        {
            system("clear");
            ft_flight(list);
        }
        else if (select == 5)
        {
            system("clear");
            ft_passenger(list);
        }
        else if (select == 6)
        {
            system("clear");
            ft_reservation(list);
        }
        else if (select == 0)
        {
            break;
        }
        else
        {
            system("clear");
            printf("Wrong input\n");
        }
    }
    close(list->aircraft_fd);
    close(list->airline_fd);
    close(list->airport_fd);
    close(list->flight_fd);
    close(list->passenger_fd);
    close(list->reservation_fd);
}