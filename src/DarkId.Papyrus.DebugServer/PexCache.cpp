#include "PexCache.h"
#include "Pex.h"

#include <functional>
#include <algorithm>
#include <string>
#include "Decompiler/PscCoder.hpp"
#include "Decompiler/StreamWriter.hpp"

namespace DarkId::Papyrus::DebugServer
{
	bool PexCache::HasScript(const int scriptReference)
	{
		std::lock_guard<std::mutex> scriptLock(m_scriptsMutex);
		
		return m_scripts.find(scriptReference) != m_scripts.end();
	}

	bool PexCache::HasScript(const char* scriptName)
	{
		return HasScript(GetScriptReference(scriptName));
	}

	int PexCache::GetScriptReference(const char* scriptName) const
	{
		const std::hash<std::string> hasher;

		std::string name = scriptName;
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		return std::abs(unrestricted_cast<int>(hasher(name))) + 1;
	}

	std::shared_ptr<Pex::Binary> PexCache::GetScript(const char* scriptName)
	{
		std::lock_guard<std::mutex> scriptLock(m_scriptsMutex);
		
		UInt32 reference = GetScriptReference(scriptName);

		const auto entry = m_scripts.find(reference);
		if (entry == m_scripts.end())
		{
			auto binary = std::make_shared<Pex::Binary>();
			if (LoadPexData(scriptName, *binary))
			{
				m_scripts.emplace(reference, binary);
				return binary;
			}
		}

		return entry != m_scripts.end() ? entry->second : nullptr;
	}

	bool PexCache::GetDecompiledSource(const char* scriptName, std::string& decompiledSource)
	{
		const auto binary = this->GetScript(scriptName);
		if (!binary)
		{
			return false;
		}

		std::basic_stringstream<char> pscStream;
		Decompiler::PscCoder coder(new Decompiler::StreamWriter(pscStream));

		coder.code(*binary);

		decompiledSource = pscStream.str();

		return true;
	}

	bool PexCache::GetSourceData(const char* scriptName, Source& data)
	{
		const auto sourceReference = GetScriptReference(scriptName);

		auto binary = GetScript(scriptName);
		if (!binary)
		{
			return false;
		}
		
		if (strcmp(binary->getHeader().getSourceFileName().c_str(), "") == 0)
		{
			return false;
		}

		data = Source(scriptName, binary->getHeader().getSourceFileName(), sourceReference);

		return true;
	}
}
