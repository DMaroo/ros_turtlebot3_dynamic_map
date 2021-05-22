#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tbot3_practice/termcolor.hpp>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "my_navigator");
    ros::NodeHandle goal_pub_node;

    ros::Publisher goal_pub = goal_pub_node.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);

    ros::Rate loop_rate(0.5);

    std::string state = "";

    while (ros::ok())
    {
        std::cout << termcolor::color<100, 100, 100> << termcolor::bold << "[?]" << termcolor::reset << " To exit the program, enter \"" << termcolor::red << "exit" << termcolor::reset << "\" as any one of the inputs\n\n";

        std::cout << termcolor::blue << termcolor::bold << "[=]" << termcolor::reset << " Please enter the goal position (format: <x y>) : ";

        geometry_msgs::PoseStamped goal;

        std::cin >> state;

        if (state == "exit")
        {
            std::cout << termcolor::red << termcolor::bold << "[-]" << termcolor::reset << " Exiting the program...\n";
            return 0;
        }
        else
        {
            goal.pose.position.x = atof(state.c_str());
        }

        std::cin >> state;

        if (state == "exit")
        {
            std::cout << termcolor::red << termcolor::bold << "[-]" << termcolor::reset << " Exiting the program...\n";
            return 0;
        }
        else
        {
            goal.pose.position.y = atof(state.c_str());
        }

        std::cout << termcolor::blue << termcolor::bold << "[=]" << termcolor::reset << " Please enter the goal orientation (format: <z w>) : ";

        std::cin >> state;

        if (state == "exit")
        {
            std::cout << termcolor::red << termcolor::bold << "[-]" << termcolor::reset << " Exiting the program...\n";
            return 0;
        }
        else
        {
            goal.pose.orientation.z = atof(state.c_str());
        }

        std::cin >> state;

        if (state == "exit")
        {
            std::cout << termcolor::red << termcolor::bold << "[-]" << termcolor::reset << " Exiting the program...\n";
            return 0;
        }
        else
        {
            goal.pose.orientation.w = atof(state.c_str());
        }


        goal.header.frame_id = "map";

        goal.pose.position.z = 0.0;

        goal.pose.orientation.x = 0.0;
        goal.pose.orientation.y = 0.0;

        goal.header.seq = 1;
        goal.header.stamp = ros::Time::now();

        std::cout << "\n" << termcolor::yellow << termcolor::bold << "[*]" << termcolor::reset << " Publishing the input parameters to the concerned node...\n";

        goal_pub.publish(goal);

        std::cout << termcolor::green << termcolor::bold << "[+]" << termcolor::reset << " Input parameters successfully published!\n\n";

        std::cout << termcolor::yellow << termcolor::bold << "[*]" << termcolor::reset << " Bot planning the path and moving accordingly...\n\n";

        ros::spinOnce();
        loop_rate.sleep();
    }
}