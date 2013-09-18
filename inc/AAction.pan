
#ifndef AACTION_PAN_H
#define AACTION_PAN_H

/** AAction application panic codes */
enum TAActionPanics
	{
	EAActionUi = 1
	// add further panics here
	};

inline void Panic(TAActionPanics aReason)
	{
	_LIT(applicationName,"AAction");
	User::Panic(applicationName, aReason);
	}

#endif // AACTION_PAN_H
