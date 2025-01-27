#include "StructStateNode.h"
#include "RuntimeState.h"

namespace DarkId::Papyrus::DebugServer
{
	StructStateNode::StructStateNode(std::string name, RE::BSScript::Struct* value, RE::BSScript::StructTypeInfo* knownType) : m_name(name), m_value(value)
	{
		m_type = RE::BSTSmartPointer<RE::BSScript::StructTypeInfo>(value ? value->GetTypeInfo() : knownType);
	}

	bool StructStateNode::SerializeToProtocol(Variable& variable)
	{
		variable.variablesReference = m_value ? GetId() : 0;
		variable.namedVariables = m_value ? m_value->GetNumProperties() : 0;
		
		variable.name = m_name;
		variable.type = m_type->GetName();
		variable.value = m_value ? variable.type : "None";
		
		return true;
	}

	bool StructStateNode::GetChildNames(std::vector<std::string>& names)
	{
		if (!m_value)
		{
			return true;
		}
		
		for (const auto pair : m_type->members)
		{
			names.push_back(pair.first.c_str());
		}

		return true;
	}

	bool StructStateNode::GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node)
	{
		if (!m_value)
		{
			return false;
		}
		
		const auto propIndex = m_type->members.find(RE::BSFixedString(name));
		if (propIndex == m_type->members.end())
		{
			return false;
		}

		const auto propValue = &m_value->GetPropertyIter()[propIndex->second];
		node = RuntimeState::CreateNodeForVariable(propIndex->first.c_str(), propValue);
		
		return true;
	}
}