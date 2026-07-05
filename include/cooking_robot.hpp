#pragma once
#include "robot.hpp"

class CookingRobot : public Robot {
public:
    CookingRobot(const std::string& id, const std::string& name, int battery, std::string cuisine);

    void        work()  override;  
    std::string type()  const override;

private:
    std::string cuisine_;
};