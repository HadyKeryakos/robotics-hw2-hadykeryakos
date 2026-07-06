This project gives the user a menu where he can add a robot to a fleet.
The robot can be one of the following types: Mobile Robot, Cleaning Robot, Cooking Robot.
The user can assign a specific task to a certain robot.
The user can start timed work on a certain robot.
The user has other options in the menu that provide information about this fleet.

To compile run : ./compile.sh
Then run: ./fleet_app

The main issue that i faced was when i started timed work on a robot, it starts printing the type of work and its status every 1 second, which collided with me entering other options from the menu (e.g. option 3). The issue was solved with a mutex around printing the menu and around work() and cout << status() in the thread that runs in the background.

Another issue is that once a robot is sent to charge, it remains in "charging" mode,
but there was no specific behavior required in the assignement addressing how the robot is expected to charge (instantly goes up to 100 or takes a certain amount of time). This could be fixed by making the charge() function take 10 seconds to finish and then changing the robots mode to "idle" again.