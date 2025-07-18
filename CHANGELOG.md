# Zivid ROS driver changelog

This project adheres to [Semantic Versioning](https://semver.org).

# 3.2.0
* Added new services for a number of different functions: 
  * Calibration board and fiducial marker detection. 
  * Infield correction. 
  * Hand-eye calibration. 
  * Image projection. 
  * See [README](./README.md) for a description of all the available services.
* Added URDF/Xacro for Zivid cameras. The Zivid camera will now appear in the scene in RViz.
* Added parameter `color_space` used to configure whether images or point clouds are published in `linear_rgb` or `srgb`
  color space. This also applies to point clouds saved using `capture_and_save`.
* Added ability to get estimate intrinsics from capture frame. Estimate intrinsics are more accurate than the previously
  hard-coded camera intrinsics.
* The minimum supported Zivid SDK version is now 2.15.
* Added CI testing of Zivid SDK version 2.16.

# 3.1.0

* Fix an issue that could result in a crash due to use of uninitialized memory in zivid_camera.
* The zivid_camera node no longer terminates when capturing and no settings are set. Instead, the TriggerResponse
  will have its "success" field set to false. See #116.
* The zivid_camera node no longer terminates if `capture_assistant/suggest_settings` throws an exception. Instead,
  the exception message is passed to the response. The fields "success" and "message" have been added to
  `CaptureAssistantSuggestSettings.srv` for this purpose. See #116.
* Add support for versions 2.9 to 2.15 of the Zivid SDK.

# 3.0.0

* Driver is updated with support for ROS 2. ROS 1 is no longer supported. If you need support
  for ROS 1, check one of the earlier releases below, or use the branch `ros1-master`.
* Capture settings must be set via .yml files or YAML strings, which can be exported from
  Zivid Studio or the Zivid SDK. The driver no longer supports changing individual Zivid
  settings nodes directly from ROS. See the Configuration section of the [README](./README.md)
  for more details.
* Service descriptions have been moved to a separate ROS package named `zivid_interfaces`.
* The `capture` and `capture_2d` services now use the standard `std_srvs/srv/Trigger` type.
* The `load_settings_from_file` and `load_settings_2d_from_file` services are removed. Settings
  files must now be configured via parameters. See the Configuration section of the
  [README](./README.md) for more details.
* The data type of the `rgba` field in the `points/xyzrgba` topic is changed from `FLOAT32` to
  `UINT32`.

## 2.5.0

* Fixed an issue where the driver when running as a nodelet could not attach to a manager
  in the global namespace (https://github.com/zivid/zivid-ros/issues/84).
* Added `capture_and_save` service that captures a frame and saves it to a file.
* Adjusted some error messages that were assuming all Zivid cameras are connected via USB3.
* Added CI testing for Zivid SDK versions 2.9 to 2.12.

## 2.4.0

* Added support for PointXYZ and Range settings that are required for Zivid SDK 2.9.0 and newer
* Added launch parameter to disable firmware upgrade automatically
* Add support for loading capture settings via YML file

## 2.3.0

* Add support for normals. Normals are exposed via topic "normals/xyz".
* The minimum supported Zivid SDK version is now SDK 2.5.

## 2.2.0

* Add support for version 2.2.0 of the Zivid SDK.

## 2.0.0

* Support for version 2.0.0 of the Zivid SDK. For a full list of changes in the SDK, see the
  [SDK 2.0.0 Changelog](https://www.zivid.com/software/releases/2.0.0+7c4918cf-14/Changelog.md).
  Note that Zivid SDK 1.x is not supported by this driver version.
* The "points" topic has been renamed to "points/xyzrgba". The "contrast" value is no longer
  available in this message. Use the SNR image at topic "snr/image" instead.
* Added new topic "points/xyz". This is similar to "points/xyzrgba" except the color values
  are not included in the message. The message is compatible with pcl::PointXYZ. This topic is
  recommended for users who do not use the RGBA values in the point cloud.
* Added new "snr/image" topic. This topic contains the SNR values for all the pixels. SNR
  replaces the old "Contrast" values from SDK 1.x.
* Changes to how capture settings are configured:
  * The available settings, and the names and paths of the settings, has been updated to match
    the SDK 2.0.0 API. Note that some settings have been removed in 2.0.0. In addition the default
    values for some settings have changed. See the [README](./README.md) for a table of the
    supported settings in 2.0.0. Refer to the
    [SDK 2.0.0 Changelog](https://www.zivid.com/software/releases/2.0.0+7c4918cf-14/Changelog.md)
    for all the changes to settings.
  * The dynamic_reconfigure node `capture/general/` has been renamed to `settings/`.
  * The dynamic_reconfigure nodes `capture/frame_<n>/` has been renamed to `settings/acquisition_<n>/`.
  * The dynamic_reconfigure node `capture_2d/frame_0/` has been renamed to `settings_2d/acquisition_0/`.
  * Added new dynamic_reconfigure node `settings_2d/` which contains non-acquisition related 2D settings.
    As of SDK 2.0.0 this contains color balance settings.
* The depth image topic has been renamed from "depth/image_raw" to "depth/image".
* The encoding of "color/image" for 3D captures has been changed from "rgb8" to "rgba8".
* The launch parameter "num_capture_frames" has been renamed to "max_capture_acquisitions" to be
  consistent with the naming in the Zivid SDK.

## 1.1.0

* Updated the Intel OpenCL CPU runtime driver used in CI tests. This makes the CI tests
  stable again.
* Fixed a unit test that failed due to a missing sleep.
* Enabled unit tests for the Capture Assistant.
* Other minor improvements to README.md.
* Bumped minimum Zivid SDK version to 1.8.0.

## 1.0.0

* Added support for Capture Assistant. Added new service "capture_assistant/suggest_settings"
  that can be used to find suggested settings for your scene. Added sample_capture_assistant
  for C++ and Python. For more information, see README.md.
* Added support for 2D capture. Added new service "capture_2d" and new dynamic_reconfigure
  server "capture_2d/frame_0". Added sample_capture_2d for both C++ and Python. For more
  information, see README.md.
* Made common sample.launch script for all samples.
* Adjusted rviz/camera_view.rviz to make the 2D RGB image a bit bigger.
* Other minor improvements to README.md.
* Bumped minimum Zivid SDK version to 1.7.0.

## 0.9.0

* Initial release of ROS driver for Zivid cameras. For more information, see README.md.
