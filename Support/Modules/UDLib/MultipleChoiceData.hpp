#ifndef	GS_COMMONUI_MULTIPLECHOICEDATA_HPP
#define	GS_COMMONUI_MULTIPLECHOICEDATA_HPP


#include "UDDefinitions.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"


namespace UD {
	class MultipleChoiceDataObserver;
}


namespace UD {


class UD_DLL_EXPORT MultipleChoiceItem {
private:
	bool			isSelected;
	GS::UniString	text;

public:
	MultipleChoiceItem ();

	bool					IsSelected (void) const;
	void					SetSelected (bool inIsSelected);

	const GS::UniString&	GetText	(void) const;
	void					SetText (const GS::UniString& inText);
};


class UD_DLL_EXPORT MultipleChoiceData : public GS::EventSource
{
private:
	GS::Array<MultipleChoiceItem> items;

public:
	virtual ~MultipleChoiceData ();

	void	Attach (MultipleChoiceDataObserver& observer);
	void	Detach (MultipleChoiceDataObserver& observer);

	const GS::Array<MultipleChoiceItem>& GetItems (void) const;

	void	Clear (void);
	void	AddItem (const MultipleChoiceItem& item);
	void	SetItemSelected (UIndex itemIndex, bool inIsSelected);
};


class UD_DLL_EXPORT MultipleChoiceDataObserver : public GS::EventObserver
{
protected:
	friend class MultipleChoiceData;

	virtual void SelectionChanged (const MultipleChoiceData& source);

public:
	virtual ~MultipleChoiceDataObserver ();
};


class UD_DLL_EXPORT MultipleChoiceDataChanges : public MultipleChoiceDataObserver
{
private:
	bool	isSelectionChanged;

	virtual void	SelectionChanged (const MultipleChoiceData& source) override;

public:
	MultipleChoiceDataChanges (MultipleChoiceData& multipleChoicePopUpDialog);

	bool			IsSelectionChanged (void) const;
};

} // namespace UD


#endif