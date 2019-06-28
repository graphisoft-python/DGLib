#ifndef GS_COMMONUI_DGLISTBOXUTILITIES_HPP
#define GS_COMMONUI_DGLISTBOXUTILITIES_HPP


#include "UDDefinitions.hpp"
#include "HashTable.hpp"

namespace DG {
	class ListBox;
}

namespace Gfx {
	class Color;
}


namespace UD {
	UD_DLL_EXPORT short GetListBoxRequiredHeight (const DG::ListBox& listBox);
	UD_DLL_EXPORT Gfx::Color GetListBoxDefaultHeaderBgColor (const DG::ListBox&	listBox, short itemIndex);

	UD_DLL_EXPORT short	GetListBoxDesiredOnTabItemWidth (const DG::ListBox& listBox, short tabItemIndex);

	class UD_DLL_EXPORT ListBoxColumnResizer : public DG::ListBoxObserver {
	public:
		explicit ListBoxColumnResizer (DG::ListBox& listBox);
		virtual ~ListBoxColumnResizer ();

		void SetColumnFixWidth (short column, short fixWidth);
		void SetColumnResizableWeight (short column, short weight);

		void Resize ();

	private:
		DG::ListBox& listBox;
		GS::HashTable<short, short> fixColumnWidths;
		GS::HashTable<short, short> resizableColumnWeights;

		virtual short	ListBoxHeaderItemResizeExited (const DG::ListBoxHeaderItemResizeEvent& ev) override;
		void			UpdateResizableColumnWeights ();
		void			FillWithDefaultValues ();
	};
}


#endif