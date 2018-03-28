#include "robot_simulator.h"
#include <stdio.h>

robot_grid_status_t robot_init(void)
{
    robot_grid_status_t robot;
    robot.bearing = DEFAULT_BEARING;
    robot.grid.x_position = DEFAULT_X_COORDINATE;
    robot.grid.y_position = DEFAULT_Y_COORDINATE;
    return robot;
}

robot_grid_status_t robot_init_with_position(int bearing, int x, int y)
{
    robot_grid_status_t robot;
    if (bearing < HEADING_MAX) {
        robot.bearing = bearing;
    }
    else {
        robot.bearing = DEFAULT_BEARING;
    }
    robot.grid.x_position = x;
    robot.grid.y_position = y;
    return robot;
}

void robot_turn_right(robot_grid_status_t * robot)
{
    robot->bearing = (robot->bearing + 1) % HEADING_MAX;
}

void robot_turn_left(robot_grid_status_t * robot) {
    robot->bearing = (robot->bearing - 1) % HEADING_MAX;
}

void robot_advance(robot_grid_status_t * robot)
{
    switch(robot->bearing) {
        case HEADING_NORTH:
        robot->grid.y_position++;
        break;
        
        case HEADING_EAST:
        robot->grid.x_position++;
        break;
        
        case HEADING_SOUTH:
        robot->grid.y_position--;
        break;
        
        case HEADING_WEST:
        robot->grid.x_position--;
        break;
        
        case HEADING_MAX:
        fprintf(stderr, "Invalid bearing: HEADING_MAX");
    }
}

void robot_simulator(robot_grid_status_t * robot, const char *commands)
{
    for (int i = 0; commands[i]; i++) {
        switch (commands[i]) {
            case 'L':
            robot_turn_left(robot);
            break;
            
            case 'R':
            robot_turn_right(robot);
            break;
            
            case 'A':
            robot_advance(robot);
        }
    }
}