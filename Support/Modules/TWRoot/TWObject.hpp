
// *****************************************************************************
//
//                                 Class Object
//
// Module:		   TWClientBase
// Namespace:	   TW
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined TWOBJECT_HPP
#define TWOBJECT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "TWRootExport.hpp"

#include "ODBDynamicObject.hpp"



// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace TW {
	class Object;
	typedef ODB::Ref<Object> ObjectRef;
	typedef ODB::ConstRef<Object> ObjectConstRef;
}

// =============================== Class Object ================================

namespace TW {

class TWROOT_DLL_EXPORT Object : public ODB::DynamicObject {
	DECLARE_ABSTRACT_DYNAMIC_CLASS

protected:
			Object ();
			Object (const GS::ClassInfo* finalClassInfo);
			Object (const ODB::DynamicClass* finalDynamicClass);

public:
	virtual ~Object ();

			Object (const Object& source);

protected:
			Object& operator= (const Object& source);

public:
	virtual GSErrCode	Write 					(GS::OChannel& oc) const override;
	virtual GSErrCode	Read 					(GS::IChannel& ic) override;

private:
	//serialization
	GSErrCode			WriteVersion1			(GS::OChannel& oc) const;
	GSErrCode			ReadVersion1			(GS::IChannel& ic);

public:
	// ... Transaction management methods ..............................................................................

	virtual GSErrCode	StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode	RestoreIsolatedState 	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual void		Isolate					(void) override;
	virtual GSErrCode	WriteIsolatedState   	(GS::OChannel& oc) const override;
	virtual GSErrCode	ReadIsolatedState 		(GS::IChannel& ic) override;

	virtual	GSErrCode	WriteIsolatedStateXML	(GS::XMLOChannel& oc) const override;
	virtual	GSErrCode	ReadIsolatedStateXML	(GS::XMLIChannel& ic) override;


	// Isolated state management

	virtual	GSErrCode	WriteTWIsolatedState	(GS::OChannel& oc) const = 0;
	virtual	GSErrCode	ReadTWIsolatedState		(GS::IChannel& ic) = 0;

	// ... Transaction management class TWROOT_DLL_EXPORT ................................................................................

protected:
	class TWROOT_DLL_EXPORT IsolatedState : public ODB::DynamicObject::IsolatedState {
	private:
		friend class TW::Object;

	public:
		virtual ~IsolatedState ();
	};
};


class TWROOT_DLL_EXPORT IsolatedStateIO: public ODB::Object::IsolatedStateIO {
public:
	virtual	GSErrCode	WriteIsolatedState (const ODB::ConstRef<ODB::Object>& object, GS::OChannel& oc) const override;
	virtual	GSErrCode	ReadIsolatedState  (const ODB::Ref<ODB::Object>& object, GS::IChannel& ic) override;
};

TWROOT_DLL_EXPORT extern IsolatedStateIO	isolatedStateIO;	// Teamwork isolated state IO

}	// namespace TW
// _______________________________ Class Object ________________________________


#endif
