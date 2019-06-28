
// *****************************************************************************
//
//                              Class EventSender
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENTSENDER_HPP
#define EVENTSENDER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Array.hpp"
#include "EventReceiver.hpp"

#include <functional>


// ============================= Class EventSender =============================

namespace GS {

class GSROOT_DLL_EXPORT EventSenderBase {
protected:
	friend class EventReceiver;		// to access ReceiverDeleted

	virtual ~EventSenderBase ();

	virtual void	ReceiverDeleted (EventReceiver& receiver) = 0;
};


template <class CallbackFunctionType, class SendCaller = void>
class EventSender: public EventSenderBase {
public:
	typedef std::function<CallbackFunctionType> CallbackFunction;

protected:
	struct Receiver {
		EventReceiver*	 receiver;
		CallbackFunction callbackFunction;

		Receiver (): receiver (nullptr) {}
		Receiver (EventReceiver* receiver, const CallbackFunction& callbackFunction): receiver (receiver), callbackFunction (callbackFunction) {}
	};

	Array<Receiver>	receivers;			// receivers of the sender
	bool			sending;			// true during sending
	bool			reverseSendOrder;	// true if receivers are notified in the reverse order during sending, it is alternated after each send

	virtual void	ReceiverDeleted (EventReceiver& receiver) override;

	friend SendCaller;

	void	Send ();

	template <class Type1>
	void	Send (const Type1& parameter1);

	template <class Type1, class Type2>
	void	Send (const Type1& parameter1, const Type2& parameter2);

	template <class Type1, class Type2, class Type3>
	void	Send (const Type1& parameter1, const Type2& parameter2, const Type3& parameter3);

	void	Send (const std::function<void (const CallbackFunction&)>& invoker);

public:
	EventSender ();
	EventSender (const EventSender& source);
  	EventSender&	operator= (const EventSender& source);
   ~EventSender ();

	void	Attach (EventReceiver& receiver, const CallbackFunction& callbackFunction);
	void	Detach (EventReceiver& receiver);
};


class PublicSendCaller {};

template <class CallbackFunctionType>
class EventSender<CallbackFunctionType, void>: public EventSender<CallbackFunctionType, PublicSendCaller> {
public:
	void	Send ()																			 { EventSender<CallbackFunctionType, PublicSendCaller>::Send (); }

	template <class Type1>
	void	Send (const Type1& parameter1)													 { EventSender<CallbackFunctionType, PublicSendCaller>::Send (parameter1); }

	template <class Type1, class Type2>
	void	Send (const Type1& parameter1, const Type2& parameter2)							 { EventSender<CallbackFunctionType, PublicSendCaller>::Send (parameter1, parameter2); }

	template <class Type1, class Type2, class Type3>
	void	Send (const Type1& parameter1, const Type2& parameter2, const Type3& parameter3) { EventSender<CallbackFunctionType, PublicSendCaller>::Send (parameter1, parameter2, parameter3); }

	void	Send (const std::function<void (const typename EventSender::CallbackFunction&)>& invoker) { EventSender<CallbackFunctionType, PublicSendCaller>::Send (invoker); }
};

}	// namespace GS



template <class CallbackFunctionType, class SendCaller>
GS::EventSender<CallbackFunctionType, SendCaller>::EventSender ():
	sending (false),
	reverseSendOrder (false)
{
}


template <class CallbackFunctionType, class SendCaller>
GS::EventSender<CallbackFunctionType, SendCaller>::EventSender (const EventSender& /*source*/):
	sending (false),
	reverseSendOrder (false)
{
	// receivers are not copied
}


template <class CallbackFunctionType, class SendCaller>
GS::EventSender<CallbackFunctionType, SendCaller>&	GS::EventSender<CallbackFunctionType, SendCaller>::operator= (const EventSender& /*source*/)
{
	// receivers are not copied

	return *this;
}


template <class CallbackFunctionType, class SendCaller>
GS::EventSender<CallbackFunctionType, SendCaller>::~EventSender ()
{
	for (UInt32 i = 0; i < receivers.GetSize (); i++)
		receivers[i].receiver->eventSenders.DeleteFirst (this);
}


template <class CallbackFunctionType, class SendCaller>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Attach (EventReceiver& receiver, const CallbackFunction& callbackFunction)
{
	DBASSERT (&receiver != nullptr);
	DBASSERT (&callbackFunction != nullptr);
	//lint !e914 [Implicit adjustment of function return value] LINT felrefutas
	DBASSERT (!receivers.Contains ([&] (const Receiver& r) { return r.receiver == &receiver; }));
	DBASSERT (!sending);	// it needs further development to enable Attach during event sending (new receivers should be added only after event sending has been finished)

	receivers.Push (Receiver (&receiver, callbackFunction));
	receiver.eventSenders.Push (this);
}


template <class CallbackFunctionType, class SendCaller>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Detach (EventReceiver& receiver)
{
	DBASSERT (&receiver != nullptr);
	DBASSERT (!sending);	// it needs further development to enable Detach during event sending (existing receivers should be deleted only after event sending has been finished)

	//lint !e914 [Implicit adjustment of function return value] LINT felrefutas
	UInt32 receiverIndex = receivers.FindFirst ([&] (const Receiver& r) { return r.receiver == &receiver; });

	if (receiverIndex != MaxUIndex) {
		receivers.Delete (receiverIndex);
		receiver.eventSenders.DeleteFirst (this);
	}
}


template <class CallbackFunctionType, class SendCaller>
void	GS::EventSender<CallbackFunctionType, SendCaller>::ReceiverDeleted (EventReceiver& receiver)
{
	DBASSERT (!sending);	// it is not allowed to delete receiver during event sending

	UInt32 receiverIndex = receivers.FindFirst ([&] (const Receiver& r) { return r.receiver == &receiver; });
	receivers.Delete (receiverIndex);
}


template <class CallbackFunctionType, class SendCaller>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Send ()
{
	std::function<void (const CallbackFunction&)> invoker = [&] (const CallbackFunction& function) { function (); };
	Send (invoker);
}


template <class CallbackFunctionType, class SendCaller>
template <class Type1>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Send (const Type1& parameter1)
{
	std::function<void (const CallbackFunction&)> invoker = [&] (const CallbackFunction& function) { function (parameter1); };
	Send (invoker);
}


template <class CallbackFunctionType, class SendCaller>
template <class Type1, class Type2>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Send (const Type1& parameter1, const Type2& parameter2)
{
	std::function<void (const CallbackFunction&)> invoker = [&] (const CallbackFunction& function) { function (parameter1, parameter2); };
	Send (invoker);
}


template <class CallbackFunctionType, class SendCaller>
template <class Type1, class Type2, class Type3>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Send (const Type1& parameter1, const Type2& parameter2, const Type3& parameter3)
{
	std::function<void (const CallbackFunction&)> invoker = [&] (const CallbackFunction& function) { function (parameter1, parameter2, parameter3); };
	Send (invoker);
}


template <class CallbackFunctionType, class SendCaller>
void	GS::EventSender<CallbackFunctionType, SendCaller>::Send (const std::function<void (const CallbackFunction&)>& invoker)
{
	DBASSERT (&invoker != nullptr);

	sending = true;

	if (reverseSendOrder) {
		for (UInt32 i = receivers.GetSize (); i > 0; i--)
			invoker (receivers[i - 1].callbackFunction);
	} else {
		for (UInt32 i = 0; i < receivers.GetSize (); i++)
			invoker (receivers[i].callbackFunction);
	}

	reverseSendOrder = !reverseSendOrder;

	sending = false;
}


#endif
