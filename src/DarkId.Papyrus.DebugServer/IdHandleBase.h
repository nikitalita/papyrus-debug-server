#pragma once
#include "IdMap.h"

namespace DarkId::Papyrus::DebugServer
{
	template<class T>
	class IdHandleBase
	{
		IdMap<T>* m_idMap;

	public:
		explicit IdHandleBase(IdMap<T>* idMap)
			: m_idMap(idMap)
		{
			static_assert(std::is_base_of<IdHandleBase<T>, T>());
			m_idMap->Add(static_cast<T*>(this));
		}

		virtual ~IdHandleBase()
		{
			m_idMap->Remove(static_cast<T*>(this));
		}

		UInt32 GetId() const
		{
			return m_idMap->GetId(static_cast<T*>(this));
		}
	};
}
