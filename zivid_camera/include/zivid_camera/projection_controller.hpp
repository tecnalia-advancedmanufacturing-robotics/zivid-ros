// Copyright 2025 Zivid AS
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the Zivid AS nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <Zivid/Projection/Projection.h>

#include <filesystem>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <string>
#include <vector>
#include <zivid_camera/controller_interface.hpp>
#include <zivid_interfaces/srv/projection_resolution.hpp>
#include <zivid_interfaces/srv/projection_start.hpp>
#include <zivid_interfaces/srv/projection_status.hpp>

namespace Zivid
{
class Camera;
class Settings;
}  // namespace Zivid

namespace zivid_camera
{
template <typename SettingsType>
class CaptureSettingsController;

struct ProjectionState
{
  std::optional<Zivid::Projection::ProjectedImage> projected_image;
};

class ProjectionController
{
public:
  ProjectionController(
    rclcpp::Node & zivid_camera_node, Zivid::Camera & camera,
    CaptureSettingsController<Zivid::Settings2D> & settings_2d_controller,
    ControllerInterface controller_interface);
  ~ProjectionController();

private:
  void capture2DServiceHandler(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
    std::shared_ptr<std_srvs::srv::Trigger::Response> response);
  void resolutionServiceHandler(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<zivid_interfaces::srv::ProjectionResolution::Request> request,
    std::shared_ptr<zivid_interfaces::srv::ProjectionResolution::Response> response);
  void startServiceHandler(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<zivid_interfaces::srv::ProjectionStart::Request> request,
    std::shared_ptr<zivid_interfaces::srv::ProjectionStart::Response> response);
  void statusServiceHandler(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<zivid_interfaces::srv::ProjectionStatus::Request> request,
    std::shared_ptr<zivid_interfaces::srv::ProjectionStatus::Response> response);
  void stopServiceHandler(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
    std::shared_ptr<std_srvs::srv::Trigger::Response> response);

  rclcpp::Node & node_;
  Zivid::Camera & camera_;
  CaptureSettingsController<Zivid::Settings2D> & settings_2d_controller_;
  ControllerInterface controller_interface_;

  std::unique_ptr<ProjectionState> state_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr capture_2d_service_;
  rclcpp::Service<zivid_interfaces::srv::ProjectionResolution>::SharedPtr resolution_service_;
  rclcpp::Service<zivid_interfaces::srv::ProjectionStart>::SharedPtr start_service_;
  rclcpp::Service<zivid_interfaces::srv::ProjectionStatus>::SharedPtr status_service_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr stop_service_;
};
}  // namespace zivid_camera
