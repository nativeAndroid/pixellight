/*********************************************************\
 *  File: Context_GDCM.cpp                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Log/Log.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4530)	// "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <gdcm/Common/gdcmTypes.h>
PL_WARNING_POP
#include "PLLoaderDICOM_GDCM/Context_GDCM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLLoaderDICOM_GDCM {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
uint32			   Context_GDCM::m_nContextCounter = 0;
std::ostringstream Context_GDCM::m_stdOStringStream;


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a context reference
*/
void Context_GDCM::AddReference()
{
	// Check context
	if (!m_nContextCounter) {
		PL_LOG(Info, String("Initialize GDCM ") + GDCM_VERSION)

		// Ensure GDCM debug, warning and error trace is enabled
		gdcm::Trace::DebugOff();	// By default, disable the debug output or else GDCM will spam the log with more or less useless information
		gdcm::Trace::WarningOn();
		gdcm::Trace::ErrorOn();
		gdcm::Trace::SetStream(m_stdOStringStream);
	}
	m_nContextCounter++;
}

/**
*  @brief
*    Releases a context reference
*/
void Context_GDCM::ReleaseReference()
{
	// Check context
	m_nContextCounter--;
	if (!m_nContextCounter)
		PL_LOG(Info, String("De-initialize GDCM ") + GDCM_VERSION)
}

/**
*  @brief
*    Flush the GDCM trace into the PixelLight log
*/
void Context_GDCM::FlushTraceToLog()
{
	PL_LOG(Warning, m_stdOStringStream.str().c_str())
	m_stdOStringStream.clear();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLLoaderDICOM_GDCM
