#ifndef SINGLEITEMSELECTIONDIALOG_HPP
#define SINGLEITEMSELECTIONDIALOG_HPP

#include "UDDefinitions.hpp"
#include "ItemSelectionDialog.hpp"


namespace UD {
	class BaseItemSelectionDataObserver;
}


namespace UD {


class UD_DLL_EXPORT SingleItemSelectionDialogBase : public ItemSelectionDialogBase
{
private:
	enum {
		DialogResourceId = 2110
	};

	virtual bool KeyPressed (const DG::Key::Code& code, DG::Item** item) override;

public:
	SingleItemSelectionDialogBase (const DG::Item&			parentItem,
								   BaseItemSelectionData&	itemSelectionDialogData,
								   DG::TreeView&			itemsTreeView);

	~SingleItemSelectionDialogBase ();
};


class UD_DLL_EXPORT SingleItemSelectionDialog : public SingleItemSelectionDialogBase
{
private:
	DG::SingleSelTreeView	itemsTreeView;

public:
	SingleItemSelectionDialog (const DG::Item&			parentItem,
							  BaseItemSelectionData&	itemSelectionDialogData);

	virtual ~SingleItemSelectionDialog ();
};


class UD_DLL_EXPORT SingleItemSelectionDialogPopup : public SingleItemSelectionDialog
{
private:
	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;

public:
	SingleItemSelectionDialogPopup (const DG::Item&			parent,
									BaseItemSelectionData&	itemSelectionDialogData);

	virtual void	TreeViewItemDoubleClicked (const DG::TreeViewDoubleClickEvent& ev, bool* processed) override;
	virtual void	ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;
};

} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP
