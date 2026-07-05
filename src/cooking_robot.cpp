#include "cooking_robot.hpp"

#include <iostream>

CookingRobot::CookingRobot(const std::string& id,
                         const std::string& name,
                         int battery,
                         std::string cuisine)
    : Robot(id, name, battery),
      cuisine_(cuisine)
{}

void CookingRobot::work(){
    if (battery == 0)
        throw std::runtime_error(name_ + "battery's empty: cannot cook");
    
    status_ = "working";
    battery_ = std::clamp(battery_ - 20, 0, 100);

    std::cout << name_ << "is cooking some delicious " << cuisine_ << "  dish with remaining battery : " << battery_ << "%\n";
}

std::string CookingRobot::type() const{
    return cuisine_ + "CookingRobot";
}