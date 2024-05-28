// Copyright 2021 Apex.AI, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef AUTOWARE_AUTO_PERCEPTION_RVIZ_PLUGIN__OBJECT_DETECTION__DETECTED_OBJECTS_WITH_FEATURE_DISPLAY_HPP_
#define AUTOWARE_AUTO_PERCEPTION_RVIZ_PLUGIN__OBJECT_DETECTION__DETECTED_OBJECTS_WITH_FEATURE_DISPLAY_HPP_

#include "autoware_auto_perception_rviz_plugin/object_detection/object_polygon_display_base.hpp"

#include <tier4_perception_msgs/msg/detected_objects_with_feature.hpp>

namespace autoware
{
namespace rviz_plugins
{
namespace object_detection
{
/// \brief Class defining rviz plugin to visualize DetectedObjectsWithFeature
class AUTOWARE_AUTO_PERCEPTION_RVIZ_PLUGIN_PUBLIC DetectedObjectsWithFeatureDisplay
: public ObjectPolygonDisplayBase<tier4_perception_msgs::msg::DetectedObjectsWithFeature>
{
  Q_OBJECT

public:
  using DetectedObjectsWithFeature = tier4_perception_msgs::msg::DetectedObjectsWithFeature;

  DetectedObjectsWithFeatureDisplay();

private:
  std::optional<Marker::SharedPtr> get_point_cloud_marker_ptr(
    const sensor_msgs::msg::PointCloud2 & point_cloud, const std_msgs::msg::ColorRGBA & color,
    const double & scale) const
  {
    if (m_display_point_cloud_property.getBool()) {
      return detail::get_point_cloud_marker_ptr(point_cloud, color, scale);
    } else {
      return std::nullopt;
    }
  }

  double get_scale() { return m_scale_property.getFloat(); }
  std_msgs::msg::ColorRGBA get_rgba()
  {
    QColor color = m_color_property.getColor();
    std_msgs::msg::ColorRGBA color_rgba;
    color_rgba.r = color.redF();
    color_rgba.g = color.greenF();
    color_rgba.b = color.blueF();
    color_rgba.a = m_alpha_property.getFloat();
    return color_rgba;
  }
  void processMessage(DetectedObjectsWithFeature::ConstSharedPtr msg) override;

  // Properties to enable/disable and modify point cloud visualization
  rviz_common::properties::BoolProperty m_display_point_cloud_property;
  rviz_common::properties::ColorProperty m_color_property;
  rviz_common::properties::FloatProperty m_alpha_property;
  rviz_common::properties::FloatProperty m_scale_property;
};

}  // namespace object_detection
}  // namespace rviz_plugins
}  // namespace autoware

#endif  // AUTOWARE_AUTO_PERCEPTION_RVIZ_PLUGIN__OBJECT_DETECTION__DETECTED_OBJECTS_WITH_FEATURE_DISPLAY_HPP_
