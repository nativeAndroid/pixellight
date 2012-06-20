/*********************************************************\
 *  File: TransferFunctionChannel.inl                    *
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
#include "PLVolume/TransferFunctionControl/TransferFunctionControl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline TransferFunctionChannel::TransferFunctionChannel(TransferFunctionControl &cTransferFunctionControl) :
	m_pTransferFunctionControl(&cTransferFunctionControl)
{
}

/**
*  @brief
*    Copy constructor
*/
inline TransferFunctionChannel::TransferFunctionChannel(const TransferFunctionChannel &cSource) :
	m_pTransferFunctionControl(cSource.m_pTransferFunctionControl),
	m_lstTransferControlPoints(cSource.m_lstTransferControlPoints),
	m_sName(cSource.m_sName),
	m_cVisualizationColor(cSource.m_cVisualizationColor),
	m_lstCubicSplines(cSource.m_lstCubicSplines)
{
}

/**
*  @brief
*    Destructor
*/
inline TransferFunctionChannel::~TransferFunctionChannel()
{
}

/**
*  @brief
*    Copy operator
*/
inline TransferFunctionChannel &TransferFunctionChannel::operator =(const TransferFunctionChannel &cSource)
{
	// Image is now considered to be dirty (previous owner)
	m_pTransferFunctionControl->m_bImageDirty = true;

	// Copy data
	m_pTransferFunctionControl = cSource.m_pTransferFunctionControl;
	m_lstTransferControlPoints = cSource.m_lstTransferControlPoints;
	m_sName					   = cSource.m_sName;
	m_cVisualizationColor	   = cSource.m_cVisualizationColor;
	m_lstCubicSplines		   = cSource.m_lstCubicSplines;

	// Image is now considered to be dirty
	m_pTransferFunctionControl->m_bImageDirty = true;

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Returns the owner transfer function control instance
*/
inline TransferFunctionControl &TransferFunctionChannel::GetTransferFunctionChannel() const
{
	return *m_pTransferFunctionControl;
}

/**
*  @brief
*    Returns the list of transfer control points
*/
inline PLCore::Array<TransferControlPoint> &TransferFunctionChannel::GetTransferControlPoints()
{
	// Cached cubic splines and image are now considered to be dirty
	m_lstCubicSplines.Clear();
	m_pTransferFunctionControl->m_bImageDirty = true;

	// Return the list of transfer control points
	return m_lstTransferControlPoints;
}

/**
*  @brief
*    Returns the list of transfer control points
*/
inline const PLCore::Array<TransferControlPoint> &TransferFunctionChannel::GetTransferControlPoints() const
{
	// Return the list of transfer control points
	return m_lstTransferControlPoints;
}

/**
*  @brief
*    Returns the color to use for channel visualization
*/
inline const PLGraphics::Color3 &TransferFunctionChannel::GetVisualizationColor() const
{
	return m_cVisualizationColor;
}

/**
*  @brief
*    Returns the human readable channel name
*/
inline PLCore::String TransferFunctionChannel::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Sets the human readable channel name
*/
inline void TransferFunctionChannel::SetName(const PLCore::String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Sets the color to use for channel visualization
*/
inline void TransferFunctionChannel::SetVisualizationColor(const PLGraphics::Color3 &cColor)
{
	// Set visualization color
	m_cVisualizationColor = cColor;

	// Image is now considered to be dirty
	m_pTransferFunctionControl->m_bImageDirty = true;
}

/**
*  @brief
*    Returns the list of cubic splines
*/
inline const PLCore::Array<CubicSpline> &TransferFunctionChannel::GetCubicSplines()
{
	// Create cached cubic splines right now?
	if (!m_lstCubicSplines.GetNumOfElements() && m_lstTransferControlPoints.GetNumOfElements())
		CubicSpline::CalculateCubicSpline(m_lstTransferControlPoints.GetNumOfElements() - 1, m_lstTransferControlPoints, m_lstCubicSplines);

	// Return the list of cached cubic splines
	return m_lstCubicSplines;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
