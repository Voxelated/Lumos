//==--- Lumos/Geometry/Extent.hpp -------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  Extent.hpp
/// \brief This file defines a classes which define sizes in multiple
///        dimensions.
//
//==------------------------------------------------------------------------==//

/// The Extent struct defines an object which holds the size of single
/// dimension.
struct Extent {
	int16_t length; //!< The length of the extent.
}

/// The Extent2d struct defines an object which holds the sizes of the
/// dimensions for two dimensions.
struct Extent2d {
	int16_t width;	//!< The width of the extent.
	int16_t height;	//!< The height of the extent.
};

/// The Extent 3d struct defines an object which holds the sizes of the
/// dimensions for three dimensions.
struct Extent3d {
	int16_t width;	//!< The width of the extent.
	int16_t height;	//!< The height of the extent.
	int16_t depth; 	//!< The depth of the extent.
};