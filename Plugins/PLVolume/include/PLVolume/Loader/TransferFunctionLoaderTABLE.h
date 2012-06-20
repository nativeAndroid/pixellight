/*********************************************************\
 *  File: TransferFunctionLoaderTABLE.h                  *
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


#ifndef __PLVOLUME_TRANSFERFUNCTIONLOADER_TABLE_H__
#define __PLVOLUME_TRANSFERFUNCTIONLOADER_TABLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolume/TransferFunctionLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TransferFunction;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Transfer function loader implementation for the "TABLE" file format from the University of Erlangen, Germany
*
*  @note
*    - The file format specification is online available at http://openqvis.sourceforge.net/docu/fileformat.html
*    - Sample data sets are available at http://openqvis.sourceforge.net/ and http://www.voreen.org/108-Data-Sets.html
*/
class TransferFunctionLoaderTABLE : public TransferFunctionLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, TransferFunctionLoaderTABLE, "PLVolume", PLVolume::TransferFunctionLoader, "Transfer function loader implementation for the \"TABLE\" file format from the University of Erlangen, Germany")
		// Properties
		pl_properties
			pl_property("Formats",	"table,TABLE")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,	pl_ret_type(bool),	TransferFunction&,			PLCore::File&,	"Load method",	"")
		pl_method_2(Save,	pl_ret_type(bool),	const TransferFunction&,	PLCore::File&,	"Save method",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(TransferFunction &cTransferFunction, PLCore::File &cFile);
		bool Save(const TransferFunction &cTransferFunction, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		TransferFunctionLoaderTABLE();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TransferFunctionLoaderTABLE();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_TRANSFERFUNCTIONLOADER_TABLE_H__
