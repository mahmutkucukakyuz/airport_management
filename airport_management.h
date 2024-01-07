#ifndef AIRPROT_MANAGEMENT_H
# define AIRPROT_MANAGEMENT_H

#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "fcntl.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <time.h>


typedef struct s_list
{
	int aircraft_fd;
    int airline_fd;
    int airport_fd;
    int flight_fd;
    int passenger_fd;
    int reservation_fd;
}		t_list;

void free_split(char **split);
void ft_find_id_print(int fd, int id);
void ft_find_iata_print(int fd, char *id);
void ft_add_aircraft(t_list *list);
void ft_list_airlines(t_list *list);
void ft_list_aircraft(t_list *list);
void ft_del_aircraft(t_list *list);
void ft_list_airlines_country(t_list *list);
void ft_filter_aircraft_capacity(t_list *list);
void ft_filter_airlines_bycountry(t_list *list);
void ft_add_airlines(t_list *list);
void ft_del_airlines(t_list *list);
void ft_list_passenger(t_list *list);
void ft_find_passenger_by_id(t_list *list, int i, int fd);
void ft_add_passenger(t_list *list);
void ft_del_passenger(t_list *list);
void ft_list_all_airport(t_list *list);
void ft_filter_airport_bycountry(t_list *list);
void ft_filter_airport_bycity(t_list *list);
void ft_list_airport(t_list *list);
void ft_add_airport(t_list *list);
void ft_del_airport(t_list *list);
void ft_list_flight(t_list *list);
void ft_del_flight(t_list *list);
void ft_find_flight_by_id(t_list *list, int boolean);
void ft_find_flight_by_aircraft(t_list *list, int boolean);
void ft_add_flight(t_list *list);
void ft_filter_flight_date(t_list *list, int i);
void ft_find_flight_by_airline(t_list *list);
void ft_list_reservation(t_list *list);
void ft_add_reservation(t_list *list);
void ft_del_reservation(t_list *list, int i);
void ft_find_reservation_by_id(t_list *list, int i);
void ft_filter_reservation_date(t_list *list);
void ft_find_reservation_by_flight(t_list *list, int i);
void ft_update_reservation_by_id(t_list *list);
int is_it_has(int fd, int select);
int is_it_has_char(int fd, char *select);
int get_new_id(int fd);
int match_id(int fd, char input_string[50], int id_col, int source_col);
int ft_find_airlines_aircraft(t_list *list, int a);
void ft_write_text(int fd, char **a, int i);

#endif
