/*********************************************************\
 *  File: RTTIObjectPointerBase.h                        *
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


#ifndef __PLSCRIPTLUA_RTTIOBJECTPOINTERBASE_H__
#define __PLSCRIPTLUA_RTTIOBJECTPOINTERBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScriptLua/LuaUserData.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Object;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    RTTI object pointer base class
*/
class RTTIObjectPointerBase : public LuaUserData {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class LuaContext;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectPointerBase();

		/**
		*  @brief
		*    Returns the pointer to the RTTI object to wrap
		*
		*  @return
		*    Pointer to the RTTI object to wrap, can be a null pointer
		*/
		PLCore::Object *GetObject() const;

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    Other instance to compare with
		*
		*  @return
		*    'true' if both are equal, else 'false'
		*/
		bool operator ==(const RTTIObjectPointerBase &cOther) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    The Lua user data type
		*/
		RTTIObjectPointerBase(EType nType = TypeObjectPointer);

		/**
		*  @brief
		*    Initializes this instance
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] pRTTIObject
		*    Pointer to the RTTI object to wrap, can be a null pointer
		*/
		void InitializeInstance(Script &cScript, PLCore::Object *pRTTIObject);

		/**
		*  @brief
		*    De-initializes this instance
		*/
		void DeInitializeInstance();


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual int IndexMetamethod(lua_State *pLuaState) override;
		virtual int NewIndexMetamethod(lua_State *pLuaState) override;
		virtual void CallMetamethod(lua_State *pLuaState) override;
		virtual void ToStringMetamethod(lua_State *pLuaState) override;
		virtual int EqualityMetamethod(lua_State *pLuaState) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the RTTI object assigned with this wrapper was destroyed
		*/
		void OnDestroy();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<>  m_cEventHandlerOnDestroy;	/**< "OnDestroy" event handler */
		PLCore::Object		   *m_pRTTIObject;				/**< Pointer to the RTTI object to wrap, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTPOINTERBASE_H__