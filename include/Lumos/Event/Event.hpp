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

class KeyEvent {
 public:
 	/// Constructor -- set the action kind of the event.
 	/// \param action The action kind of the event.
 	explicit KeyEvent(EventActionKind action) {
 		setAction(action);
 	}
 	
 	/// Sets the value kind of the key event.
 	void setValue(KeyEventKind value) {
 		Value |= (value << 1) & valueMask;
 	}

 	/// Sets the action kind of the key event.
 	void setAction(EventActionKind action) {
 		Value |= action & actionMask;
 	}

 	/// Returns the value kind of the key event.
 	KeyEventKind value() const {
 		return static_cast<KeyEventKind>((Value >> 1) & valueMask);
 	}

 	/// Returns the action kind of the key event.
 	EventActionKind action() const {
 		return static_cast<EventActionKind>(Value & actionMask);
 	}

 private:
 	/// Defines the mask for the action.
 	static constexpr uint16_t valueMask = 0xFFFE;
 	/// Defines the mask for the action.
 	static constexpr uint8_t actionMask = 0x01;

	/// The value of the event. The LSB stores the action type of the event which
	/// is converted to an EventAction kind, and the remaining 15 bits are used
	/// to define the key value for the event.
	uint16_t Value = 0;
};

} // namespace Voxx::Lumos

#endif // VOXEL_LUMOS_EVENT_EVENT_HPP