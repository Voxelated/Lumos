//==--- Lumos/Event/KeyEvent.hpp --------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  KeyEvent.hpp
/// \brief This file classes for key related events.
//
//==------------------------------------------------------------------------==//

#ifndef VOXEL_LUMOS_EVENT_KEY_EVENT_HPP
#define VOXEL_LUMOS_EVENT_KEY_EVENT_HPP

#include "Event.hpp"

namespace Voxx::Lumos {

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

/// The KeyHandler struct defines the interface for key event handling.
struct KeyHandler {
	/// Destructor --- enables calling of derived destructor.
	virtual ~KeyHandler() {}

	/// Handles the key event \p keyEvent.
	virtual void handleEvent(const KeyEvent& keyEvent) = 0;
};

/// The KeyEventHandler defines a mixin class which allows a class to add key
/// event handling functionality to itself.
/// \tparam HandlerImpl The implementation of the key handling functionality.
template <typename HandlerImpl>
class KeyEventHandler {
 private:
	/// Adapter class which allows a class which mixes in KeyEventHandler
	/// functionality to implement the KeyHandler interface and therefore be stored
	/// in a container. This class allows the class mixing in the KeyEventHandler
	/// functionality to not have to implement the runtime polymorphic KeyHandler
	/// class.
	/// \tparam 	KeyEventHandlerImpl 	The implementation of the static key
	///																	key handling interface.
	template <typename KeyEventHandlerImpl>
	class KeyHandlerAdapter  : public KeyHandler, public KeyEventHandlerImpl {
	 public:
	 	/// Constructor --- stores a reference to the key handling implementation.
	 	/// \param[in] 	keyHandlerImpl 	A reference to the key handling
	 	///															implementation.
	 	KeyHandlerAdapter(KeyEventHandlerImpl& keyHandlerImpl) 
	 	: KeyHandlerImpl(keyHandlerImpl) {}

	 	/// Implementation of the KeyHandler virtual interface to allow the adaption
	 	/// from the KeyEventHandlerImpl interface to the Keyhandler interface.
	 	/// \param[in]	keyEvent 	The key event to handle.
	 	void handleEvent(const KeyEvent& keyEvent) final override {
	 		static_cast<KeyEventHandlerImpl*>(this)->handleKeyEvent(keyEvent);
	 	}

	 private:
	 	/// The key handling implementation to adapt.
	 	KeyEventHandlerImpl& KeyHandlerImpl;
	};

	/// Defines the type of the static event handling type.
	using EventHandlerType 	= KeyEventHandler<HandlerImpl>;
	/// Defines the type of the handler adapter.
	using AdapterType 			= KeyHandlerAdapter<EventHandlerType>;

 public:
	/// Handler the key event by invoking the implementation defiened in the
	/// HandlerImpl class.
	/// \param[in] 	keyEvent 	The key event to handle.
	void handleKeyEvent(const KeyEvent& keyEvent) {
		static_cast<HandlerImpl*>(this)->handleKeyEvent(keyEvent);
	}

	/// Clones the class which mixes in the key event handling functionality,
	/// returning a unique pointer to the clone.
	std::unique_ptr<KeyHandler> clone() {
		return std::unique_ptr<KeyHandler>(
			new AdapterType(*static_cast<EventHandlerType*>(this)));
	}
};

} // namespace Voxx::Lumos

#endif // VOXEL_LUMOS_EVENT_KEY_EVENT_HPP
