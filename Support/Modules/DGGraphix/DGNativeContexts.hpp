// *********************************************************************************************************************
// File:			DGNativeContexts.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
// *********************************************************************************************************************

#ifndef DGNATIVECONTEXTS_HPP
#define DGNATIVECONTEXTS_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGGraphixDefinitions.hpp"					// DGGRAPHIX_DLL_EXPORT
#include "NativeContext.hpp"

namespace DG {
	class UserItemUpdateEvent;
	class FileDialogPreviewUpdateEvent;
	class ListBoxItemUpdateEvent;
	class ListBoxTabItemUpdateEvent;
	class ListViewUpdateEvent;
}

struct IDGItemUpdateData;


namespace NewDisplay {

class DGGRAPHIX_DLL_EXPORT UserItemUpdateNativeContext: public NativeContext
{
public:
	UserItemUpdateNativeContext (const DG::UserItemUpdateEvent&);
	UserItemUpdateNativeContext (const DG::FileDialogPreviewUpdateEvent&);
	explicit UserItemUpdateNativeContext (const IDGItemUpdateData* updateItemData);

	~UserItemUpdateNativeContext ();
};

class DGGRAPHIX_DLL_EXPORT ListBoxUpdateEventContext: public NativeContext
{
public:
	ListBoxUpdateEventContext (const DG::ListBoxItemUpdateEvent&);
	ListBoxUpdateEventContext (const DG::ListBoxTabItemUpdateEvent&);
	explicit ListBoxUpdateEventContext (const IDGItemUpdateData* updateItemData);

	~ListBoxUpdateEventContext ();
};

class DGGRAPHIX_DLL_EXPORT ListViewUpdateEventContext: public NativeContext
{
public:
	ListViewUpdateEventContext (const DG::ListViewUpdateEvent&);
	explicit ListViewUpdateEventContext (const IDGItemUpdateData* updateItemData);

	~ListViewUpdateEventContext ();
};


}

#endif
