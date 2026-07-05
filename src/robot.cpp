#include "robot.hpp"
#include <algorithm>

Robot::Robot(const std::string& id, const std::string& name, int battery)
    : id_(id),
      name_(name),
      battery_(std::clamp(battery, 0, 100)),
      status_("idle") 
      {}

void Robot::charge()
{
  battery_ = 100;
  status_ = "charging";
}

std::string Robot::id() const
{
    return id_;
}

std::string Robot::name() const
{
    return name_;
}

int Robot::battery() const
{
    return battery_;
}

std::string Robot::status() const
{
    return status_;
}

void Robot::set_status(const std::string& status)
{
    status_ = status;
}

bool Robot::operator==(const Robot& other) const
{
    return id_ == other.id_;
}

std::string Robot::operator+(const Robot& other) const
{
    return name_ + " + " + other.name_;
}

//we declared this function as a "friend" because usually when calling member methods or overloading operators it would be robot "overloaded operator". 
//in this case it would be robot << std::cout. Which is not the syntax we want. We want it to be std::cout << robot. So the method cant be a member method BUT still
//has to be able to access the attributes of robot to print them out, which is the permissions given by the keyword friend.
std::ostream& operator<<(std::ostream& os, const Robot& r)
{
    os << "[" << r.type() << "] "
       << "id=" << r.id_
       << ", name=" << r.name_
       << ", battery=" << r.battery_ << "%"
       << ", status=" << r.status_;

    return os;
}