#ifndef CW_FRAME_OPERATIONS_HPP
#define CW_FRAME_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBElements
#include "CWFrame.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT CWFrameOperations
{
public:
	enum FramePosition {
		VerticalFrame = 0,
		HorizontalFrame = 1,
		OnContourFrame = 2,
		DiagonalFrame = 3
	};

	static void GetStandaloneVisibleMaterials (VBElem::CWFrameConstRef frame, bool pbcConversion, GS::HashSet<short>& materials);

	template<class CWFramePtrType>
	static GS::Optional<double> GetWidth (CWFramePtrType framePtr)
	{
		if (framePtr->GetObjectType () == VBElem::CWFrame::Invisible)
			return GS::NoValue;
		return 2 * framePtr->GetFrameCornerOffset ();
	}

	template<class CWFramePtrType>
	static GS::Optional<double> GetHeight (CWFramePtrType framePtr)
	{
		bool buttGlazed = false;
		switch (framePtr->GetObjectType ()) {
			case VBElem::CWFrame::Invisible:
				return GS::NoValue;
			case VBElem::CWFrame::GDL:
				buttGlazed = (framePtr->GetBeamProfileID () > 0 && framePtr->GetCapProfileID () <= 0);
				break;
			default:
				DBBREAK ();
				return GS::NoValue;
		}
		if (buttGlazed)
			return framePtr->GetB2 () - framePtr->GetW () / 2;
		else
			return framePtr->GetB1 () + framePtr->GetB2 ();
	}
};

#endif // CW_FRAME_OPERATIONS_HPP
