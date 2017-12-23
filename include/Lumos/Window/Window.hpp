//==--- Lumos/Window/Window.hpp ---------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  Window.hpp
/// \brief This file defines a class which represents a window.
//
//==------------------------------------------------------------------------==//

#include <memory>
#include <Lumos/Geometry/Extent.hpp>

#ifndef VOXEL_LUMOS_WINDOW_WINDOW_HPP
#define VOXEL_LUMOS_WINDOW_WINDOW_HPP

namespace Voxx::Lumos {

/// The WindowTraits class defines the traits of all windows.
/// \tparam WindowType The type of the window to get the traits of.
template <typename WindowImpl>
struct WindowTraits {
	/// Defines the type of the pointer used to access the window.
	using WindowPtr = std::unique_ptr<WindowImpl>;
};


/// The Window class defines the interface for a windows in Lumos. It is
/// statically polymorphic as the implementation is platform specific and can
/// therefore be selected at compile time.
/// \tparam WindowImpl The implementation type for the window.
template <typename WindowImpl>
class Window  {
 public:
 	/// Defines the type of pointer the implementation must return.
 	using WindowPtr = typename WindowTraits::WindowPtr;

 	/// Creates an instance of a window, passing ownership to the caller.
 	/// \param extent The extent of the window.
 	/// \param title  The title of the window.
 	WindowPtr create(Extent2d extent, const char* title)
 	{
 		return windowImpl()->create(extent, title);
 	}

 private:
 	/// Returns a pointer to the window implementation.
 	WindowImpl* windowImpl()
 	{
 		return static_cast<WindowImpl*>(this);
 	}

 	/// Returns a pointer to a const window implementation.
 	const WindowImpl* windowImpl() const
 	{
 		return static_cast<const WindowImpl*>(this);
 	}
};

} // namespace Voxx::Lumos

#endif // VOXEL_LUMOS_WINDOW_WINDOW_HPP
