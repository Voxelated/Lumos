//==--- Lumos/Event/Keycodes.hpp --------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  Keycodes.hpp
/// \brief This file defines the appropriate key codes based on the platform.
//
//==------------------------------------------------------------------------==//

#ifndef VOXEL_LUMOS_EVENT_KEYCODES_HPP
#define VOXEL_LUMOS_EVENT_KEYCODES_HPP

#if defined(VOXX_PLATFORM_LINUX) || defined(VOXX_PLATFORM_LINUX)
	#include "KeycodesXcb.hpp"
#endif

#endif // VOXEL_LUMOS_EVENT_KEYCODES_HPP