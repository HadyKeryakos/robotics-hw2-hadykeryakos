#include "cleaning_robot.hpp"

#include <iostream>

CleaningRobot::CleaningRobot(const std::string& id, const std::string& name, int battery, double speed, std::string whattoclean)
    : MobileRobot(id, name, battery, speed),
      whattoclean_(whattoclean)
{}

void CleaningRobot::work(){
    if (battery_ == 0)
        throw std::runtime_error(name_ + "battery's empty: cannot clean");
    
    status_ = "working";
    battery_ = std::clamp(battery_ - 20, 0, 100);

    std::cout << name_ << "is meticulously cleaning the " << whattoclean_ << " with remaining battery : " << battery_ << "%\n";
}

std::string CleaningRobot::type() const{
    return whattoclean_ + "CleaningRobot";
}