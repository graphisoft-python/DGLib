#ifndef IMODELVISUALOVERRIDETYPES_HPP
#define IMODELVISUALOVERRIDETYPES_HPP

#pragma once

//#include "IVisualOverrideTemplate.hpp"
#include "CountedPtr.hpp"

namespace VisualOverride
{
	template <class DrawSpecificsT>
	class IVisualOverrideTemplate;
	class IModelDrawSpecifics;
	typedef IVisualOverrideTemplate<IModelDrawSpecifics> IModelVisualOverride;  
}

typedef GS::CountedPtr<const VisualOverride::IModelVisualOverride> IModelVisualOverrideConstPtr;

#endif //IMODELVISUALOVERRIDETYPES_HPP
