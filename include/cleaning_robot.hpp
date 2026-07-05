#pragma once
#include "mobile_robot.hpp"

class CleaningRobot : public MobileRobot{
public:
    CleaningRobot(const std::string& id, const std::string& name, int battery, double speed, std::string whattoclean);

    void        work()  override;  
    std::string type()  const override;

private:
    std::string whattoclean_;
};