// *****************************************************************************
//
//                        Classes IChannel, OChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#ifndef CHANNEL_HPP
#define CHANNEL_HPP


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Protocol.hpp"
#include "TypeTraits.hpp"

namespace GS { class Object; }
namespace GS { class Guid; }


// ======================== Class SerializationContext =========================

namespace GS {

class GSROOT_DLL_EXPORT SerializationContext {
private:
	UInt32 flags;	// each bit is a separate flag

	enum { PointerCount = 10 };

	void* pointers[PointerCount];

public:
	class Flag;
	class Pointer;

	SerializationContext ();

	inline void		Set	  (const Flag& flag);
	inline void		Set	  (const Flag& flag, bool newValue);
	inline void		Clear (const Flag& flag);
	inline bool		Get   (const Flag& flag) const;
	inline bool		IsSet (const Flag& flag) const;

	inline void		Set	  (const Pointer& pointer, void* newValue);
	inline void		Clear (const Pointer& pointer);
	inline void*	Get	  (const Pointer& pointer) const;
	inline bool		IsSet (const Pointer& pointer) const;

	template <class Type>
	inline Type*	Get	  (const Pointer& pointer) const;
	

		// types

	class GSROOT_DLL_EXPORT Flag {
	private:
		static UInt32 maskGenerator;

		UInt32 mask;	// mask value of a bit in flags field

	public:
		Flag ();

		friend class SerializationContext;
	};

	class GSROOT_DLL_EXPORT Pointer {
	private:
		static UInt32 indexGenerator;

		UInt32 index;	// index of the pointer in the pointers field

	public:
		Pointer ();

		friend class SerializationContext;
	};
};


inline void		SerializationContext::Set (const Flag& flag)
{
	flags |= flag.mask;
}


inline void		SerializationContext::Set (const Flag& flag, bool newValue)
{
	if (newValue == true)
		flags |= flag.mask;
	else
		flags &= ~flag.mask;
}


inline void		SerializationContext::Clear (const Flag& flag)
{
	flags &= ~flag.mask;
}


inline bool		SerializationContext::Get (const Flag& flag) const
{
	return ((flags & flag.mask) != 0);
}


inline bool		SerializationContext::IsSet (const Flag& flag) const
{
	return ((flags & flag.mask) != 0);
}


inline void		SerializationContext::Set (const Pointer& pointer, void* newValue)
{
	pointers[pointer.index] = newValue;
}


inline void		SerializationContext::Clear (const Pointer& pointer)
{
	pointers[pointer.index] = nullptr;
}


inline void*	SerializationContext::Get (const Pointer& pointer) const
{
	return pointers[pointer.index];
}


template <class Type>
inline Type*	SerializationContext::Get (const Pointer& pointer) const
{
	return static_cast<Type*> (pointers[pointer.index]);
}


inline bool		SerializationContext::IsSet (const Pointer& pointer) const
{
	return (pointers[pointer.index] != nullptr);
}

}	// namespace GS
// ________________________ Class SerializationContext _________________________


// ============================== Class IChannel ===============================

namespace GS {

template <class Type>
class HasReadWriteMethods {};


class GSROOT_DLL_EXPORT IChannel {
private:
	IProtocol*			  iProtocol;		// input protocol for the serialization of built in types
	SerializationContext* context;			// context containing properties and settings for the serialization
	SerializationContext  defaultContext;	// default serialization context

protected:
	IChannel (IProtocol& ip);

public:
		// error codes

	enum {
		EndOfInput = IChannelErrors + 0,	// end of input has been reached, read operation is not completed
		ReadError  = IChannelErrors + 1		// read error on the input device, read operation is not completed
	};

		// destructor

	virtual ~IChannel ();

		// binary input

	virtual GSErrCode	ReadBin	  (char* destination, USize nOfCharToRead, USize* read = nullptr) = 0;
	virtual GSErrCode	CopyBin	  (char* destination, USize nOfCharToCopy, USize* copied = nullptr) = 0;
	virtual GSErrCode	Look	  (UIndex idx, char* c) = 0;
	virtual	GSErrCode	PushBack  (const char* source, USize nOfChar) = 0;
	virtual	GSErrCode	Skip	  (UInt64 nOfCharToSkip, UInt64* skipped = nullptr) = 0;
	virtual	GSErrCode	DirectInputAccess (USize nOfCharToAccess, char** source, USize* accessible = nullptr) = 0;

	virtual GSErrCode	GetInputPosition (UInt64* position) const = 0;
	virtual GSErrCode	GetAvailable     (UInt64* /*available*/) const;
	virtual	GSErrCode	GetAvailable     (USize* available) const;

	virtual bool		IsEOI (void);

	virtual	GSErrCode	PushBack (char c);

		// reading C++ base types and Object

	virtual	void		SetDefaultInputProtocol (void) = 0;
	virtual	void		SetInputProtocol		(IProtocol& ip);
	inline IProtocol&	GetInputProtocol		(void) const;

	GSErrCode	Read (char& c)			 { return iProtocol->Read (*this, c); }
	GSErrCode	Read (unsigned char& c)	 { return iProtocol->Read (*this, c); }
	GSErrCode	Read (bool& b)			 { return iProtocol->Read (*this, b); }
	GSErrCode	Read (short& s)			 { return iProtocol->Read (*this, s); }
	GSErrCode	Read (unsigned short& s) { return iProtocol->Read (*this, s); }
	GSErrCode	Read (int& i)			 { return iProtocol->Read (*this, i); }
	GSErrCode	Read (unsigned int& i)	 { return iProtocol->Read (*this, i); }
	GSErrCode	Read (long& l)			 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (unsigned long& l)	 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (Int64& l)			 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (UInt64& l)		 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (float& f)			 { return iProtocol->Read (*this, f); }
	GSErrCode	Read (double& d)		 { return iProtocol->Read (*this, d); }
	GSErrCode	Read (long double& d)	 { return iProtocol->Read (*this, d); }
	GSErrCode	Read (char* cStr)		 { return iProtocol->Read (*this, cStr); }
	GSErrCode	Read (Object& obj)		 { return iProtocol->Read (*this, obj); }
	GSErrCode	Read (Guid& guid)		 { return iProtocol->Read (*this, guid); }
	template <class Type>
	GSErrCode	Read (HasReadWriteMethods<Type>& arg) { return static_cast<Type&> (arg).Read (*this); }

	static GSErrCode	ConvertObjectReadError (GSErrCode ec);

		// input context

	virtual	void					SetInputContext (SerializationContext& newContext);
	inline SerializationContext&	GetInputContext (void) const;

		// input status

	virtual GSErrCode	GetInputStatus	 (void) const = 0;
	virtual void		ResetInputStatus (void) = 0;
};


inline IProtocol&	IChannel::GetInputProtocol (void) const
{
	return *iProtocol;
}


inline SerializationContext&	IChannel::GetInputContext (void) const
{
	return *context;
}


	// external Read functions

inline GSErrCode	Read (IChannel& ic, char& c)			{ return ic.Read (c); }
inline GSErrCode	Read (IChannel& ic, unsigned char& c)	{ return ic.Read (c); }
inline GSErrCode	Read (IChannel& ic, bool& b)			{ return ic.Read (b); }
inline GSErrCode	Read (IChannel& ic, short& s)			{ return ic.Read (s); }
inline GSErrCode	Read (IChannel& ic, unsigned short& s)	{ return ic.Read (s); }
inline GSErrCode	Read (IChannel& ic, int& i)				{ return ic.Read (i); }
inline GSErrCode	Read (IChannel& ic, unsigned int& i)	{ return ic.Read (i); }
inline GSErrCode	Read (IChannel& ic, long& l)			{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, unsigned long& l)	{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, Int64& l)			{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, UInt64& l)			{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, float& f)			{ return ic.Read (f); }
inline GSErrCode	Read (IChannel& ic, double& d)			{ return ic.Read (d); }
inline GSErrCode	Read (IChannel& ic, long double& d)		{ return ic.Read (d); }
inline GSErrCode	Read (IChannel& ic, char* cStr)			{ return ic.Read (cStr); }
inline GSErrCode	Read (IChannel& ic, Object& obj)		{ return ic.Read (obj); }
inline GSErrCode	Read (IChannel& ic, Guid& guid)			{ return ic.Read (guid); }
template <class Type>
inline GSErrCode	Read (IChannel& ic, HasReadWriteMethods<Type>& arg) { return static_cast<Type&> (arg).Read (ic); }

template <class Type>
inline GSErrCode	ReadType (IChannel& ic, Type& arg) { return Read (ic, arg); }

template <class PersistentType, class Enum>
inline GSErrCode	ReadEnum (IChannel& ic, Enum& e) 
{ 
	static_assert (IsIntegral<PersistentType>, "'PersistentType' should be an integral type.");
	static_assert (IsEnum<Enum>, "'Enum' should be an enum type.");

	PersistentType persistentType;
	GSErrCode err = Read (ic, persistentType);
	e = static_cast<Enum> (persistentType);

	return err;
}

}	// namespace GS
// ______________________________ Class IChannel _______________________________



// ============================== Class OChannel ===============================

namespace GS {

class GSROOT_DLL_EXPORT OChannel {
private:
	OProtocol*			  oProtocol;		// output protocol for the serialization of built in types
	SerializationContext* context;			// context containing properties and settings for the serialization
	SerializationContext  defaultContext;	// default serialization context

protected:
	OChannel (OProtocol& op);

public:
		// error codes

	enum {
		OutputIsFull = OChannelErrors + 0,	// output device is full, write operation is not completed
		WriteError	 = OChannelErrors + 1	// write error on the output device, write operation is not completed
	};

		// destructor

	virtual ~OChannel ();

		// binary output

	virtual GSErrCode	WriteBin (const char* source, USize nOfCharToWrite, USize* written = nullptr) = 0;
	virtual	GSErrCode	DirectOutputAccess (UIndex startPosition, char** output, USize* accessibleDataSize) = 0;

	virtual GSErrCode   GetOutputPosition (UInt64* pos) const = 0;
	virtual GSErrCode	Flush (void);

		// writing C++ base types and Object

	virtual	void		SetDefaultOutputProtocol (void) = 0;
	virtual	void		SetOutputProtocol		 (OProtocol& op);
	inline OProtocol&	GetOutputProtocol		 (void) const;

	GSErrCode	Write (char c)			  { return oProtocol->Write (*this, c); }
	GSErrCode	Write (unsigned char c)	  { return oProtocol->Write (*this, c); }
	GSErrCode	Write (bool b)			  { return oProtocol->Write (*this, b); }
	GSErrCode	Write (short s)			  { return oProtocol->Write (*this, s); }
	GSErrCode	Write (unsigned short s)  { return oProtocol->Write (*this, s); }
	GSErrCode	Write (int i)			  { return oProtocol->Write (*this, i); }
	GSErrCode	Write (unsigned int i)	  { return oProtocol->Write (*this, i); }
	GSErrCode	Write (long l)			  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (unsigned long l)	  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (Int64 l)			  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (UInt64 l)		  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (float f)			  { return oProtocol->Write (*this, f); }
	GSErrCode	Write (double d)		  { return oProtocol->Write (*this, d); }
	GSErrCode	Write (long double d)	  { return oProtocol->Write (*this, d); }
	GSErrCode	Write (const char* cStr)  { return oProtocol->Write (*this, cStr); }
	GSErrCode	Write (const void* p)	  { return oProtocol->Write (*this, p); }
	GSErrCode	Write (const Object& obj) { return oProtocol->Write (*this, obj); }
	GSErrCode	Write (const Guid& guid)  { return oProtocol->Write (*this, guid); }
	template <class Type>
	GSErrCode	Write (const HasReadWriteMethods<Type>& arg) { return static_cast<const Type&> (arg).Write (*this); }

	OChannel&	operator<< (char c)			   { Write (c);	return *this; }
	OChannel&	operator<< (unsigned char c)   { Write (c);	return *this; }
	OChannel&	operator<< (bool b)			   { Write (b);	return *this; }
	OChannel&	operator<< (short s)		   { Write (s);	return *this; }
	OChannel&	operator<< (unsigned short s)  { Write (s);	return *this; }
	OChannel&	operator<< (int i)			   { Write (i);	return *this; }
	OChannel&	operator<< (unsigned int i)	   { Write (i);	return *this; }
	OChannel&	operator<< (long l)			   { Write (l);	return *this; }
	OChannel&	operator<< (unsigned long l)   { Write (l);	return *this; }
	OChannel&	operator<< (Int64 l)		   { Write (l);	return *this; }
	OChannel&	operator<< (UInt64 l)		   { Write (l);	return *this; }
	OChannel&	operator<< (float f)		   { Write (f);	return *this; }
	OChannel&	operator<< (double d)		   { Write (d);	return *this; }
	OChannel&	operator<< (long double d)	   { Write (d);	return *this; }
	OChannel&	operator<< (const char* cStr)  { Write (cStr); return *this; }
	OChannel&	operator<< (const void* p)	   { Write (p);	return *this; }
	OChannel&	operator<< (const Object& obj) { Write (obj); return *this; }
	OChannel&	operator<< (const Guid& guid)  { Write (guid); return *this; }
	template <class Type>
	OChannel&	operator<< (const HasReadWriteMethods<Type>& arg) { Write (arg); return *this; }

	GSErrCode	WriteChar	 (char c)			{ return oProtocol->Write (*this, c); }
	GSErrCode	WriteUChar	 (unsigned char c)	{ return oProtocol->Write (*this, c); }
	GSErrCode	WriteBool	 (bool b)			{ return oProtocol->Write (*this, b); }
	GSErrCode	WriteShort	 (short s)			{ return oProtocol->Write (*this, s); }
	GSErrCode	WriteUShort	 (unsigned short s) { return oProtocol->Write (*this, s); }
	GSErrCode	WriteInt	 (int i)			{ return oProtocol->Write (*this, i); }
	GSErrCode	WriteUInt	 (unsigned int i)	{ return oProtocol->Write (*this, i); }
	GSErrCode	WriteLong	 (Int32 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteULong	 (UInt32 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteInt64	 (Int64 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteUInt64	 (UInt64 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteFloat	 (float f)			{ return oProtocol->Write (*this, f); }
	GSErrCode	WriteDouble	 (double d)			{ return oProtocol->Write (*this, d); }
	GSErrCode	WriteLDouble (long double d)	{ return oProtocol->Write (*this, d); }

		// block support

	virtual GSErrCode	PushMark	(void) = 0;
	virtual GSErrCode	PopMark		(void) = 0;
	virtual USize		GetOffset	(void) const = 0;
	virtual void		ResetOffset	(void) = 0;

	GSErrCode			OpenBlock   (void);
	GSErrCode			CloseBlock  (void);

		// output context

	virtual	void					SetOutputContext (SerializationContext& newContext);
	inline SerializationContext&	GetOutputContext (void) const;

		// output status

	virtual GSErrCode	GetOutputStatus	  (void) const = 0;
	virtual void		ResetOutputStatus (void) = 0;
};


inline OProtocol&	OChannel::GetOutputProtocol (void) const
{
	return *oProtocol;
}


inline SerializationContext&	OChannel::GetOutputContext (void) const
{
	return *context;
}


	// external Write functions

inline GSErrCode	Write (OChannel& oc, char c)			{ return oc.Write (c); }
inline GSErrCode	Write (OChannel& oc, unsigned char c)	{ return oc.Write (c); }
inline GSErrCode	Write (OChannel& oc, bool b)			{ return oc.Write (b); }
inline GSErrCode	Write (OChannel& oc, short s)			{ return oc.Write (s); }
inline GSErrCode	Write (OChannel& oc, unsigned short s)	{ return oc.Write (s); }
inline GSErrCode	Write (OChannel& oc, int i)				{ return oc.Write (i); }
inline GSErrCode	Write (OChannel& oc, unsigned int i)	{ return oc.Write (i); }
inline GSErrCode	Write (OChannel& oc, long l)			{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, unsigned long l)	{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, Int64 l)			{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, UInt64 l)			{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, float f)			{ return oc.Write (f); }
inline GSErrCode	Write (OChannel& oc, double d)			{ return oc.Write (d); }
inline GSErrCode	Write (OChannel& oc, long double d)		{ return oc.Write (d); }
inline GSErrCode	Write (OChannel& oc, const char* cStr)	{ return oc.Write (cStr); }
inline GSErrCode	Write (OChannel& oc, const Object& obj)	{ return oc.Write (obj); }
inline GSErrCode	Write (OChannel& oc, const Guid& guid)	{ return oc.Write (guid); }
inline GSErrCode	Write (OChannel& oc, const void* p)		{ return oc.Write (p); }
template <class Type>
inline GSErrCode	Write (OChannel& oc, const HasReadWriteMethods<Type>& arg) { return static_cast<const Type&> (arg).Write (oc); }

template <class Type>
inline GSErrCode	WriteType (OChannel& oc, const Type& arg) { return Write (oc, arg); }

template <class PersistentType, class Enum>
inline GSErrCode	WriteEnum (OChannel& oc, Enum e)
{
	static_assert (IsIntegral<PersistentType>, "'PersistentType' should be an integral type.");
	static_assert (IsEnum<Enum>, "'Enum' should be an enum type.");

	return Write (oc, static_cast<PersistentType> (e));
}


}	// namespace GS
// ______________________________ Class OChannel _______________________________



// =============================================================================

namespace GS {

GSROOT_DLL_EXPORT GSErrCode		Copy (IChannel& from, OChannel& to, UInt64 maxLength = MaxUInt64);

}	// namespace GS
// _____________________________________________________________________________


#endif
