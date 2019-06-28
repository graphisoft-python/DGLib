#ifndef ROOM_OPERATIONS_HPP
#define ROOM_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBElements
#include "Room.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT RoomOperations
{
public:
	static void GetStandaloneVisibleMaterials (VBElem::RoomConstRef room, GS::HashSet<short>& materials);
	static void SetHomeStory (VBElem::RoomRef room, const short homeStoryNum);

};

#endif // ROOM_OPERATIONS_HPP
