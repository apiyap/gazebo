/*
 * Copyright (C) 2014-2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef _GAZEBO_RAZER_HYDRA_HH_
#define _GAZEBO_RAZER_HYDRA_HH_

#include <vector>
#include <gazebo/math/Filter.hh>
#include <gazebo/math/Vector3.hh>
#include <gazebo/common/Plugin.hh>

namespace gazebo
{
  class RazerHydra : public WorldPlugin
  {
    /// \brief Constructor.
    public: RazerHydra();

    /// \brief Destructor.
    public: virtual ~RazerHydra();

    // Documentation Inherited.
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);

    /// \brief Poll the hydra for input.
    /// \param[in] _lowPassCornerHz Filter frequency.
    /// \return true when there is a new update coming from the controller.
    private: bool Poll(float _lowPassCornerHz = 5.0);

    /// \brief Method executed in a separate thread to poll hydra for updates.
    private: void Run();

    /// \brief Update the hydra.
    /// \param[in] _info Update information.
    private: void Update(const common::UpdateInfo &_info);

    /// \brief Raw controller positions.
    private: std::array<int16_t, 6> rawPos;

    /// \brief Raw controller orientations.
    private: std::array<int16_t, 6> rawQuat;

    /// \brief Raw value of the buttons.
    private: std::array<uint8_t, 2> rawButtons;

    /// \brief Raw values of the analog joysticks.
    private: std::array<double, 6> rawAnalog;

    /// \brief Device file descriptor
    private: std::vector<int> hidrawFd;

    /// \brief Left and right controller positions.
    private: std::array<math::Vector3, 2> pos;

    /// \brief Left and right controller orientations.
    private: std::array<math::Quaternion, 2> quat;

    /// \brief Left and right filtered positions.
    private: std::array<math::OnePoleVector3, 2> filterPos;

    /// \brief Left and right filtered controller orientations.
    private: std::array<math::OnePoleQuaternion, 2> filterQuat;

    /// \brief Analog joysticks
    private: std::array<float. 6> analog;

    /// \brief Buttons that have been pressed.
    private: std::array<uint8_t, 14> buttons;

    /// \brief Estimate of the update period.
    private: math::OnePole<float> periodEstimate;

    /// \brief Time of the last poll cycle.
    private: common::Time lastCycleStart;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    /// \brief Mutex
    private: boost::mutex mutex;

    /// \brief Additional thread
    private: boost::thread *pollThread;

    /// \brief Use to stop the additional thread that the plugin uses.
    private: bool stop;

    /// \brief Gazebo communication node pointer.
    private: transport::NodePtr node;

    /// \brief Publisher pointer used to publish the messages.
    private: transport::PublisherPtr pub;
  };
}
#endif
