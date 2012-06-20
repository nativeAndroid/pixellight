/*********************************************************\
 *  File: DepthTexture_GLSL.h                            *
 *      Fragment shader source code - GLSL (OpenGL 3.3 ("#version 330")
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
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


// Depth buffer information usage for ray clipping as described within the paper
// "GPU-Based High-Quality Volume Rendering For Virtual Environments" by Andrea Kratz,
// Markus Hadwiger, Anton Fuhrmann, Rainer Splechtna, Katja B�hler and the book
// "Real-Time Volume Graphics", section "11.4.1 Opaque Scene Geometry Intersection with a Ray-Cast Volume" (page 286).


// Template version
static const PLCore::String sSourceCode_Fragment_Template = STRINGIFY(
// Uniforms
uniform sampler2DRect DepthTexture_x_;				// Depth texture map
uniform mat4		  ClipSpaceToObjectSpace_x_;	// Clip space to object space matrix

/**
*  @brief
*    Performs an clipping operation on the given ray
*
*  @param[in, out] RayOrigin
*    Start position of the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*  @param[in]      RayDirection
*    Normalized ray direction
*  @param[in, out] MaximumTravelLength
*    Maximum travel length along the ray, within the interval [0 .. 1]
*/
void ClipRay_x_(inout vec3 RayOrigin, vec3 RayDirection, inout float MaximumTravelLength)
{
	// Compute the homogeneous view-space position
	vec4 hviewpos;
	hviewpos.xy = gl_FragCoord.xy/textureSize(DepthTexture_x_).xy;			// Window position is in [0,1]^2
	hviewpos.z  = texelFetch(DepthTexture_x_, ivec2(gl_FragCoord.xy)).r;	// Depth in [0,1]
	hviewpos.w  = 1.0;

	// We need this to be in [-1,1]^3 clip space
	hviewpos = hviewpos*2.0 - 1.0;

	// Back-project to homogeneous volume space
	vec4 hvolpos = ClipSpaceToObjectSpace_x_*hviewpos;

	// Get normalized volume-space position
	vec4 position = hvolpos/hvolpos.w;

	// Update maximum travel length along the ray
	vec3 delta = position.xyz - RayOrigin;
	float newLength = length(delta);
	if (MaximumTravelLength > newLength)
		MaximumTravelLength = newLength;

	// In case we're drawing backfaces with disabled depth buffer test, we need
	// to check in here whether or not the ray is completely culled
	if (dot(1.0/delta, RayDirection) < 0.0)
		discard;
}
);	// STRINGIFY

// None-template version
static const PLCore::String sSourceCode_Fragment = sSourceCode_Fragment_Template + '\n' + STRINGIFY(
// None-template version
void ClipRay(inout vec3 RayOrigin, vec3 RayDirection, inout float MaximumTravelLength)
{
	// Call the function version also used by the template
	ClipRay_x_(RayOrigin, RayDirection, MaximumTravelLength);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY