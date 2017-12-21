//==--- Lumos/Event/EventManager.hpp ----------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  EventManager.hpp
/// \brief This file provides a class which manages events.
//
//==------------------------------------------------------------------------==//

#ifndef VOXEL_LUMOS_EVENT_EVENT_MANAGER_HPP
#define VOXEL_LUMOS_EVENT_EVENT_MANAGER_HPP

namespace Voxx::Lumos {

/// The EventManager class defines a class which manages different types of
/// events in Lumos. It is the central point through which events flow.
/// Objects can be added as sources which allow them to post events to the
/// manager, and can also be added as sinks where they can consume the events.
class EventManager {
	
};

} // namespace Voxx::Lumos

#endif // VOXEL_LUMOS_EVENT_EVENT_MANAGER_HPP