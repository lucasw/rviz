/*
 * Copyright (c) 2012, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "ros/master.h"

#include "rviz/properties/ros_service_property.h"

#include <QApplication>


namespace rviz
{

RosServiceProperty::RosServiceProperty( const QString& name,
                                        const QString& default_value,
                                        const QString& message_type,
                                        const QString& description,
                                        Property* parent,
                                        const char *changed_slot,
                                        QObject* receiver )
  : EditableEnumProperty( name, default_value, description, parent, changed_slot, receiver )
  , message_type_( message_type )
{
  connect( this, SIGNAL( requestOptions( EditableEnumProperty* )),
           this, SLOT( fillServiceList()));
}

void RosServiceProperty::setMessageType( const QString& message_type )
{
  message_type_ = message_type;
}

void RosServiceProperty::fillServiceList()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  clearOptions();

  std::string std_message_type = message_type_.toStdString();

  // There is no ros::master::getServices
  // The only point of getting a list of existing services would
  // be to prevent the user from typing in the name of a service that
  // already exists, otherwise they should be able to type in any
  // valid service name and that service will be created.
  #if 0
  ros::master::V_ServiceInfo services;
  ros::master::getServices( services );


  // Loop through all provided services
  ros::master::V_ServiceInfo::iterator it;
  for( it = services.begin(); it != services.end(); ++it )
  {
    const ros::master::ServiceInfo& service = *it;

    // Only add services whose type matches.
    if( service.datatype == std_message_type )
    {
      addOptionStd( service.name );
    }
  }
  #endif
  sortOptions();
  QApplication::restoreOverrideCursor();
}

} // end namespace rviz
