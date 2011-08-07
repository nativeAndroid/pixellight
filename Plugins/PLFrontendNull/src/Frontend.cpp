/*********************************************************\
 *  File: Frontend.cpp                                   *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Timing.h>
#include <PLCore/System/System.h>
#include "PLFrontendNull/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendNull {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Frontend)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Frontend::Frontend() :
	m_cFrontend(*this),
	m_nTimeToWait(0)
{
	// Do the frontend lifecycle thing - let the world know that we have been created
	OnCreate();
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
	// Do the frontend lifecycle thing - let the world know that we're going to die
	OnDestroy();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::FrontendImpl functions        ]
//[-------------------------------------------------------]
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sApplicationClass)
{
	// Do the frontend lifecycle thing - initialize
	if (OnStart()) {
		OnResume();

		// The frontend main loop
		while (m_cFrontend.IsRunning()) {
			// Time to wait?
			if (m_nTimeToWait) {
				// Let the system some time to process other system tasks etc.
				// If this isn't done the CPU usage is always up to 100%!!
				// Please note that there's no guaranty that the resulting FPS always reaches
				// exactly the maximum FPS limit.
				System::GetInstance()->Sleep(m_nTimeToWait);
			}

			// Redraw & ping
			Redraw();
			Ping();
		}

		// Do the frontend lifecycle thing - de-initialize
		OnPause();
		OnStop();

		// Done
		return 0;
	} else {
		// Error!
		return -1;
	}
}

handle Frontend::GetNativeWindowHandle() const
{
	// There's no window handle!
	return NULL_HANDLE;
}

void Frontend::Redraw()
{
	// Let the frontend draw into it's window
	OnDraw();
}

void Frontend::Ping()
{
	// Check if we're allowed to perform an update right now
	if (Timing::GetInstance()->Update(&m_nTimeToWait)) {
		// Let the frontend update it's states
		OnUpdate();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendNull
