#include "RE/ExtraMissingLinkedRefIDs.h"

#include <cassert>  // assert

#include "RE/BGSKeyword.h"  // BGSKeyword
#include "RE/TESObjectREFR.h"  // TESObjectREFR


namespace RE
{
	auto ExtraMissingLinkedRefIDs::Array::operator[](size_type a_pos)
		-> reference
	{
		assert(a_pos < size());
		return size() > 1 ? _data.entryPtr[a_pos] : _data.entry[a_pos];
	}


	auto ExtraMissingLinkedRefIDs::Array::begin() noexcept
		-> iterator
	{
		return size() > 1 ? _data.entryPtr : _data.entry;
	}


	auto ExtraMissingLinkedRefIDs::Array::end() noexcept
		-> iterator
	{
		return size() > 1 ? std::addressof(_data.entryPtr[size()]) : std::addressof(_data.entry[size()]);
	}


	auto ExtraMissingLinkedRefIDs::Array::size() const noexcept
		-> size_type
	{
		return _size;
	}


	TESObjectREFR* ExtraMissingLinkedRefIDs::GetLinkedRef(BGSKeyword* a_keyword)
	{
		for (auto& entry : entries) {
			if (entry.keyword == a_keyword) {
				auto objRef = RE::TESForm::LookupByID(entry.linkedRefID);
				return objRef ? objRef->GetReference() : 0;
			}
		}
		return 0;
	}
}
