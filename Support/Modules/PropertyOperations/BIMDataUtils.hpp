#ifndef BIMDATAUTILS_HPP
#define BIMDATAUTILS_HPP

#include "PropertyOperationsExport.hpp"
#include "ODBIdSpace.hpp"
#include "ProjectTypes.hpp"


namespace BIMData {

class PROPERTY_OPERATIONS_DLL_EXPORT ProjectBIMData
{
public:
	enum class CopySettings {
		CopyClassificationsOnly,
		CopyAllBIMData
	};

	explicit ProjectBIMData (CopySettings copySettings);
	ProjectBIMData (const ProjectBIMData& source) = delete;
	ProjectBIMData& operator= (const ProjectBIMData& source) = delete;
	~ProjectBIMData ();

	bool	SaveFromProject (EDB::ProjectConstRef project);
	bool	LoadToProject (EDB::ProjectRef project, const std::function<void (const EDB::ProjectRef& edbProject)>&	dynamicBuiltInPropertyContainerInitializer);

private:
	ODB::IdSpace idSpace;
	CopySettings copySettings;
	bool		 initDynamicBuiltInContainer;
};

}

#endif