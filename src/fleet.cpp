#include "fleet.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>

void Fleet::add(std::shared_ptr<Robot> robot)
{
    if (!robot) {
        throw std::runtime_error("Cannot add null robot");
    }

    robots_[robot->id()] = robot;
}

void Fleet::remove(const std::string& id)
{
    robots_.erase(id);
}

std::shared_ptr<Robot> Fleet::find(const std::string& id) const
{
    auto r = robots_.find(id);

    if (r == robots_.end())
        throw std::runtime_error("Robot with id : " + id + " not found.");
    return r->second;
}

void Fleet::assign_task(const std::string& robot_id, const Task& t)
{
    auto robot = find(robot_id);

    Task assigned_task = t;
    assigned_task.assigned_to = robot_id;

    tasks_.push(assigned_task);
    robot->set_status("working");
}

void Fleet::show_tasks() const
{
    auto copy = tasks_;

    while (!copy.empty()) {
        std::cout << copy.top() << "\n";
        copy.pop();
    }
}

void Fleet::work_all() const
{
    for (const auto& pair : robots_) {
        pair.second->work();
    }
}

void Fleet::charge_all() const
{
    for (const auto& pair : robots_) {
        pair.second->charge();
    }
}

std::size_t Fleet::size() const
{
    return robots_.size();
}

bool Fleet::empty() const
{
    return robots_.empty();
}

Fleet& Fleet::operator+=(std::shared_ptr<Robot> robot)
{
    add(robot);
    return *this;
}

Fleet& Fleet::operator-=(const std::string& id)
{
    remove(id);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fleet& f)
{
    os << "Fleet size: " << f.robots_.size() << "\n";

    for (const auto& pair : f.robots_) {
        os << *pair.second << "\n";
    }

    return os;
}

void Fleet::show_first_low_battery_robot() const
{
    auto it = std::find_if(robots_.begin(), robots_.end(),
        [](const auto& pair) {
            return pair.second->battery() < 20;
        });

    if (it == robots_.end()) {
        std::cout << "No robot below 20% battery.\n";
        return;
    }

    std::cout << "First low battery robot: " << *it->second << "\n";
}

void Fleet::show_first_working_battery_robot() const
{
    auto it = std::find_if(robots_.begin(), robots_.end(),
        [](const auto& pair) {
            return pair.second->status() == "working";
        });

    if (it == robots_.end()) {
        std::cout << "No robot below 20% battery.\n";
        return;
    }

    std::cout << "First low battery robot: " << *it->second << "\n";
}