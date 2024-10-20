#ifndef OUTLIER_FILTER_HPP_
#define OUTLIER_FILTER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <pcl_conversions/pcl_conversions.h>  

namespace outlierfilter
{
class OutlierFilter : public rclcpp::Node
{
public:
    explicit OutlierFilter(); 

private:
    void pc_filter_cb(const sensor_msgs::msg::PointCloud2::SharedPtr msg);  
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pc_sub_;  
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr filter_pc_pub_;  
};  
} // namespace outlierfilter


#endif  // VOXEL_FILTER_HPP_
