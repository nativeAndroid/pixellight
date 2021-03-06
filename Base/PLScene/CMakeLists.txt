#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the "Software"), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## Project
##################################################
define_project(PLScene)

##################################################
## Source files
##################################################
add_sources(
	src/Scene/SceneNodes/Loader/SkinLoader.cpp
	src/Scene/SceneNodes/Loader/SkinLoaderPL.cpp
	src/Scene/SceneNodes/SNCoordinateAxis.cpp
	src/Scene/SceneNodes/SNLineGrid.cpp
	src/Scene/SceneNodes/SNString.cpp
	src/Scene/SceneNodes/SNEventArea.cpp
	src/Scene/SceneNodes/SNCoordinateAxisRotation.cpp
	src/Scene/SceneNodes/SNText.cpp
	src/Scene/SceneNodes/SNText2D.cpp
	src/Scene/SceneNodes/SNText3D.cpp
	src/Scene/SceneNodes/SNKeyValue.cpp
	src/Scene/SceneNodes/SCRenderToTexture.cpp
	src/Scene/SceneNodes/SNHelper.cpp
	src/Scene/SceneNodes/SNUnknown.cpp
	src/Scene/SceneNodes/SCUnknown.cpp
	src/Scene/SceneNodes/SCMirror.cpp
	src/Scene/SceneNodes/SNLineBox.cpp
	src/Scene/SceneNodes/SNCoordinateAxis3D.cpp
	src/Scene/SceneNodes/SNArea.cpp
	src/Scene/SceneNodes/SNBitmap.cpp
	src/Scene/SceneNodes/SNBitmap2D.cpp
	src/Scene/SceneNodes/SNBitmap3D.cpp
	src/Scene/SceneNodes/SNLine.cpp
	src/Scene/SceneNodes/SNPoint.cpp
	src/Scene/SceneNodes/SNMesh.cpp
	src/Scene/SceneNodeModifiers/SNMAnchor.cpp
	src/Scene/SceneNodeModifiers/SNMTransform.cpp
	src/Scene/SceneNodeModifiers/SNMTransformGizmo.cpp
	src/Scene/SceneNodeModifiers/SNMTransformGizmoPosition.cpp
	src/Scene/SceneNodeModifiers/SNMTransformGizmoRotation.cpp
	src/Scene/SceneNodeModifiers/SNMTransformGizmoScale.cpp
	src/Scene/SceneNodeModifiers/SNMPositionPath.cpp
	src/Scene/SceneNodeModifiers/SNMPositionMoveToTarget.cpp
	src/Scene/SceneNodeModifiers/SNMPositionLinearAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMPositionKeyframeAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMScaleKeyframeAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMRotationTarget.cpp
	src/Scene/SceneNodeModifiers/SNMRotationFixRoll.cpp
	src/Scene/SceneNodeModifiers/SNMRotationMoveDirection.cpp
	src/Scene/SceneNodeModifiers/SNMRotationLinearAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMRotationKeyframeAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMBillboard.cpp
	src/Scene/SceneNodeModifiers/SNMBillboardSpherical.cpp
	src/Scene/SceneNodeModifiers/SNMBillboardCylindrical.cpp
	src/Scene/SceneNodeModifiers/SNMMesh.cpp
	src/Scene/SceneNodeModifiers/SNMMeshMorph.cpp
	src/Scene/SceneNodeModifiers/SNMMeshJoint.cpp
	src/Scene/SceneNodeModifiers/SNMMeshUpdate.cpp
	src/Scene/SceneNodeModifiers/SNMMeshAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMMeshMorphBlink.cpp
	src/Scene/SceneNodeModifiers/SNMMeshMorphCameraNear.cpp
	src/Scene/SceneNodeModifiers/SNMDraw.cpp
	src/Scene/SceneNodeModifiers/SNMDrawRectangle.cpp
	src/Scene/SceneNodeModifiers/SNMKeyValue.cpp
	src/Scene/SceneNodeModifiers/SNMDeactivationOnTimeout.cpp
	src/Scene/SceneNodeModifiers/SNMOrbiting.cpp
	src/Scene/SceneNodeModifiers/SNMUnknown.cpp
	src/Scene/SceneNodeModifiers/SNMCameraZoom.cpp
	src/Scene/SceneNodeModifiers/SNMPositionRandomAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMScaleRandomAnimation.cpp
	src/Scene/SceneNodeModifiers/SNMLightRandomAnimation.cpp
	src/Scene/SceneLoader/SceneLoader.cpp
	src/Scene/SceneLoader/SceneLoaderPL.cpp
	src/Scene/SceneQueries/SQAABoundingBox.cpp
	src/Scene/SceneQueries/SQPlaneSet.cpp
	src/Scene/SceneQueries/SQEnumerate.cpp
	src/Scene/SceneQueries/SQSphere.cpp
	src/Scene/SceneQueries/SQLine.cpp
	src/Scene/SceneQueries/SQPoint.cpp
	src/Scene/SceneQueries/SQByName.cpp
	src/Scene/SceneQueries/SQByClassName.cpp
	src/Scene/SceneHierarchies/SHList.cpp
	src/Scene/SceneHierarchies/SHKdTree.cpp
	src/Scene/SceneHierarchyNode.cpp
	src/Scene/SceneContainer.cpp
	src/Scene/SceneNodeHandler.cpp
	src/Scene/SNPortal.cpp
	src/Scene/SNCellPortal.cpp
	src/Scene/SNAntiPortal.cpp
	src/Scene/SNEffectLight.cpp
	src/Scene/SceneNode.cpp
	src/Scene/SCCell.cpp
	src/Scene/SNFog.cpp
	src/Scene/SPScene.cpp
	src/Scene/SNProjectiveSpotLight.cpp
	src/Scene/SNSpotLight.cpp
	src/Scene/SNProjectivePointLight.cpp
	src/Scene/SceneHierarchyNodeItem.cpp
	src/Scene/SceneQueryManager.cpp
	src/Scene/SNLight.cpp
	src/Scene/SceneContext.cpp
	src/Scene/SceneQueryHandler.cpp
	src/Scene/SNPointLight.cpp
	src/Scene/SceneNodeModifier.cpp
	src/Scene/SNSphereFog.cpp
	src/Scene/SNCamera.cpp
	src/Scene/SceneQuery.cpp
	src/Scene/SNDirectionalLight.cpp
	src/Scene/SceneHierarchy.cpp
	src/Visibility/SQCull.cpp
	src/Visibility/VisManager.cpp
	src/Visibility/VisNode.cpp
	src/Visibility/VisContainer.cpp
	src/Visibility/VisPortal.cpp
	src/Compositing/SceneRendererLoaderPL.cpp
	src/Compositing/SceneRendererLoader.cpp
	src/Compositing/SceneRenderer.cpp
	src/Compositing/SceneRendererHandler.cpp
	src/Compositing/SceneRendererManager.cpp
	src/Compositing/SceneRendererPass.cpp
	src/Application/SceneApplication.cpp
	src/PLScene.cpp
)

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	${CMAKE_SOURCE_DIR}/Base/PLMath/include
	${CMAKE_SOURCE_DIR}/Base/PLGraphics/include
	${CMAKE_SOURCE_DIR}/Base/PLRenderer/include
	${CMAKE_SOURCE_DIR}/Base/PLMesh/include
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_LIB_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
	PLCore
	PLMath
	PLGraphics
	PLRenderer
	PLMesh
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_libs(
		${WIN32_USER32_LIB}
		${WIN32_ADVAPI32_LIB}
		${WIN32_WINMM_LIB}
	)
endif()

##################################################
## Preprocessor definitions
##################################################
add_compile_defs(
	PLSCENE_EXPORTS
)
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_compile_defs(
		${LINUX_COMPILE_DEFS}
	)
endif()

##################################################
## Compiler flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_compile_flags(
		${WIN32_COMPILE_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_compile_flags(
		${LINUX_COMPILE_FLAGS}
	)
endif()

##################################################
## Linker flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_linker_flags(
		${WIN32_LINKER_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_linker_flags(
		${LINUX_LINKER_FLAGS}
	)
endif()

##################################################
## Build
##################################################
build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
pl_create_plugin_description(${CMAKE_CURRENT_SOURCE_DIR} ${PL_RUNTIME_BIN_DIR})

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore PLMath PLGraphics PLRenderer PLMesh)
add_dependencies(Base                       	${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

# Dynamic library
add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_RUNTIME_BIN_DIR}
)

# Create relative symbolic links?
if(LINUX AND CMAKETOOLS_DETAILED_VERSION_INFORMATION)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKETOOLS_CURRENT_SHARED_LIB} ${CMAKETOOLS_CURRENT_SHARED_LIB_SO_VERSION} WORKING_DIRECTORY ${PL_RUNTIME_BIN_DIR}
	)
endif()

# Import library
if(WIN32)
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_STATIC_LIB} ${PL_LIB_DIR}
	)
endif()

##################################################
## Install
##################################################

# Library
install(TARGETS ${CMAKETOOLS_CURRENT_TARGET}
	RUNTIME DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	LIBRARY DESTINATION ${PL_INSTALL_RUNTIME_BIN}	COMPONENT Runtime
	ARCHIVE DESTINATION ${PL_INSTALL_LIB}			COMPONENT SDK
)

# Include files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKETOOLS_CURRENT_PROJECT}
	DESTINATION ${PL_INSTALL_INCLUDE} 				COMPONENT SDK		REGEX ${PL_EXCLUDE_FILE_EXTENSIONS} EXCLUDE
)

# Plugin file
install(FILES ${PL_RUNTIME_BIN_DIR}/${CMAKETOOLS_CURRENT_PLUGIN}
	DESTINATION ${PL_INSTALL_RUNTIME_BIN}			COMPONENT Runtime
)
