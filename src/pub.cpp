#include "ros/ros.h"
#include "ros_protobuf_bridge/Foo.h"
#include "Bar_ros.h"

#include <string>

/// Foo publisher.
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<ros_protobuf_bridge::Bar>("chatter", 1000);

  ros::Rate loop_rate(10);

  ros_protobuf_bridge::Bar prot, d_prot;

  int count = 0;
  std::string ser;
  while (ros::ok())
  {

    ros_protobuf_bridge::Foo obj;

    obj.a = count;
    ROS_INFO("%d", obj.a);
    // chatter_pub.publish(obj);

    prot.set_page_number(count);
    prot.SerializeToString(&ser);
    ROS_INFO("Bar: %s", ser.c_str());

    d_prot.ParseFromString(ser);
    ROS_INFO("Bar: %d", d_prot.page_number());
    chatter_pub.publish(d_prot);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}