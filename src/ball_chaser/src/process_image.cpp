#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    //  Service message
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255; 
    int left_region = img.width / 3; 
    int right_region = 2 * img.width / 3;

    bool white_ball_detected = false;
    int sum_positions = 0;
    int white_pixel_count = 0;

    
    for (int i = 0; i < img.height * img.step; i += 3) 
    {
        if (img.data[i] == white_pixel && img.data[i + 1] == white_pixel && img.data[i + 2] == white_pixel)
        {
            white_ball_detected = true;
            sum_positions += (i % img.step) / 3; // kinda added this to increase accuracy and miss recognition 
            white_pixel_count++;
        }
    }

    
    if (white_ball_detected)
    {
        if (ball_position < left_region)
        {
            drive_robot(0.0, 0.5); // Turn left
        }
        else if (ball_position > right_region)
        {
            drive_robot(0.0, -0.5); // Turn right
        }
        else
        {
            drive_robot(0.5, 0.0); // Move forward
        }
    }
    else
    {
        drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

