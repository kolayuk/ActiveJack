/*
========================================================================
 Name        : AActionAppUi.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef AACTIONAPPUI_H
#define AACTIONAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CAknNavigationDecorator;
class CAknTabGroup;
class CConnectView;
class CDisconnectView;
// ]]] end generated region [Generated Forward Declarations]
#include <CenRepObserver.h>
#include <OnEventAction.h>
/**
 * @class	CAActionAppUi AActionAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CAActionAppUi : public CAknViewAppUi, public MCRCallBack
	{
public: 
	// constructor and destructor
	CAActionAppUi();
	virtual ~CAActionAppUi();
	void ConstructL();
	CAknNavigationDecorator* iNaviDecorator_;
public:
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );
	TBool GlobalMsgQuery(TPtrC aText,TPtrC aHeader);
	// from CEikAppUi
	TUid iPrevView;
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );
	void ReadSettings();
	void WriteSettings();
	RArray<TInt> iSettings;
	CCenRepObserver* iObserver;
	COnEventAction* iActions;
	TBool ProcessCommandParametersL( CApaCommandLine &aCommandLine );
	CArrayFix <TCoeHelpContext>* HelpContextL() const;
	void ValueChanged(TInt aVal);
	void UpdateView(TUid aViewId);
	CDesCArray* iConnectSettings;
	CDesCArray* iDisconnectSettings;
	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	void SetActiveTabByViewId( TUid aViewId );
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	// any current navi decorator
	CAknTabGroup* iNaviTabs1;
	CConnectView* iConnectView;
	CDisconnectView* iDisconnectView;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // AACTIONAPPUI_H			
