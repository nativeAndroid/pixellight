/*********************************************************\
 *  File: SearchFilterRegEx.cpp                          *
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
#include "PLGeneral/File/SearchFilterRegEx.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SearchFilterRegEx::SearchFilterRegEx(const String &sExpression, uint32 nMode) :
	m_cRegEx(sExpression, nMode)
{
}

/**
*  @brief
*    Destructor
*/
SearchFilterRegEx::~SearchFilterRegEx()
{
}

/**
*  @brief
*    Get expression
*/
String SearchFilterRegEx::GetExpression() const
{
	return m_cRegEx.GetExpression();
}


//[-------------------------------------------------------]
//[ Public virtual SearchFilter functions                 ]
//[-------------------------------------------------------]
bool SearchFilterRegEx::CheckFile(const String &sFilename)
{
	// Check matching
	return m_cRegEx.Match(sFilename);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral