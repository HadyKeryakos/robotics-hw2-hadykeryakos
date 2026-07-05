#include "fleet.hpp"
#include "mobile_robot.hpp"
#include "cleaning_robot.hpp"
#include "cooking_robot.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

void clear_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int read_int(const std::string& prompt)
{
    int value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin) {
            return value;
        }

        std::cout << "Invalid number. Try again.\n";
        clear_input();
    }
}

double read_double(const std::string& prompt)
{
    double value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin) {
            return value;
        }

        std::cout << "Invalid number. Try again.\n";
        clear_input();
    }
}

std::string read_string(const std::string& prompt)
{
    std::string value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

void print_menu()
{
    std::cout << "\n=== Robot Fleet Manager ===\n";
    std::cout << "1. Add robot\n";
    std::cout << "2. Remove robot\n";
    std::cout << "3. Show all robots\n";
    std::cout << "4. Work single robot\n";
    std::cout << "5. Work all\n";
    std::cout << "6. Charge all\n";
    std::cout << "7. Assign task to robot\n";
    std::cout << "8. Show task queue\n";
    std::cout << "9. Start timed work on a mobile robot\n";
    std::cout << "10. Show first robot below 20% battery\n";
    std::cout << "11. Show first robot that is currently working\n";
    std::cout << "0. Exit\n";
}

int main()
{
    Fleet fleet;

    // Extra vector only for the std::find_if homework requirement.
    // Fleet still owns/stores the robots in its internal unordered_map.
    std::vector<std::shared_ptr<Robot>> robot_list;

    bool running = true;

    while (running) {
        print_menu();

        int choice = read_int("Choose option: ");

        try {
            if (choice == 1) {
                std::cout << "\nRobot type:\n";
                std::cout << "1. MobileRobot\n";
                std::cout << "2. CleaningRobot\n";
                std::cout << "3. CookingRobot\n";

                int type = read_int("Choose robot type: ");

                std::string id = read_string("Enter id: ");
                std::string name = read_string("Enter name: ");
                int battery = read_int("Enter battery: ");

                std::shared_ptr<Robot> robot;

                if (type == 1) {
                    double speed = read_double("Enter speed: ");
                    robot = std::make_shared<MobileRobot>(id, name, battery, speed);
                } else if (type == 2) {
                    double speed = read_double("Enter speed: ");
                    std::string mode = read_string("Enter cleaning mode: ");

                    // Change this constructor if your CleaningRobot uses different attributes.
                    robot = std::make_shared<CleaningRobot>(id, name, battery, speed, mode);
                } else if (type == 3) {
                    std::string cuisine = read_string("Enter cuisine: ");

                    // Change this constructor if your CookingRobot uses different attributes.
                    robot = std::make_shared<CookingRobot>(id, name, battery, cuisine);
                } else {
                    std::cout << "Invalid robot type.\n";
                    continue;
                }

                fleet.add(robot);
                robot_list.push_back(robot);

                std::cout << "Robot added.\n";
            } else if (choice == 2) {
                std::string id = read_string("Enter robot id to remove: ");

                fleet.remove(id);

                robot_list.erase(
                    std::remove_if(robot_list.begin(), robot_list.end(),
                        [&id](const std::shared_ptr<Robot>& robot) {
                            return robot->id() == id;
                        }),
                    robot_list.end()
                );

                std::cout << "Robot removed if it existed.\n";
            } else if (choice == 3) {
                std::cout << fleet;
            } else if (choice == 4) {
                std::string id = read_string("Enter robot id: ");

                auto robot = fleet.find(id);
                robot->work();
            } else if (choice == 5) {
                fleet.work_all();
            } else if (choice == 6) {
                fleet.charge_all();
                std::cout << "All robots charged.\n";
            } else if (choice == 7) {
                std::string robot_id = read_string("Enter robot id: ");
                std::string task_name = read_string("Enter task name: ");
                int priority = read_int("Enter priority 1-5: ");

                if (priority < 1 || priority > 5) {
                    std::cout << "Priority must be between 1 and 5.\n";
                    continue;
                }

                Task task{task_name, priority, robot_id};
                fleet.assign_task(robot_id, task);

                std::cout << "Task assigned.\n";
            } else if (choice == 8) {
                fleet.show_tasks();
            } else if (choice == 9) {
                std::string id = read_string("Enter mobile robot id: ");
                int seconds = read_int("Enter seconds: ");

                auto robot = fleet.find(id);
                //cast to MobileRobot to make sure startwork() is available, if the cast fails, mobile will be a nullptr.
                auto mobile = std::dynamic_pointer_cast<MobileRobot>(robot);

                if (!mobile) {
                    std::cout << "This robot is not a MobileRobot.\n";
                    continue;
                }

                mobile->start_work(seconds);
                std::cout << "Timed work started.\n";
            } else if (choice == 10) {
                fleet.show_first_low_battery_robot();
            } else if (choice == 11) {
                fleet.show_first_working_robot();
            } else if (choice == 0) {
                running = false;
            } else {
                std::cout << "Invalid option.\n";
            }
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}