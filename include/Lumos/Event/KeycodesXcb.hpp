//==--- Lumos/Event/KeycodesXcb.hpp ------------------------ -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  KeycodesXcb.hpp
/// \brief This file defines key codes for XCB
//
//==------------------------------------------------------------------------==//

#ifndef VOXEL_LUMOS_EVENT_KEYCODES_XCB_HPP
#define VOXEL_LUMOS_EVENT_KEYCODES_XCB_HPP

namespace Voxx::Lumos {

enum class KeyEventKind : uint8_t {
	Esc 	= 0x09,
	W 		= 0x19,
	A 		= 0x26,
	S 		= 0x27,
	D 		= 0x28,
	Space	= 0x41,
	F1 	  = 0x43,
	F2 	 	= 0x44,
	F3 		= 0x45,
	F4 		= 0x46
	Sub 	= 0x52,
	Add 	= 0x56,
};

} // namespace Voxx::Lumos

#endif // VOXEL_LUMOS_EVENT_KEYCODES_XCB_HPP