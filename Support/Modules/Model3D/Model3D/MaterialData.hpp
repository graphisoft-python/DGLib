// *********************************************************************************************************************
// Description:		Attribute Data
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	AACS
//
// SG compatible
// *********************************************************************************************************************

#if !defined (MATERIALDATA_HPP)
#define MATERIALDATA_HPP

#pragma once

#include	"Model3D/UMAT.hpp"
#include	"TextureData.hpp"

namespace Modeler {
	class MaterialData
	{
	public: 
		MaterialData ()
		{
		}

		UMAT					uMat; 
		Modeler::TextureData	textureSetupData; 
	};
} //Modeler

#endif //MATERIALDATA_HPP

