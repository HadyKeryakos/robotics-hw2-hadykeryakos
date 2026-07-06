1. Why `shared_ptr` in Fleet and not `unique_ptr`? What would break if you switched?

With unique_ptr, fleet will store the pointer in its unsorted_map, but when main.cpp runs fleet.find(robot_id) in option 9, which is supposed to return a pointer to a robot, it will not be able to do that. we will have to std::move the robot out of fleet to main which will turn the pointer in fleet to null and break other behavior like option 3 which shows all robots.

2. What container did you use for `robots_`? Why — what is its lookup cost?

The container used was an unordered_map because it has the fastest lookup cost which is O(1). 

3. What container did you use for the task queue? What data structure is it built on, and why is it the right fit for "highest priority first"?

the container used was priority_queue. It is build on top of a vector who's elements are arranged in a way of a tree where the root is guaranteed to have the largest element thats why it is the right fit for highest priority first.

4. `operator<<` is declared `friend` inside Robot. What does `friend` give it that a regular method does not? Why can it not be a regular member function?

Both friend and being a regular method give it the access to members of the class. But we dont want it to be a regular member function because then we would have to use it with the following syntax Robot << ... Meanwhile the real use case is os << robot OR cout << robot
thats why we need to be a FREE function but we declare it as friend so it can access the attributes we want to print out.

5. You used `std::find_if` with a lambda. What does that communicate compared to a hand-written loop?

when someone sees find_if they immediately know it is a search based on a certain condition represented by the lambda, meanwhile when reading the hand-written loop it is not as direct it could be a transformation or a filter or a search...

6. `work()` throws if battery is 0. Why use an exception rather than returning false or printing an error?

better than returning false because it forces us (the caller) to catch the exception and handle it. and its better than printing an error because what if we had logs too and wanted to log the error somewhere, using a throw we can choose how to handle in different parts of the system instead of always throwing the error directly from work()

7. An exception is thrown inside `assign_task` when the robot is not found. Is the fleet's state consistent afterwards?

yes the felet's state is consistent because we validated that the robot is there before adding to the queue or changing the robot's status to working.

8. `start_work` uses a background thread. What did you do with `stop_` and `worker_`, and why?

I start the thread worker with a for loop that keeps running under 2 conditions, i < number of seconds and stop_ is false. At first i was joining the thread right after its block which went against "running in the background". So i removed the .join() and added a destructor for the MobileRobot class and in it i change stop_ to true to stop any thread currently in its loop and check if there is a joinable thread, if there is any  .join().

9. **Diamond inheritance — read and answer:**

```cpp
class Robot { public: std::string name_ = "base"; };
class MobileRobot      : public Robot {};
class CookingRobot     : public Robot {};
class MaintenanceRobot : public MobileRobot, public CookingRobot {};

int main() {
    MaintenanceRobot m;
    std::cout << m.name_;   // which name_?
}
```

This does not compile. Why? How many copies of `Robot` exist inside `MaintenanceRobot`? How does C++ solve this — what keyword is involved and what does it change? Figure it out, write a corrected version, and explain it in your own words.

It does not compile because MaintenanceRobot will have two different copies of Robot . It is fixed by using virtual inheritance.

```cpp
class Robot { public: std::string name_ = "base"; };
class MobileRobot      : public virtual Robot {};
class CookingRobot     : public virtual Robot {};
class MaintenanceRobot : public MobileRobot, public CookingRobot {};

int main() {
    MaintenanceRobot m;
    std::cout << m.name_;   // which name_?
}
```

Now both MobileRobot and CookingRobot hold the same copy of Robot so when MaintenanceRobot inherits from them it will have one shared copy.