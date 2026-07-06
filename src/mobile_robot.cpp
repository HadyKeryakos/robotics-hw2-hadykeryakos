#include "mobile_robot.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <stdexcept>

extern std::mutex g_cout_mutex;

MobileRobot::MobileRobot(const std::string& id,
                         const std::string& name,
                         int battery,
                         double speed)
    : Robot(id, name, battery),
      speed_(speed)
{}

MobileRobot::~MobileRobot()
{
    stop_ = true;

    if (worker_.joinable()) {
        worker_.join();
    }
}

void MobileRobot::work(){
    if (battery_ == 0)
        throw std::runtime_error(name_ + " battery's empty: cannot be mobile");
    
    status_ = "working";
    battery_ = std::clamp(battery_ - 20, 0, 100);

    std::cout << name_ << " is moving at speed " << speed_ << " m/s with remaining battery : " << battery_ << "%\n";
}

std::string MobileRobot::type() const{
    return "MobileRobot";
}

void MobileRobot::start_work(int seconds)
{
    if (seconds <= 0) {
        throw std::runtime_error("seconds must be positive");
    }

    if (worker_.joinable()) {
        //if the user calls start_work on r1 for 20 seconds, then calls it again on r1 before the 20 seconds are over, the following line stops the old  when it gets to its next loop check
        //and lets the new one run, we can remove if we want the first start_work to finish before the second one starts running.
        stop_ = true; 
        worker_.join();
    }

    stop_ = false;

    worker_ = std::thread([this, seconds]() {
        for (int i = 0; i < seconds && !stop_; ++i) {
            try {
                std::lock_guard<std::mutex> lock(g_cout_mutex);
                work();
                std::cout << "Status: " << status() << "\n";
            } catch (const std::runtime_error& e) {
                std::lock_guard<std::mutex> lock(g_cout_mutex);
                std::cout << "Error: " << e.what() << "\n";
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}