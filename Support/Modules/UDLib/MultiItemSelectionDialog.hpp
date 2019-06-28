#ifndef MULTIITEMSELECTIONDIALOG_HPP
#define MULTIITEMSELECTIONDIALOG_HPP


#include "UDDefinitions.hpp"
#include "ItemSelectionDialog.hpp"


namespace UD {
	class BaseItemSelectionDataObserver;
}


namespace UD {


class UD_DLL_EXPORT MultiItemSelectionDialog :	public ItemSelectionDialogBase
{
private:

	enum {
		DialogResourceId = 2101
	};

	DG::MultiSelTreeView	itemsTreeView;

public:

	MultiItemSelectionDialog (const DG::Item&			parentItem,
							  BaseItemSelectionData&	itemSelectionDialogData);
	MultiItemSelectionDialog (const DG::NativeRect&		parentRect,
							  BaseItemSelectionData&	itemSelectionDialogData);

	~MultiItemSelectionDialog ();
};


} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP
