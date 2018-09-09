#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/transforms.h>
#include <boost/foreach.hpp>
#include <tf/transform_listener.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

ros::Publisher tf_pub;
tf::TransformListener *tf_listener; 

void callback(const PointCloud::ConstPtr& pcl_in)
{
  PointCloud pcl_out;
  tf_listener->waitForTransform("/velodyne", "/odom",ros::Time::now(), ros::Duration(3.0));
  pcl_ros::transformPointCloud("/odom", *pcl_in, pcl_out, *tf_listener);
  tf_pub.publish(pcl_out);


  /*printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
  BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points)
    printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);*/
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sub_pcl");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe<PointCloud>("velodyne_points", 1, callback);
  tf_pub = nh.advertise<PointCloud> ("tf_points2", 1);  
  tf_listener    = new tf::TransformListener();
  ros::spin();
}
