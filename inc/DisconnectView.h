/*
========================================================================
 Name        : DisconnectView.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef DISCONNECTVIEW_H
#define DISCONNECTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CDisconnect;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for DisconnectView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CDisconnectView DisconnectView.h
 */						
			
class CDisconnectView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CDisconnectView();
	static CDisconnectView* NewL();
	static CDisconnectView* NewLC();        
	void ConstructL();
	virtual ~CDisconnectView();
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	void Update();
	// [[[ begin generated region: do not modify [Generated Methods]
	CDisconnect* CreateContainerL();
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	
	// [[[ begin [Protected Section]
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	// [[[ begin generated region: do not modify [Overridden Methods]
	// ]]] end generated region [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
	TBool AddAction( TInt aCommand );
	TBool RemoveAction( TInt aCommand );
	TBool Help( TInt aCommand );
	TBool Donate( TInt aCommand );
	TBool SendComment( TInt aCommand );
	TBool About( TInt aCommand );
	TBool Exit( TInt aCommand );
	TBool Hide( TInt aCommand );
	TBool Edit( TInt aCommand );
	TBool OtherProducts( TInt aCommand );
	TBool Switch( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
public:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CDisconnect* iDisconnect;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // DISCONNECTVIEW_H
