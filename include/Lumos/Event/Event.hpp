//==--- Lumos/Event/Event.hpp ------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  Event.hpp
/// \brief This file provides the implementation for event types.
//
//==------------------------------------------------------------------------==//

#ifndef VOXEL_LUMOS_EVENT_EVENT_HPP
#define VOXEL_LUMOS_EVENT_EVENT_HPP

#include "Keycodes.hpp"

namespace Voxx::Lumos {

/// Defines the possible types of actions for an event.
enum class EventActionKind : uint8_t {
	Press   = 0, 		//!< Defines a press event.
	Release = 1			//!< Defines a release event.
};

} // namespace Voxx::Lumos

#endif // VOXEL_LUMOS_EVENT_EVENT_HPP