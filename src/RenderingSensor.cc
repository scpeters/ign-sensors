/*
 * Copyright (C) 2019 Open Source Robotics Foundation
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

#include "ignition/sensors/RenderingSensor.hh"

/// \brief Private data class for RenderingSensor
class ignition::sensors::RenderingSensorPrivate
{
  public: ignition::rendering::ScenePtr scene;
};

using namespace ignition;
using namespace sensors;

//////////////////////////////////////////////////
RenderingSensor::RenderingSensor() :
  dataPtr(new RenderingSensorPrivate)
{
}

//////////////////////////////////////////////////
RenderingSensor::~RenderingSensor()
{
}

/////////////////////////////////////////////////
void RenderingSensor::SetScene(rendering::ScenePtr _scene)
{
  this->dataPtr->scene = _scene;
}

/////////////////////////////////////////////////
rendering::ScenePtr RenderingSensor::Scene() const
{
  return this->dataPtr->scene;
}