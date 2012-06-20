/*********************************************************\
 *  File: TriCubic_Cg.h                                  *
 *      Fragment shader source code - Cg
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


// Source: http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter20.html - "Example 20-2. Bicubic B-Spline Filtering" extended to 3D
// Source (optimizations): "CUDA Cubic B-Spline Interpolation (CI)" - http://www.dannyruijters.nl/cubicinterpolation/ - http://www.dannyruijters.nl/cubicinterpolation/CI.zip - "cubicTex3D_kernel.cu"


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment_Header = STRINGIFY(
// Uniforms
uniform float3 VolumeTextureSize;	// Volume texture size

/**
*  @brief
*    Reconstructs a scalar by using a given position inside the volume
*
*  @param[in] Position
*    Position inside the volume were to reconstruct the scalar, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Reconstructed scalar, usually in the interval [0 .. 1]
*/
float Reconstruction(float3 Position)
{
	// Shift the coordinate from [0, extent] to [-0.5, extent-0.5]
	// -> OpenGL centers texels at 0.5
	float3 coord_grid = Position*VolumeTextureSize - float3(0.5, 0.5, 0.5);
	float3 index = floor(coord_grid);

	// Calculate weights using a cubic B-spline and calculate the periodic g and h functions
	float3 fraction = coord_grid - index;
	float3 one_frac = float3(1.0, 1.0, 1.0) - fraction;
	float3 squared = fraction*fraction;
	float3 one_sqd = one_frac*one_frac;
	float3 w0 = 1.0/6.0*one_sqd*one_frac;
	float3 w1 = 2.0/3.0 - 0.5*squared*(2.0 - fraction);
	float3 w2 = 2.0/3.0 - 0.5*one_sqd*(2.0 - one_frac);
	float3 w3 = 1.0/6.0*squared*fraction;
	float3 g0 = w0 + w1;
	float3 g1 = w2 + w3;
	float3 h0 = ((w1/g0) - 0.5 + index)/VolumeTextureSize;	// h0 = w1/g0 - 1, move from [-0.5, extent-0.5] to [0, extent]
	float3 h1 = ((w3/g1) + 1.5 + index)/VolumeTextureSize;	// h1 = w3/g1 + 1, move from [-0.5, extent-0.5] to [0, extent]

	// Call the fetch scalar function
	//     float FetchScalar(float3 Position)

	// Fetch the eight linear interpolations
	// -> Weighting and fetching is interleaved for performance and stability reasons
	float tex000 = FetchScalar(vec3(h0.x, h0.y, h0.z));
	float tex100 = FetchScalar(vec3(h1.x, h0.y, h0.z));
	tex000 = g0.x*tex000 + g1.x*tex100;	// Weight along the x-direction
	float tex010 = FetchScalar(vec3(h0.x, h1.y, h0.z));
	float tex110 = FetchScalar(vec3(h1.x, h1.y, h0.z));
	tex010 = g0.x*tex010 + g1.x*tex110;	// Weight along the x-direction
	tex000 = g0.y*tex000 + g1.y*tex010;	// Weight along the y-direction

	float tex001 = FetchScalar(vec3(h0.x, h0.y, h1.z));
	float tex101 = FetchScalar(vec3(h1.x, h0.y, h1.z));
	tex001 = g0.x*tex001 + g1.x*tex101;	// Weight along the x-direction
	float tex011 = FetchScalar(vec3(h0.x, h1.y, h1.z));
	float tex111 = FetchScalar(vec3(h1.x, h1.y, h1.z));
	tex011 = g0.x*tex011 + g1.x*tex111;	// Weight along the x-direction
	tex001 = g0.y*tex001 + g1.y*tex011;	// Weight along the y-direction

	return (g0.z*tex000 + g1.z*tex001);	// Weight along the z-direction
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
