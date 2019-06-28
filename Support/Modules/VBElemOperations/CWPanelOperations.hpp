#ifndef CW_PANEL_OPERATIONS_HPP
#define CW_PANEL_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBElements
#include "CWPanel.hpp"

class VBElemSurfaceDescriptor;

class VB_ELEM_OPERATIONS_DLL_EXPORT CWPanelOperations
{
public:
	enum MaterialSelector {
		OuterMaterial,
		InnerMaterial,
		SideMaterial
	};

	static VBElemSurfaceDescriptor GetMaterial (	VBElem::CWPanelConstRef panel,
								const ADB::AttributeSetConstRef& attributeSet,
								MaterialSelector selector,
								bool pbcConversions);

	static void GetStandaloneVisibleMaterials (VBElem::CWPanelConstRef panel, bool pbcConversion, GS::HashSet<short>& materials);
	static void  GetDirections (VBElem::CWPanelConstRef panel,
								double northDirection,
								double* vertDirection,
								double*	horDirection);
};


#endif // CW_PANEL_OPERATIONS_HPP
