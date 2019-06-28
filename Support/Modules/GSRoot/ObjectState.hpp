// *********************************************************************************************************************
// Description:		class ObjectState
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, BIM, KKr
//
// *********************************************************************************************************************

#ifndef OBJECTSTATE_HPP
#define OBJECTSTATE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "GSNew.hpp"
#include "String.hpp"
#include "UniString.hpp"
#include "HashTable.hpp"
#include "CArray.hpp"
#include "Array.hpp"
#include "Pair.hpp"
#include "TypeTraits.hpp"
#include "EnumerationTraits.hpp"
#include "RangeElementType.hpp"
#include "Owner.hpp"

// =============================================================================


namespace GS {

class ErrorStatus;

GSROOT_DLL_EXPORT extern const CustomClassProperty	ObjectStateSchema;

template <class Type>
struct ObjectStateTypeConversion {
	static constexpr bool isConvertible = false;
};


class GSROOT_DLL_EXPORT ObjectState {
public:
	class Processor;
	class Content;
	class ContentProcessor;
	struct Result;
	class Field;
	class Schema;

	friend ContentProcessor;

	enum Type {
		Bool,
		UInt,
		Int,
		Real,
		String,
		List,
		Object
	};

private:
	struct GSROOT_DLL_EXPORT Value;
	struct GSROOT_DLL_EXPORT BoolValue;
	struct GSROOT_DLL_EXPORT IntValue;
	struct GSROOT_DLL_EXPORT UIntValue;
	struct GSROOT_DLL_EXPORT RealValue;
	struct GSROOT_DLL_EXPORT StringValue;
	struct GSROOT_DLL_EXPORT ListValue;
	struct GSROOT_DLL_EXPORT ObjectValue;

	HashTable<GS::String, Value*> fields;

	template <class T>
	using Convertible = typename Enable<ObjectStateTypeConversion<T>::isConvertible>::TrueCondition;

	template <class T>
	using NotConvertible = typename Enable<ObjectStateTypeConversion<T>::isConvertible>::FalseCondition;

	void	PassToProcessor (const GS::String& fieldName, const Value* value, Processor& processor) const;
	
	template <class T, class... Fields>
	void	AddFields (const GS::String& fieldName, const T& value, Fields&&... fields);

	void	AddFields ();

	template <class T>
	GSErrCode	AddObject (const GS::String& fieldName, const T& value, Convertible<T> = true);

	template <class T>
	GSErrCode	AddObject (const GS::String& fieldName, const T& value, NotConvertible<T> = true);

	GSErrCode	AddValue (Array<Value*>& list, bool value);
	GSErrCode	AddValue (Array<Value*>& list, UInt8 value);
	GSErrCode	AddValue (Array<Value*>& list, UInt16 value);
	GSErrCode	AddValue (Array<Value*>& list, UInt32 value);
	GSErrCode	AddValue (Array<Value*>& list, UInt64 value);
	GSErrCode	AddValue (Array<Value*>& list, Int8 value);
	GSErrCode	AddValue (Array<Value*>& list, Int16 value);
	GSErrCode	AddValue (Array<Value*>& list, Int32 value);
	GSErrCode	AddValue (Array<Value*>& list, Int64 value);
	GSErrCode	AddValue (Array<Value*>& list, float value);
	GSErrCode	AddValue (Array<Value*>& list, double value);
	GSErrCode	AddValue (Array<Value*>& list, const UniString& value);
	GSErrCode	AddValue (Array<Value*>& list, const GS::String& value);
	GSErrCode	AddValue (Array<Value*>& list, const ObjectState& value);
	GSErrCode	AddValue (Array<Value*>& list, ObjectState* value);

	template <class T>
	GSErrCode	AddValue (Array<Value*>& list, const T& value, NotEnumerable<T> = true);

	template <class T>
	GSErrCode	AddValue (Array<Value*>& list, const T& value, Enumerable<T> = true);

	template <class T>
	Result		GetObject (const GS::String& fieldName, T& value, Convertible<T> = true) const;

	template <class T>
	Result		GetObject (const GS::String& fieldName, T& value, NotConvertible<T> = true) const;

	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, bool& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, UInt8& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, UInt16& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, UInt32& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, UInt64& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, Int8& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, Int16& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, Int32& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, Int64& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, double& outValue) const;
	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, UniString& outValue) const;

	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, ObjectState& outValue) const;

	GSErrCode	GetValue (const Array<Value*>& list, UIndex idx, GS::String& outValue) const;

	template <class T>
	GSErrCode		GetValue (const Array<Value*>& list, UIndex idx, T& outValue, NotEnumerable<T> = true) const;

	template <class T>
	GSErrCode		GetValue (const Array<Value*>& list, UIndex idx, T& outValue, Enumerable<T> = true) const;

	ObjectState*		  GetObjectState	(const ObjectValue* objValue) const;
	Value*				  CreateObjectValue (ObjectState* os) const;
	Value*				  CreateListValue	(const Array<Value*>& array) const;
	const Array<Value*>*  GetValueArray		(const ListValue* listValue) const;
	Array<Value*>&		  GetValueArray (ListValue* listValue);

	inline bool		IsIntInRange  (Value* value, Int64 min = MinInt64, Int64 max = MaxInt64) const;
	inline bool		IsUIntInRange (Value* value, UInt64 min = 0, UInt64 max = MaxUInt64) const;

public:
	inline ~ObjectState ();
	inline ObjectState ();

	template <class T, class... Fields>
	ObjectState (const GS::String& fieldName, const T& value, Fields&&... fields);

	ObjectState (const ObjectState& source);
	ObjectState (ObjectState&& source);
	ObjectState& operator= (const ObjectState& source);
	ObjectState& operator= (ObjectState&& source);

	GSErrCode	Add (const GS::String& fieldName, bool value);
	GSErrCode	Add (const GS::String& fieldName, UInt64 value);
	GSErrCode	Add (const GS::String& fieldName, UInt8 value);
	GSErrCode	Add (const GS::String& fieldName, UInt16 value);
	GSErrCode	Add (const GS::String& fieldName, UInt32 value);
	GSErrCode	Add (const GS::String& fieldName, Int64 value);
	GSErrCode	Add (const GS::String& fieldName, Int8 value);
	GSErrCode	Add (const GS::String& fieldName, Int16 value);
	GSErrCode	Add (const GS::String& fieldName, Int32 value);
	GSErrCode	Add (const GS::String& fieldName, double value);
	GSErrCode	Add (const GS::String& fieldName, float value);
	GSErrCode	Add (const GS::String& fieldName, const UniString& value);
	GSErrCode	Add (const GS::String& fieldName, const GS::String& value);
	GSErrCode	Add (const GS::String& fieldName, const char* value);
	GSErrCode	Add (const GS::String& fieldName, const ObjectState& value);
	GSErrCode	Add (const GS::String& fieldName, Owner<ObjectState> value);

	template <class T>
	GSErrCode	Add (const GS::String& fieldName, const T& value, NotEnumerable<T> = true, NotEnumType<T> = true);

	template <class T>
	GSErrCode	Add (const GS::String& fieldName, const T& value, Enumerable<T> = true, NotEnumType<T> = true);

	template <class T>
	GSErrCode	Add (const GS::String& fieldName, const T& value, EnumType<T> = true);

	template <class T>
	GSErrCode	Add (const Field& field, const T& value);

	ObjectState&	AddObject (const GS::String& fieldName);

	template <class T>
	auto		AddList (const GS::String& fieldName);

	GSErrCode	Build (const Content& content);

	bool		Contains (const GS::String& fieldName) const;
	bool		Contains (const Field& field) const;

	bool		IsType	 (const GS::String& fieldName, Type type) const;
	
	bool		IsBool   (const GS::String& fieldName) const;
	bool		IsUInt   (const GS::String& fieldName) const;
	bool		IsInt    (const GS::String& fieldName) const;
	bool		IsReal   (const GS::String& fieldName) const;
	bool		IsString (const GS::String& fieldName) const;
	bool		IsList   (const GS::String& fieldName) const;
	bool		IsObject (const GS::String& fieldName) const;

	bool		FitsInUInt8  (const GS::String& fieldName) const;
	bool		FitsInUInt16 (const GS::String& fieldName) const;
	bool		FitsInUInt32 (const GS::String& fieldName) const;
	bool		FitsInUInt64 (const GS::String& fieldName) const;
	bool		FitsInInt8   (const GS::String& fieldName) const;
	bool		FitsInInt16  (const GS::String& fieldName) const;
	bool		FitsInInt32  (const GS::String& fieldName) const;
	bool		FitsInInt64  (const GS::String& fieldName) const;
	bool		FitsInDouble (const GS::String& fieldName) const;
	bool		FitsInFloat  (const GS::String& fieldName) const;

	bool		Get (const GS::String& fieldName, bool& value) const;
	bool		Get (const GS::String& fieldName, Int8& value) const;
	bool		Get (const GS::String& fieldName, Int16& value) const;
	bool		Get (const GS::String& fieldName, Int32& value) const;
	bool		Get (const GS::String& fieldName, Int64& value) const;
	bool		Get (const GS::String& fieldName, UInt8& value) const;
	bool		Get (const GS::String& fieldName, UInt16& value) const;
	bool		Get (const GS::String& fieldName, UInt32& value) const;
	bool		Get (const GS::String& fieldName, UInt64& value) const;
	bool		Get (const GS::String& fieldName, double& value) const;
	bool		Get (const GS::String& fieldName, float& value) const;
	bool		Get (const GS::String& fieldName, UniString& value) const;
	bool		Get (const GS::String& fieldName, GS::String& value) const;
	bool		Get (const GS::String& fieldName, ObjectState& value) const;

	const ObjectState*	Get (const GS::String& fieldName) const;

	template <class T>
	Result		Get (const GS::String& fieldName, T& value, NotEnumerable<T> = true, NotEnumType<T> = true) const;

	template <class T>
	Result		Get (const GS::String& fieldName, T& value, Enumerable<T> = true, NotEnumType<T> = true) const;

	template <class T>
	Result		Get (const GS::String& fieldName, T& value, EnumType<T> = true) const;

	template <class T>
	bool		Get (const Field& field, T& value) const;

	bool		Get (const GS::String& fieldName, bool& value, bool defaultValue) const;
	bool		Get (const GS::String& fieldName, Int8& value, Int8 defaultValue) const;
	bool		Get (const GS::String& fieldName, Int16& value, Int16 defaultValue) const;
	bool		Get (const GS::String& fieldName, Int32& value, Int32 defaultValue) const;
	bool		Get (const GS::String& fieldName, Int64& value, Int64 defaultValue) const;
	bool		Get (const GS::String& fieldName, UInt8& value, UInt8 defaultValue) const;
	bool		Get (const GS::String& fieldName, UInt16& value, UInt16 defaultValue) const;
	bool		Get (const GS::String& fieldName, UInt32& value, UInt32 defaultValue) const;
	bool		Get (const GS::String& fieldName, UInt64& value, UInt64 defaultValue) const;
	bool		Get (const GS::String& fieldName, double& value, double defaultValue) const;
	bool		Get (const GS::String& fieldName, float& value, float defaultValue) const;
	bool		Get (const GS::String& fieldName, UniString& value, const UniString& defaultValue) const;
	bool		Get (const GS::String& fieldName, GS::String& value, const GS::String& defaultValue) const;

	template <class T>
	void		Get (const GS::String& fieldName, T& value, const T& defaultValue) const;

	template <class T>
	void		Get (const Field& field, T& value, const T& defaultValue) const;

	Type		GetType (const GS::String& fieldName) const;

	void		Clear	();
	bool		IsEmpty () const;
	UInt32		GetFieldCount () const;

	void		EnumerateFields (const std::function<void (const GS::String&)>& processor) const;

	void		Enumerate (Processor& processor) const;
	void		Enumerate (const GS::String& fieldName, Processor& processor) const;

	static	GS::String	ToString (Type type);

		// types

	enum Optionality {
		Required,
		Optional
	};

	class GSROOT_DLL_EXPORT Processor {
	public:
		virtual ~Processor ();

		virtual void	BoolFound     (const GS::String& fieldName, bool value);
		virtual void	IntFound      (const GS::String& fieldName, Int64 value);
		virtual void	UIntFound     (const GS::String& fieldName, UInt64 value);
		virtual void	RealFound     (const GS::String& fieldName, double value);
		virtual void	StringFound   (const GS::String& fieldName, const UniString& value);
		virtual bool	ObjectFound   (const GS::String& fieldName, const ObjectState& value);
		virtual void	ObjectEntered (const GS::String& fieldName);
		virtual void	ObjectExited  (const GS::String& fieldName);
		virtual bool	ListFound	  (const GS::String& fieldName);
		virtual void	ListEntered   (const GS::String& fieldName);
		virtual void	ListExited    (const GS::String& fieldName);
	};


	class GSROOT_DLL_EXPORT Content {
	public:
		virtual ~Content ();
		virtual void	Enumerate (ContentProcessor& processor) const = 0;
	};
	

	class GSROOT_DLL_EXPORT ContentProcessor final {
	private:
		GS::Array<ObjectState*>		  nestedObjects;
		GS::Array<GS::Array<Value*>>  nestedLists;
		GS::Array<GS::String>         fieldNames;
		GS::Array<Type> listOrObject;

		UIndex call = 0;
	public:
		ContentProcessor (ObjectState* os);

		void	FieldFound	(const GS::String& fieldName);
		void	NoValueFound ();
		void	BoolFound	 (bool value);
		void	IntFound	 (Int64 value);
		void	UIntFound	 (UInt64 value);
		void	RealFound	 (double value);
		void	StringFound  (const UniString& value);
		void	ObjectEntered ();
		void	ObjectExited  ();
		void	ListEntered	  ();
		void	ListExited	  ();
	};

	struct GSROOT_DLL_EXPORT Result {
		bool      containsField;
		GSErrCode errorCode;

		Result (bool containsField) : containsField (containsField), errorCode (NoError) {}
		Result (GSErrCode errorCode) : containsField (true), errorCode (errorCode) {}

		operator bool () const { return containsField && errorCode == NoError; }
	};

	class GSROOT_DLL_EXPORT Field {
	private:
		GS::String	name;
		Type		type;
		bool		required;
		UniString	description;

	public:
		Field ();
		Field (const GS::String& name, Type type, Optionality optionality, const UniString& description = "");

		GS::String			 GetName (void) const;
		bool				 IsRequired (void) const;
		Type				 GetType (void) const;
		bool				 IsType (Type type) const;
		bool				 IsTypeCompatibleWith (Type type) const;

		GSErrCode			 Store (ObjectState& os) const;
		GSErrCode			 Restore (const ObjectState& os);
	};


	class GSROOT_DLL_EXPORT Schema {
	private:
		Array<Field> fields;

	public:
		explicit Schema (std::initializer_list<const Field*> fieldList);


		void			Clear (void);
		bool			IsEmpty (void) const;

		ErrorStatus		Validate (const ObjectState& os) const;
		void			Enumerate (const std::function<void (const Field&)>& processor) const;
		bool			HasField (const GS::String& fieldName) const;

		GSErrCode		Store (ObjectState& os) const;
		GSErrCode		Restore (const ObjectState& os);
	};
};


GSErrCode	Store (ObjectState& os, const ObjectState::Field& field);
GSErrCode	Restore (const ObjectState& os, ObjectState::Field& field);

GSROOT_DLL_EXPORT GSErrCode		Store (ObjectState& os, const ObjectState::Schema& field);
GSROOT_DLL_EXPORT GSErrCode		Restore (const ObjectState& os, ObjectState::Schema& field);

template <class Type1, class Type2>
GSErrCode	Store (ObjectState& os, const Pair<Type1, Type2>& pair);

template <class Type1, class Type2>
GSErrCode	Restore (const ObjectState& os, Pair<Type1, Type2>& pair);


struct ObjectState::Value {
	Type type;

	Value (const Type type) : type (type) {}

	virtual ~Value ();

	virtual Value* Clone () const = 0;
};


struct ObjectState::BoolValue : Value {
	bool value;

	BoolValue (const bool value) : value (value), Value (Bool) {}

	virtual ~BoolValue();

	virtual Value* Clone () const;
};


struct ObjectState::UIntValue : Value {
	UInt64 value;

	UIntValue (const UInt64 value) : value (value), Value (UInt) {}

	virtual ~UIntValue ();

	virtual Value* Clone () const;
};


struct ObjectState::IntValue : Value {
	Int64 value;

	IntValue (const Int64 value) : value (value), Value (Int) {}

	virtual ~IntValue ();

	virtual Value* Clone () const;
};


struct ObjectState::RealValue : Value {
	double value;

	RealValue (const double value) : value (value), Value (Real) {}

	virtual ~RealValue ();

	virtual Value* Clone () const;
};


struct ObjectState::StringValue : Value {
	UniString value;

	StringValue (const UniString& value) : value (value), Value (String) {}

	virtual ~StringValue ();

	virtual Value* Clone () const;
};


struct ObjectState::ObjectValue : Value {
	ObjectState* value;

	ObjectValue (ObjectState* value) : value (value), Value (Object) {}

	virtual ~ObjectValue ();

	virtual Value* Clone () const;

private:
	ObjectValue (const ObjectValue& source);				// disabled
	ObjectValue& operator= (const ObjectValue& source);		// disabled
};


struct ObjectState::ListValue : Value {
	Array<Value*> value;

	ListValue (const Array<Value*>& value) : value (value), Value (List) {}

	virtual ~ListValue ();

	virtual Value* Clone () const;
	

private:
	ListValue(const ListValue& source);					// disabled
	ListValue& operator= (const ListValue& source);		// disabled
};


inline ObjectState::ObjectState()
{
}


inline ObjectState::~ObjectState()
{
	Clear();
}


template <class T, class... Fields>
ObjectState::ObjectState (const GS::String& fieldName, const T& value, Fields&&... fields)
{
	AddFields (fieldName, value, std::forward<Fields> (fields)...);
}


template <class T, class... Fields>
void	ObjectState::AddFields (const GS::String& fieldName, const T& value, Fields&&... fields)
{
	Add (fieldName, value);
	AddFields (std::forward<Fields> (fields)...);
}



template <class T>
GSErrCode	ObjectState::AddObject (const GS::String& fieldName, const T& value, Convertible<T>)
{
	typename ObjectStateTypeConversion<T>::ConvertedType convertedValue;
	GSErrCode err = ObjectStateTypeConversion<T>::Convert (value, convertedValue);

	if (err != NoError)
		return err;

	return Add (fieldName, convertedValue);
}


template <class T>
GSErrCode	ObjectState::AddObject (const GS::String& fieldName, const T& value, NotConvertible<T>)
{
	Owner<ObjectState> os (new ObjectState);

	GSErrCode err = Store (*os, value);

	if (err == NoError)
		fields.Add (fieldName, CreateObjectValue (os.Release ()));

	return err;
}


template <class T>
GSErrCode	ObjectState::AddValue (Array<Value*>& list, const T& value, NotEnumerable<T>)
{
	Owner<ObjectState> os (new ObjectState);

	GSErrCode err = Store (*os, value);

	if (err == NoError)
		list.Push (CreateObjectValue (os.Release ()));

	return err;
}


template <class T>
GSErrCode	ObjectState::AddValue (Array<Value*>& list, const T& value, Enumerable<T>)
{
	Array<Value*> array;

	for (const auto& item : value)
		AddValue (array, item);

	list.Push (CreateListValue (array));

	return NoError;
}


template <class T>
ObjectState::Result  ObjectState::GetObject (const GS::String& fieldName, T& value, Convertible<T>) const
{
	typename ObjectStateTypeConversion<T>::ConvertedType convertedValue;

	Result result = Get (fieldName, convertedValue);
	if (result.containsField)
		result = ObjectStateTypeConversion<T>::Convert (convertedValue, value);

	return result;
}


template <class T>
ObjectState::Result  ObjectState::GetObject (const GS::String& fieldName, T& value, NotConvertible<T>) const
{
	ObjectValue* retValue = nullptr;
	if (fields.Get (fieldName, reinterpret_cast<Value**> (&retValue))) {
		ObjectState* os = GetObjectState (retValue);

		if (os == nullptr)
			return Error;
		else
			return Restore (*os, value);
	}

	return Error;
}


template <class T>
GSErrCode	ObjectState::GetValue (const Array<Value*>& list, UIndex idx, T& outValue, NotEnumerable<T>) const
{
	ObjectValue* listItem = reinterpret_cast<ObjectValue*> (list[idx]);

	ObjectState* os = GetObjectState (listItem);

	if (os == nullptr)
		return Error;
	else
		return Restore (*os, outValue);
}


template <class T>
GSErrCode	ObjectState::GetValue (const Array<Value*>& list, UIndex idx, T& outValue, Enumerable<T>) const
{
	const Array<Value*>* array = GetValueArray (reinterpret_cast<ListValue*> (list[idx]));
	
	if (array == nullptr)
		return Error;
	
	auto inserter = GetInserter (outValue);
	
	for (UIndex i = 0; i < array->GetSize (); ++i) {
		DecayedFirstArgumentType<decltype (inserter)> listValue;

		if (GetValue (*array, i, listValue) != NoError)
			return Error;

		inserter (std::move (listValue));
	}
	
	return NoError;
}


template <class T>
GSErrCode	ObjectState::Add (const GS::String& fieldName, const T& value, NotEnumerable<T>, NotEnumType<T>)
{
	if (DBVERIFY (!Contains (fieldName)))
		return AddObject (fieldName, value);

	return Error;
}


template <class T>
GSErrCode	ObjectState::Add (const GS::String& fieldName, const T& value, Enumerable<T>, NotEnumType<T>)
{
	if (DBVERIFY (!Contains (fieldName))) {

		Array<Value*> array;

		for (const auto& item : value) {
			if (AddValue (array, item) != NoError)
				return Error;
		}

		fields.Add (fieldName, CreateListValue (array));

		return NoError;
	}

	return Error;
}


template <class T>
GSErrCode	ObjectState::Add (const GS::String& fieldName, const T& value, EnumType<T>)
{
	return Add (fieldName, static_cast<UnderlyingType<T>> (value));
}


template <class T>
GSErrCode	ObjectState::Add (const ObjectState::Field& field, const T& value)
{
	return Add (field.GetName (), value);
}


template <class T>
auto	ObjectState::AddList (const GS::String& fieldName)
{
	Value* value = CreateListValue ({});
	fields.Add (fieldName, value);

	return [value, this] (const T& item) {
		AddValue (GetValueArray (reinterpret_cast<ListValue*> (value)), item);
	};
}


template <class T>
ObjectState::Result	ObjectState::Get (const GS::String& fieldName, T& value, NotEnumerable<T>, NotEnumType<T>) const
{
	return GetObject (fieldName, value);
}


template <class T>
ObjectState::Result	ObjectState::Get (const GS::String& fieldName, T& value, Enumerable<T>, NotEnumType<T>) const
{
	ListValue* retValue = nullptr;
	if (fields.Get (fieldName, reinterpret_cast<Value**> (&retValue))) {
		const Array<Value*>* array = GetValueArray (retValue);

		if (array == nullptr)
			return false;

		auto inserter = GetInserter (value);

		for (UIndex i = 0; i < array->GetSize (); ++i) {
			DecayedFirstArgumentType<decltype (inserter)> listValue;

			if (GetValue (*array, i, listValue) != NoError)
				return Error;

			inserter (std::move (listValue));
		}
	} else {
		return false;
	}

	return NoError;
}


template <class T>
ObjectState::Result		ObjectState::Get (const GS::String& fieldName, T& value, EnumType<T>) const
{
	UnderlyingType<T> underlyingType;
	Result ret = Get (fieldName, underlyingType);
	value = static_cast<T> (underlyingType);

	return ret;
}


template<class T>
bool ObjectState::Get (const ObjectState::Field& field, T& value) const
{
	return Get (field.GetName (), value);
}


template <class T>
void	ObjectState::Get (const GS::String& fieldName, T& value, const T& defaultValue) const
{
	if (Contains (fieldName))
		Get (fieldName, value);
	else
		value = defaultValue;
}


template<class T>
void ObjectState::Get (const ObjectState::Field& field, T& value, const T& defaultValue) const
{
	Get (field.GetName (), value, defaultValue);
}


template <class Type1, class Type2>
GSErrCode	Store (ObjectState& os, const Pair<Type1, Type2>& pair)
{
	return StorePair (os, pair.first, pair.second);
}


template <class Type1, class Type2>
GSErrCode	StorePair (ObjectState& os, const Type1& first, const Type2& second)
{
	os.Add ("first", first);
	os.Add ("second", second);

	return NoError;
}


template <class Type1, class Type2>
GSErrCode	Restore (const ObjectState& os, Pair<Type1, Type2>& pair)
{
	if (!os.Get ("first", pair.first))
		return Error;

	if (!os.Get ("second", pair.second))
		return Error;

	return NoError;
}

} // namespace GS

#endif