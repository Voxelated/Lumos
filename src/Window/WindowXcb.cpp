//==--- Lumos/Window/WindowXcb.cpp ------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Lumos
//
//                        Copyright (c) 2018 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  WindowXcb.cpp
/// \brief This is the implementation file for a Window class which uses XCB.
//
//==------------------------------------------------------------------------==//

#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "WindowXcb.hpp"

WindowXcb::WindowResource {
 	/// The type of a pointer to the connection to the server.
 	using ConnectionPtr 	= xcb_connection_t*;
 	/// The type of a pointer to the screen object.
 	using ScreenPtr 			= xcb_screen_t*;
 	/// The type of the X window.
 	using WindowType 		  = xcb_window_t;

 	Display* 			display 	 		= nullptr; 	//!< A pointer to the display.
 	ConnectionPtr	connection 	 	= nullptr;	//!< A pointer to the connection.
 	ScreenPtr 		screen 			 	= nullptr;	//!< A pointer to the screen.
 	WindowType		window 			 	= 0;				//!< A handle to the XCB window.
 	int 					screenNumber 	= 0; 				//!< The screen number to use.
};

WindowXcb::GraphicsResource {
	GLXContext  context;		//!< A handle to the OpenGL context.
	GLXWindow   window;			//!< A handle to the OpenGL window.
	GLXDrawable drawable;		//!< A handle to the OpenGL drawable object.
}

WindowXcb::WindowXcb() {
	GraphicsHandle = new GraphicsHandle();
	WindowHandle   = new WindowResource();
}

WindowXcb::~WindowXcb() {
	if (GraphicsHandle) {
		if (WindowHandle) {
			glXDestroyWindow(WindowHandle->display, GraphicsHandle->window);
			xcb_destroy_window(WindowHandle->connection, WindowHandle->window);
			glXDestroyContext(WindowHandle->display, GraphicsHandle->context);
			XCloseDisplay(WindowHandle->display);
			delete WindowHandle;
		}
		delete GraphicsHandle;
	}
}

WindowXcb::WindowPtr WindowXcb::create(Extent2d extent, const char* title) {
	auto* window   = WindowHandle;
	auto* graphics = GraphicsHandle;
	if (!(window->display = XOpenDisplay(0))) {
		fprintf(stderr, "Can't open display!\n");
		return nullptr;
	}
	window->screenNumber = DefaultScreen(window->display);

	if (!(window->connection = XGetXCBConnection(window->display))) {
		XCloseDisplay(window->display);
		fprintf(stderr, "Can't get XCB connection from display!\n");
		return nullptr;
	}
	XSetEventQueueOwnership(window->display, XCBOwnsEventQueue);

	// Find the XCB screen to use:
	xcb_screen_iterator_t screenIterator = 
		xcb_setup_roots_iterator(xcb_get_setup(window->connection));
	for (auto screenNumber = window->screenNumber;
			 screenIterator.rem && screenNumber > 0;
			 --screenNumber, xcb_screen_next(&screenIterator)) {
		window->screen = screen_iter.data;
	}
}

void WindowXcb::setup(Extent2d extent) {
	auto* window   	= WindowHandle;
	auto* graphics 	= GraphicsHandle;

  int visualID = 0, numFbufferConfigs = 0;
  auto fbufferConfigs = glXGetFBConfigs(window->display 		,
  																			window->screenNumber,
  																			&numFbufferConfigs  );
  if (!fbufferConfigs || numFbufferConfigs == 0) {
  	fprintf(stderr, "Frame buffer configuration failed!\n");
    return;
  }

  GLXFBConfig fbufferConfig = fbufferConfigs[0];
  glXGetFBConfigAttrib(window->display,
  										 fbufferConfig  ,
  										 GLX_VISUAL_ID  ,
  										 &visualID 			);

  graphics->context = glXCreateNewContext(window->display,
  		  																	fbufferConfig  ,
  																				GLX_RGBA_TYPE  ,
  																				0						   ,
  																				True 			  	);
  if (!graphics->context) {
  	fprintf(stderr, "Failed to create new GLX context!\n");
    return;
  }

  xcb_colormap_t colormap = xcb_generate_id(window->connection);
  xcb_create_colormap(window->connection 		 ,
      								XCB_COLORMAP_ALLOC_NONE,
      								colormap 							 ,
      								window->screen->root 	 ,
      								visualID 							 );

  uint32_t eventMask   	= XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
  uint32_t valueList[] 	= { eventMask, colormap, 0 };
  uint32_t valueMask   	= XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;
  Xcb.window = xcb_generate_id(window->connection);
	xcb_create_window(window->connection 					 ,
            				XCB_COPY_FROM_PARENT				 ,
            				window->window 							 ,
            				window->screen->root 				 ,
            				0 													 ,
            				0 													 ,
            				extent.width								 ,
            				extent.height								 ,
            				0 													 ,
            				XCB_WINDOW_CLASS_INPUT_OUTPUT,
            				visualID 										 ,
            				valueMask 									 ,
            				valueList										 );

  // NOTE: window must be mapped before glXMakeContextCurrent.
  xcb_map_window(window->connection, window->window); 

  Glx.Window = glXCreateWindow(window->display, fbConfig, window->window, 0);
  if (!window->window) {
   	xcb_destroy_window(window->connection, window->window);
    glXDestroyContext(window->display, graphics->context);

    fprintf(stderr, "Failed to destroy GLX context!\n");
    return -1;
  }
	graphics->drawable = window->window;

	// Make the OpenGL context current:
  if (!glXMakeContextCurrent(window->display   ,
  													 graphics->drawable,
  													 graphics->drawable,
  													 graphics->context )) {
  	xcb_destroy_window(window->connection, window->window);
    glXDestroyContext(window->display, graphics->context);

    fprintf(stderr, "Failed to make OpenGL context current!\n");
    return;
  }
}

void WindowXcb::pollForEvent(EventManager& eventManager) {
	auto* window = WindowHandle;
	xcb_flush(window->connection);
	xcb_generic_event_t* event;
	constexpr uint8_t eventMask = 0x7f;
	while ((event = xcb_poll_for_event(event))) {
		switch (event->response_type & eventMask) {
			case XCB_KEY_PRESS: {
				KeyEvent keyEvent(EventActionKind::Press);

			}
			break;
			case XCB_KEY_RELEASE: {
				KeyEvent keyEvent(EventActionKind::Release);
			}
			break;
		}
	}
	free(event);
}