#include "outlier_filter.hpp"

namespace outlierfilter
{
OutlierFilter::OutlierFilter() : Node("voxel_filter")
{
  pc_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/input_point_cloud", 10,
      std::bind(&OutlierFilter::pc_filter_cb, this, std::placeholders::_1));
  
  filter_pc_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/filtered_point_cloud", 10);
}

void OutlierFilter::pc_filter_cb(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *cloud);
    // VoxelGrid fliter
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
    voxel_grid.setInputCloud(cloud);

    // ボクセルサイズの設定（x, y, z軸の解像度）
    voxel_grid.setLeafSize(0.1f, 0.1f, 0.1f);  // 10cmのボクセルグリッド
    voxel_grid.filter(*cloud_filtered);
    pcl::PointCloud<pcl::PointXYZ>::Ptr final_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    int occupancy_threshold = 5;  // 最低5点以上の占有率を持つボクセルを残す
    std::map<Eigen::Vector3i, int, Eigen::less<Eigen::Vector3i>> voxel_map;
    for (const auto& point : cloud->points)
    {
        Eigen::Vector3i voxel_coord = voxel_grid.getGridCoordinates(point.x, point.y, point.z);
        voxel_map[voxel_coord]++;
    }
    for (const auto& point : cloud_filtered->points)
    {
        Eigen::Vector3i voxel_coord = voxel_grid.getGridCoordinates(point.x, point.y, point.z);
        if (voxel_map[voxel_coord] >= occupancy_threshold)
        {
            final_filtered->points.push_back(point);
        }
    }
    sensor_msgs::msg::PointCloud2 output_msg;
    pcl::toROSMsg(*final_filtered, output_msg);
    output_msg.header = msg->header;
    publisher_->publish(output_msg);
}  
} // namespace outlierfilter


#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(outlierfilter::OutlierFilter)


