#pragma once
#include "robot.hpp"
#include "task.hpp"
#include <memory>
#include <string>
#include <ostream>
#include <unordered_map>
#include <queue>

class Fleet {
public:
    void add(std::shared_ptr<Robot> robot);
    void remove(const std::string& id);
    std::shared_ptr<Robot> find(const std::string& id) const;

    // Stores the task in the priority queue and marks the robot as busy.
    void assign_task(const std::string& robot_id, const Task& t);
    void show_tasks()  const;  // prints the task queue in priority order

    void work_all()    const;  // calls work() on every robot
    void charge_all()  const;  // calls charge() on every robot

    std::size_t size()  const;
    bool        empty() const;

    Fleet& operator+=(std::shared_ptr<Robot> robot);
    Fleet& operator-=(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const Fleet& f);

    void show_first_low_battery_robot() const;
    void show_first_working_battery_robot() const;

private:

    //It is better than using normal pointers because now it manages the deletion of robots automatically.
    //And we should not use unique_ptr because if fleet needs to have the pointer to the robot our main will not be able to also control it and we will have to use std::move
    //unordered_map gives fast lookup by robot id.
    std::unordered_map<std::string, std::shared_ptr<Robot>> robots_;

    // priority_queue keeps the highest priority task at the top which is what is required.
    std::priority_queue<Task> tasks_;
};