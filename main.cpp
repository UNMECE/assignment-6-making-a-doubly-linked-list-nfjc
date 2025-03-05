//Including proper libraries and dependencies.
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "coordinate.h"

int main(int argc, char *argv[]) {
    int num_coords = 10;  // Set fixed number of coordinates because sometimes it wouldn't run.

    if (num_coords <= 0) {
        std::cout << "Gotta give me a number above zero." << std::endl;
        return 1;
    }
//Creating the actual linked llist to bbe used throughout my code.
    Coordinate *list_head = new Coordinate;
    list_head->next = nullptr;
    list_head->previous = nullptr;
//Making sure the numbers are different every time its ran.
    srand(time(0));
//Filling the list with random numbers.
    for (int i = 0; i < num_coords; i++) {
        float x = rand() % 100;
        float y = rand() % 100;
        add_coordinate(list_head, x, y);
    }
	//Creating the output and making it look pretty :).
    std::cout << "Coordinates forward:" << std::endl;
    forward_display(list_head);

    std::cout << "Coordinates backward:" << std::endl;
    backward_display(list_head);

    std::cout << "Coordinate closest to (50, 50): ";
    closest_to(list_head, 50.0f, 50.0f);

    int length = list_length(list_head);
    std::cout << "List length = " << length << "." << std::endl;


    int deleter = (rand() % list_length(list_head)) + 1;
    std::cout << "Deleting coordinate ID " << deleter << "." << std::endl;
    delete_coordinate(list_head, deleter);

    std::cout << "Coordinates after deleting ID " << deleter << ":" << std::endl;
    forward_display(list_head);
}

// Function to add a coordinate to the end of the list.
void add_coordinate(Coordinate *list_end, float x, float y) {
    while (list_end->next != nullptr) { //Making sure we're at the last node
        list_end = list_end->next;
    }

    Coordinate *new_coord = new Coordinate;
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = list_end->coord_id + 1;  //This is how I increment the next and previous pointers when a new coordinate is added.
    new_coord->next = nullptr;
    new_coord->previous = list_end;

    list_end->next = new_coord;
}


// Function to display coordinates from beginning to end
void forward_display(Coordinate *list_beginning) {
    Coordinate *current = list_beginning->next; // Skip the dummy head
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id << " | x: " << current->x << " | y: " << current->y << std::endl;
        current = current->next;
    }
}

// Function to display coordinates from end to beginning
void backward_display(Coordinate *list_end) {
    while (list_end->next != nullptr) {
        list_end = list_end->next;
    }
    while (list_end->previous != nullptr) {
        std::cout << "ID: " << list_end->coord_id << " | x: " << list_end->x << " | y: " << list_end->y << std::endl;
        list_end = list_end->previous;
    }
}

// Function to delete a coordinate by its ID
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete) {
    Coordinate *current = list_beginning->next;
//Making sure we aren;t at the end of the list.
    while (current != nullptr) {
        if (current->coord_id == coord_id_to_delete) {
            if (current->previous != nullptr) {
                current->previous->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->previous = current->previous;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

// Function to get the length of the list
int list_length(Coordinate *list_beginning) {
//Just incrememnts an int and 
    int length = 0;
    Coordinate *current = list_beginning->next;
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    return length;
}

// Function to find the closest coordinate to the given x, y point
void closest_to(Coordinate *list_beginning, float x, float y) {
    Coordinate *current = list_beginning->next;
    float min_distance = INFINITY;
    Coordinate *closest = nullptr;

    while (current != nullptr) {
        float distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest = current;
        }
        current = current->next;
    }

    if (closest != nullptr) {
        std::cout << "Closest Coordinate ID: " << closest->coord_id << " | x: " << closest->x << " | y: " << closest->y
                  << " | Distance: " << min_distance;
    }
}

