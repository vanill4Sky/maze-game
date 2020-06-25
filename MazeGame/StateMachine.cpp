#include "StateMachine.hpp"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::addState(StateRef newState, bool isReplacing)
{
	mIsAdding = true;
	mIsReplacing = isReplacing;

	/* check this construction */
	mNewState = std::move(newState);
}

void StateMachine::removeState()
{
	mIsRemoving = true;
}

void StateMachine::processStateChanges()
{
	if (mIsRemoving && !mStates.empty())
	{
		mStates.pop();
		mIsRemoving = false;

		if (!mStates.empty())
		{
			mStates.top()->resume();
		}
	}

	if (mIsAdding)
	{
		if (!mStates.empty())
		{
			if (mIsReplacing)
			{
				mStates.pop();
			}
			else
			{
				mStates.top()->pause();
			}
		}
		mStates.push(std::move(mNewState));
		mStates.top()->init();
		mIsAdding = false;
	}
}

StateRef & StateMachine::getActiveState()
{
	return mStates.top();
}
