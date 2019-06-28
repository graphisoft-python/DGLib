
// *****************************************************************************
//
//                              Class EventReceiver
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENTRECEIVER_HPP
#define EVENTRECEIVER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Array.hpp"

namespace GS { class EventSenderBase; }
namespace GS { template <class CallbackFunctionType, class SendCaller> class EventSender; }


// ============================ Class EventReceiver ============================

namespace GS {

class GSROOT_DLL_EXPORT EventReceiver {
private:
	GS::Array<EventSenderBase*> eventSenders;	// senders of the receiver

	template <class CallbackFunctionType, class SendCaller>
	friend class EventSender;					// to allow access to eventSenders

public:
	inline EventReceiver ();
	inline EventReceiver (const EventReceiver&);
	inline EventReceiver& operator = (const EventReceiver&);
   ~EventReceiver ();
};

}	// namespace GS


inline GS::EventReceiver::EventReceiver ()
{
}


inline GS::EventReceiver::EventReceiver (const EventReceiver&)
{
	// eventSenders are not copied
}


inline GS::EventReceiver&	 GS::EventReceiver::operator= (const EventReceiver&)
{
	// eventSenders are not copied

	return *this;
}


#endif
