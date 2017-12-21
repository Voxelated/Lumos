//==--- Lumos/Window/WindowXcb.hpp ------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  WindowXcb.hpp
/// \brief This file provides an implementation of the Window class which uses
///				 XCB.
//
//==------------------------------------------------------------------------==//

#include <X11/Xlib.h>
#include "Window.hpp"

/// The WindowXcb class defines an implementation of the Window interface by
/// using the XCB library for window related functionality.
class WindowXcb : Window<WindowXcb> {
 public:
 	/// Defines the type of the window base class.
 	using SelfType   = Window<WindowXcb>;
 	/// Defines the type of the traits class.
 	using TraitsType = WindowTraits<SelfType>;
 	/// Defines the type of the window pointer to return.
 	using WindowPtr  = typename TraitsType::WindowPtr;
 	/// Defines the type of the event to handle.
 	using EventType  = typename TratisType::EventType;

 	/// Constructor -- creates the necessary resources.
 	WindowXcb();

 	/// Destructor -- cleans up all resources.
 	~WindowXcb();

 	/// Creates a new window and returns a pointer to the newly created window.
 	/// Ownership of the new window is passed to the caller.
 	/// \param extent The extent of the window.
 	/// \param title  The title of the window.
 	/// \return A WindowPtr to the newly created window.
 	WindowPtr create(Extent2d extent, const char* title);

 	/// Polls for an event.
 	Event pollForEvent();

 private:
 	/// The WindowResource struct holds the window API resources required by this
 	/// implementation of the window.
 	struct WindowResource;

 	/// The Graphics resource holfd the graphics API recources required to draw to
 	/// the window.
 	struct GraphicsResource;

 	/// A poitner to the window resources.
 	WindowResource*   WindowHandle 	= nullptr;
 	/// A pointer to the graphics resources.
 	GraphicsResource* GfxHandle 	 	= nullptr;

 	/// Sets up the window.
 	/// \param extent The extent of the window.
 	void setup(Extent2d extent);
};