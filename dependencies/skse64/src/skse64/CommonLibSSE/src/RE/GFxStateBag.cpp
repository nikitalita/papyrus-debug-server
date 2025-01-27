#include "RE/GFxStateBag.h"

#include <cassert>  // assert


namespace RE
{
	GFxStateBag* GFxStateBag::GetStateBagImpl() const
	{
		return 0;
	}


	GFxStateBag::~GFxStateBag()
	{}


	void GFxStateBag::SetState(GFxState::StateType a_stateType, GFxState* a_state)
	{
		GFxStateBag* stateBag = GetStateBagImpl();
		if (stateBag) {
			assert(a_state->GetStateType() == a_stateType);
			stateBag->SetState(a_stateType, a_state);
		}
	}


	GFxState* GFxStateBag::GetStateAddRef(GFxState::StateType a_stateType) const
	{
		GFxStateBag* stateBag = GetStateBagImpl();
		return stateBag ? stateBag->GetStateAddRef(a_stateType) : 0;
	}


	void GFxStateBag::GetStatesAddRef(GFxState** a_stateList, const GFxState::StateType* a_stateTypes, UInt32 a_count) const
	{
		GFxStateBag* stateBag = GetStateBagImpl();
		if (stateBag) {
			stateBag->GetStatesAddRef(a_stateList, a_stateTypes, a_count);
		}
	}
}
