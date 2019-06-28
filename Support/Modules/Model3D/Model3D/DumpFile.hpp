// *********************************************************************************************************************
// Description:		Dumping Model3D structures into file in different formats
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	MA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_DUMP_FILE)
#define GS_MODELER_DUMP_FILE

#pragma once

#include "AutoPtr.hpp"
#include "UniString.hpp"
#include "Model3D/MeshBodyUtilTemplates.hpp"


namespace IO {
	class File;
}


namespace Modeler {


class MeshBody;


class MODEL3D_DLL_EXPORT DumpFile {
public:
	enum NotificationLevel {SilentMode, NotifyIfFileOpened};

	class MODEL3D_DLL_EXPORT FullPath : public GS::UniString {
	public:
		FullPath (const char* str);
		FullPath (const GS::UniString & str);
		virtual ~FullPath ();
	};

private:
	GS::AutoPtr<IO::File>	file;
	static Int32			dumpFileGlobalCounter;
	NotificationLevel		notificationLevel;

	void CreateFile (GS::UniString fileName);
	void CreateFile (FullPath fileName);

	bool IsFileOpened ();

	void FinalizeFile ();

public:
	// IO::File creation methods
	DumpFile ();
	DumpFile (GS::UniString fileName, NotificationLevel notificationLevel = SilentMode);
	DumpFile (FullPath fileName, NotificationLevel notificationLevel = SilentMode);

	DumpFile& NewFile (GS::UniString fileName, NotificationLevel newNotificationLevel = SilentMode);
	DumpFile& NewFile (FullPath fileName, NotificationLevel newNotificationLevel = SilentMode);

	static void RemoveFile (FullPath fileName);
	// and helper(s)

	static GS::UniString Decorate (GS::UniString fileName);


	// Open and write file
	template <typename MeshBodyType>
	void WriteGDL (MeshBodyType genericBody)
	{
		if (IsFileOpened ()) {
			DumpBodyGDLTemplate (genericBody, *file, Modeler::MeshBody::Default);
		}
	}
	
	void WriteCPP (const Modeler::MeshBody& body);
	void WriteXML (const Modeler::MeshBody& body);
	void Printf (const char * format, ...);

	template <typename MeshBodyType>
	static void WriteBodyGDL (GS::UniString fileName, const MeshBodyType& body, NotificationLevel notificationLevel = SilentMode)
	{
		DumpFile dump (GS::UniString (fileName+".gdl"), notificationLevel);
		dump.WriteGDL (body);
	}
	static void WriteBodyCPP (GS::UniString fileName, const Modeler::MeshBody& body, NotificationLevel notificationLevel = SilentMode);
	static void WriteBodyXML (GS::UniString fileName, const Modeler::MeshBody& body, NotificationLevel notificationLevel = SilentMode);

	// cleanup
	~DumpFile ();
};

} // namespace Modeler {

#endif