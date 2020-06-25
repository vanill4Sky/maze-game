#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

using StateRef = std::unique_ptr<State>;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	
	/*	\opis dodaje nowy stan programu na stos stanów
		\param newState - wskaźnik na obiekt nowego stanu
		\param isReplacing - czy aktualny stan ma być zastąpiony przez nowy */
	void addState(StateRef newState, bool isReplacing = true);
	void removeState();
	/*	\opis metoda obsługująca stos stanów, 
		zmienia jego status w zależności od  ustawionych przez 
		metody addState i remove State wartości pól klasu typu bool */
	void processStateChanges();
	
	StateRef& getActiveState();

private:
	std::stack<StateRef> mStates;
	StateRef mNewState;
	bool mIsRemoving;
	bool mIsAdding;
	bool mIsReplacing;
};

