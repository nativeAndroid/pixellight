/*********************************************************\
 *  File: SNMTransformGizmoScale.cpp                     *
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
#include <PLMath/Ray.h>
#include <PLMath/Intersect.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Font.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLMesh/MeshManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMTransformGizmoScale.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLMesh;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMTransformGizmoScale)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMTransformGizmoScale::SNMTransformGizmoScale(SceneNode &cSceneNode) : SNMTransformGizmo(cSceneNode),
	m_pMeshHandler(new MeshHandler())
{
	// Get/create the 'cone' mesh for the axis arrow
	MeshManager &cMeshManager = GetSceneNode().GetSceneContext()->GetMeshManager();
	Mesh		*pMesh		  = cMeshManager.GetByName("SNTransformGizmo_scale_sphere");
	if (!pMesh) {
		// Create mesh
		pMesh = cMeshManager.CreateMesh("PLMesh::MeshCreatorSphere", true, "Radius=\"0.4\"' Detail=\"10\"");
		if (pMesh)
			pMesh->SetName("SNTransformGizmo_scale_sphere");
	}
	m_pMeshHandler->SetMesh(pMesh);
}

/**
*  @brief
*    Destructor
*/
SNMTransformGizmoScale::~SNMTransformGizmoScale()
{
	delete m_pMeshHandler;
}


//[-------------------------------------------------------]
//[ Protected virtual SNMTransformGizmo functions         ]
//[-------------------------------------------------------]
uint32 SNMTransformGizmoScale::DetermineSelected(const Ray &cRay) const
{
	uint32 nSelected = 0;

	// Perform ray/triangle collision detection for multiple axis selection. The distance found collision
	// is used. The XYZ-triangles are topmost.
	// XYZ
	Vector3 vN, vV;
	vN.GetFaceNormal(Vector3(5.0f, 0.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f));
	if (Intersect::TriangleRay(Vector3(5.0f, 0.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), vN,                     cRay, &vV) ||
		Intersect::TriangleRay(Vector3::Zero,             Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), Vector3::NegativeUnitX, cRay, &vV) ||
		Intersect::TriangleRay(Vector3(5.0f, 0.0f, 0.0f), Vector3::Zero,             Vector3(0.0f, 0.0f, 5.0f), Vector3::NegativeUnitY, cRay, &vV) ||
		Intersect::TriangleRay(Vector3(5.0f, 0.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3::Zero,             Vector3::NegativeUnitZ, cRay, &vV)) {
		nSelected = XAxis | YAxis | ZAxis;
	} else {
		Vector3 vMax = cRay.GetPos();

		// XY
		if (Intersect::TriangleRay(Vector3(0.0f, 8.0f, 0.0f), Vector3(8.0f, 0.0f, 0.0f), Vector3(5.0f, 0.0f, 0.0f), Vector3::UnitZ, cRay, &vV) ||
			Intersect::TriangleRay(Vector3(0.0f, 8.0f, 0.0f), Vector3(5.0f, 0.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3::UnitZ, cRay, &vV)) {
			vMax = vV;
			nSelected = XAxis | YAxis;
		}

		// XZ
		if ((Intersect::TriangleRay(Vector3(0.0f, 0.0f, 5.0f), Vector3(5.0f, 0.0f, 0.0f), Vector3(8.0f, 0.0f, 0.0f), Vector3::UnitY, cRay, &vV) ||
				Intersect::TriangleRay(Vector3(0.0f, 0.0f, 5.0f), Vector3(8.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 8.0f), Vector3::UnitY, cRay, &vV)) &&
			(cRay.GetPos()-vV).GetSquaredLength() > (cRay.GetPos()-vMax).GetSquaredLength()) {
			vMax = vV;
			nSelected = XAxis | ZAxis;
		}

		// YZ
		if ((Intersect::TriangleRay(Vector3(0.0f, 0.0f, 8.0f), Vector3(0.0f, 8.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3::UnitX, cRay, &vV) ||
				Intersect::TriangleRay(Vector3(0.0f, 0.0f, 8.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), Vector3::UnitX, cRay, &vV)) &&
			(cRay.GetPos()-vV).GetSquaredLength() > (cRay.GetPos()-vMax).GetSquaredLength()) {
			vMax = vV;
			nSelected = YAxis | ZAxis;
		}
	}

	// If no multiple axis selection was found, check whether a single axis is selected. This is done
	// by calculating a ray/plane intersection of the plane the axis is on. Then the closest point on the
	// axis line to this ray/plane intersection point is calculated. If this two point are not too far away
	// the given axis is selected.
	if (!nSelected) {
		// X axis
		Plane cPlane;
		cPlane.ComputeND(Vector3::Zero, Vector3::UnitY);
		vV = Intersect::PlaneRay(cPlane, cRay.GetPos(), cRay.GetDir());
		Vector3 vMin = vV.ClosestPointOnLine(Vector3::Zero, Vector3(10.0f, 0.0f, 0.0f));
		if ((vMin-vV).GetSquaredLength() < 0.6f) {
			nSelected = XAxis;
		} else {
			// Try another plane for sure
			cPlane.ComputeND(Vector3::Zero, Vector3::UnitZ);
			vV    = Intersect::PlaneRay(cPlane, cRay.GetPos(), cRay.GetDir());
			vMin  = vV.ClosestPointOnLine(Vector3::Zero, Vector3(10.0f, 0.0f, 0.0f));
			if ((vMin-vV).GetSquaredLength() < 0.6f)
				nSelected = XAxis;
		}

		// Y axis
		cPlane.ComputeND(Vector3::Zero, Vector3::UnitX);
		vV    = Intersect::PlaneRay(cPlane, cRay.GetPos(), cRay.GetDir());
		vMin  = vV.ClosestPointOnLine(Vector3::Zero, Vector3(0.0f, 10.0f, 0.0f));
		if ((vMin-vV).GetSquaredLength() < 0.6f) {
			nSelected = YAxis;
		} else {
			// Try another plane for sure
			cPlane.ComputeND(Vector3::Zero, Vector3::UnitZ);
			vV    = Intersect::PlaneRay(cPlane, cRay.GetPos(), cRay.GetDir());
			vMin  = vV.ClosestPointOnLine(Vector3::Zero, Vector3(0.0f, 10.0f, 0.0f));
			if ((vMin-vV).GetSquaredLength() < 0.6f)
				nSelected = YAxis;
		}

		// Z axis
		cPlane.ComputeND(Vector3::Zero, Vector3::UnitY);
		vV    = Intersect::PlaneRay(cPlane, cRay.GetPos(), cRay.GetDir());
		vMin = vV.ClosestPointOnLine(Vector3::Zero, Vector3(0.0f, 0.0f, 10.0f));
		if ((vMin-vV).GetSquaredLength() < 0.6f) {
			nSelected = ZAxis;
		} else {
			// Try another plane for sure
			cPlane.ComputeND(Vector3::Zero, Vector3::UnitX);
			vV    = Intersect::PlaneRay(cPlane, cRay.GetPos(), cRay.GetDir());
			vMin = vV.ClosestPointOnLine(Vector3::Zero, Vector3(0.0f, 0.0f, 10.0f));
			if ((vMin-vV).GetSquaredLength() < 0.6f)
				nSelected = ZAxis;
		}
	}

	// Return the selected axis
	return nSelected;
}

void SNMTransformGizmoScale::DrawGizmo(Renderer &cRenderer, const VisNode *pVisNode)
{
	// This method does not need to be hightly effective because it's usually only called once per frame, so we prefere the generic way

	// The object space coordinate system we draw in is 10x10x10 so we don't have to work with to small numbers
	float fScale = 1.0f;

	// Get primary axis color (changed when axis is selected)
	const Color4 &cPrimaryXAxisColor = (m_nSelected & XAxis) ? Color4::Yellow : Color4::Red;
	const Color4 &cPrimaryYAxisColor = (m_nSelected & YAxis) ? Color4::Yellow : Color4::Green;
	const Color4 &cPrimaryZAxisColor = (m_nSelected & ZAxis) ? Color4::Yellow : Color4::Blue;

	// Setup render states
	cRenderer.GetRendererContext().GetEffectManager().Use();
	cRenderer.SetRenderState(RenderState::CullMode,     Cull::None);
	cRenderer.SetRenderState(RenderState::ZEnable,      false);
	cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

	// [TODO] Remove the direct usage of fixed functions in here
	// Fixed functions support required
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		// Set translation matrix (rotation & scale has no influence on the transform gizmo)
		Matrix4x4 mTranslation;
		mTranslation.SetTranslationMatrix(pVisNode->GetWorldMatrix().GetTranslation());
		fScale = SetScaledWorldMatrix(cRenderer, mTranslation);

		{ // Draw sphere meshes
			Matrix4x4 mLocal;

			// Draw X sphere mesh
			mLocal.FromEulerAngleZ(static_cast<float>(-90.0f*Math::DegToRad));
			mLocal.SetTranslation(10.0f, 0.0f, 0.0f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mTranslation*mLocal);
			pFixedFunctions->SetColor(cPrimaryXAxisColor);
			m_pMeshHandler->Draw(false, false);

			// Draw Y sphere mesh
			mLocal.SetTranslationMatrix(0.0f, 10.0f, 0.0f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mTranslation*mLocal);
			pFixedFunctions->SetColor(cPrimaryYAxisColor);
			m_pMeshHandler->Draw(false, false);

			// Draw Z sphere mesh
			mLocal.FromEulerAngleX(static_cast<float>(90.0f*Math::DegToRad));
			mLocal.SetTranslation(0.0f, 0.0f, 10.0f);
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mTranslation*mLocal);
			pFixedFunctions->SetColor(cPrimaryZAxisColor);
			m_pMeshHandler->Draw(false, false);
		}
	}

	// Get object space to clip space matrix (rotation & scale has no influence on the transform gizmo)
	Matrix4x4 mObjectSpaceToClipSpace;
	{ // Apply world translation
		// Construct translation matrix
		Matrix4x4 mTranslation;
		mTranslation.SetTranslationMatrix(pVisNode->GetWorldMatrix().GetTranslation());

		// Calculate the world view projection transform matrix
		mObjectSpaceToClipSpace = pVisNode->GetViewProjectionMatrix()*mTranslation;
	}
	{ // Apply scale
		Matrix3x4 mScale;
		mScale.SetScaleMatrix(fScale, fScale, fScale);
		mObjectSpaceToClipSpace *= mScale;
	}

	// Get draw helpers instance
	DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
	const float fLineWidth = 2.0f;

	{ // Draw axis lines
		// X axis
		if (!(m_nSelected & XAxis) || !(m_nSelected & YAxis) || !(m_nSelected & ZAxis))
			cDrawHelpers.DrawLine(cPrimaryXAxisColor, Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 0.0f, 0.0f), mObjectSpaceToClipSpace, fLineWidth);
		{ // XY
			const Color4 &cColor = (m_nSelected & XAxis) && (m_nSelected & YAxis) ? Color4::Yellow : Color4::Red;
			cDrawHelpers.DrawLine(cColor, Vector3(5.0f, 0.0f, 0.0f), Vector3(2.5f, 2.5f, 0.0f), mObjectSpaceToClipSpace, fLineWidth);
			cDrawHelpers.DrawLine(cColor, Vector3(8.0f, 0.0f, 0.0f), Vector3(4.0f, 4.0f, 0.0f), mObjectSpaceToClipSpace, fLineWidth);
		}
		{ // XZ
			const Color4 &cColor = ((m_nSelected & XAxis) && (m_nSelected & ZAxis)) ? Color4::Yellow : Color4::Red;
			cDrawHelpers.DrawLine(cColor, Vector3(5.0f, 0.0f, 0.0f), Vector3(2.5f, 0.0f, 2.5f), mObjectSpaceToClipSpace, fLineWidth);
			cDrawHelpers.DrawLine(cColor, Vector3(8.0f, 0.0f, 0.0f), Vector3(4.0f, 0.0f, 4.0f), mObjectSpaceToClipSpace, fLineWidth);
		}

		// Y axis
		if (!(m_nSelected & XAxis) || !(m_nSelected & YAxis) || !(m_nSelected & ZAxis))
			cDrawHelpers.DrawLine(cPrimaryYAxisColor, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 10.0f, 0.0f), mObjectSpaceToClipSpace, fLineWidth);
		{ // XY
			const Color4 &cColor = ((m_nSelected & XAxis) && (m_nSelected & YAxis)) ? Color4::Yellow : Color4::Green;
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 5.0f, 0.0f), Vector3(2.5f, 2.5f, 0.0f), mObjectSpaceToClipSpace, fLineWidth);
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 8.0f, 0.0f), Vector3(4.0f, 4.0f, 0.0f), mObjectSpaceToClipSpace, fLineWidth);
		}
		{ // YZ
			const Color4 &cColor = ((m_nSelected & YAxis) && (m_nSelected & ZAxis)) ? Color4::Yellow : Color4::Green;
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 2.5f, 2.5f), mObjectSpaceToClipSpace, fLineWidth);
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 8.0f, 0.0f), Vector3(0.0f, 4.0f, 4.0f), mObjectSpaceToClipSpace, fLineWidth);
		}

		// Z axis
		if (!(m_nSelected & XAxis) || !(m_nSelected & YAxis) || !(m_nSelected & ZAxis))
			cDrawHelpers.DrawLine(cPrimaryZAxisColor, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 10.0f), mObjectSpaceToClipSpace, fLineWidth);
		{ // XZ
			const Color4 &cColor = ((m_nSelected & XAxis) && (m_nSelected & ZAxis)) ? Color4::Yellow : Color4::Blue;
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 0.0f, 5.0f), Vector3(2.5f, 0.0f, 2.5f), mObjectSpaceToClipSpace, fLineWidth);
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 0.0f, 8.0f), Vector3(4.0f, 0.0f, 4.0f), mObjectSpaceToClipSpace, fLineWidth);
		}
		{ // YZ
			const Color4 &cColor = ((m_nSelected & YAxis) && (m_nSelected & ZAxis)) ? Color4::Yellow : Color4::Blue;
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 2.5f, 2.5f), mObjectSpaceToClipSpace, fLineWidth);
			cDrawHelpers.DrawLine(cColor, Vector3(0.0f, 0.0f, 8.0f), Vector3(0.0f, 4.0f, 4.0f), mObjectSpaceToClipSpace, fLineWidth);
		}
	}
	{ // Draw selected axis combination
		// XY
		if ((m_nSelected & XAxis) && (m_nSelected & YAxis) && !(m_nSelected & ZAxis)) {
			cDrawHelpers.DrawQuad(Color4::Yellow, Vector3(0.0f, 8.0f, 0.0f), Vector3(8.0f, 0.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3(5.0f, 0.0f, 0.0f), mObjectSpaceToClipSpace);

		// XZ
		} else if ((m_nSelected & XAxis) && !(m_nSelected & YAxis) && (m_nSelected & ZAxis)) {
			cDrawHelpers.DrawQuad(Color4::Yellow, Vector3(0.0f, 0.0f, 5.0f), Vector3(5.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 8.0f), Vector3(8.0f, 0.0f, 0.0f), mObjectSpaceToClipSpace);

		// YZ
		} else if (!(m_nSelected & XAxis) && (m_nSelected & YAxis) && (m_nSelected & ZAxis)) {
			cDrawHelpers.DrawQuad(Color4::Yellow, Vector3(0.0f, 0.0f, 8.0f), Vector3(0.0f, 8.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 5.0f, 0.0f), mObjectSpaceToClipSpace);

		// XYZ
		} else if ((m_nSelected & XAxis) && (m_nSelected & YAxis) && (m_nSelected & ZAxis)) {
			cDrawHelpers.DrawTriangle(Color4::Yellow, Vector3(5.0f, 0.0f, 0.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), mObjectSpaceToClipSpace);
			cDrawHelpers.DrawTriangle(Color4::Yellow, Vector3::Zero,             Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), mObjectSpaceToClipSpace);
			cDrawHelpers.DrawTriangle(Color4::Yellow, Vector3(5.0f, 0.0f, 0.0f), Vector3::Zero,             Vector3(0.0f, 0.0f, 5.0f), mObjectSpaceToClipSpace);

			// Draw axis in selected color
			// X axis
			cDrawHelpers.DrawLine(Color4::Yellow, Vector3(5.0f, 0.0f, 0.0f), Vector3(10.0f,  0.0f,  0.0f), mObjectSpaceToClipSpace, fLineWidth*2);
			// Y axis
			cDrawHelpers.DrawLine(Color4::Yellow, Vector3(0.0f, 5.0f, 0.0f), Vector3( 0.0f, 10.0f,  0.0f), mObjectSpaceToClipSpace, fLineWidth*2);
			// Z axis
			cDrawHelpers.DrawLine(Color4::Yellow, Vector3(0.0f, 0.0f, 5.0f), Vector3( 0.0f,  0.0f, 10.0f), mObjectSpaceToClipSpace, fLineWidth*2);
		}
	}

	// Draw texts
	Font *pFont = cRenderer.GetFontManager().GetDefaultFontTexture();
	if (pFont) {
		// X axis
		cDrawHelpers.DrawText(*pFont, 'X', cPrimaryXAxisColor, Vector3(11.0f, 0.0f, 0.0f), mObjectSpaceToClipSpace, Font::CenterText);

		// Y axis
		cDrawHelpers.DrawText(*pFont, 'Y', cPrimaryYAxisColor, Vector3(0.0f, 11.0f, 0.0f), mObjectSpaceToClipSpace, Font::CenterText);

		// Z axis
		cDrawHelpers.DrawText(*pFont, 'Z', cPrimaryZAxisColor, Vector3(0.0f, 0.0f, 11.0f), mObjectSpaceToClipSpace, Font::CenterText);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
