/*
========================================================================
 Name        : ConnectView.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef CONNECTVIEW_H
#define CONNECTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CConnect;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for ConnectView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CConnectView ConnectView.h
 */						
			
class CConnectView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CConnectView();
	static CConnectView* NewL();
	static CConnectView* NewLC();        
	void ConstructL();
	virtual ~CConnectView();
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);		
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	void Update();
	// [[[ begin generated region: do not modify [Generated Methods]
	CConnect* CreateContainerL();
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
	TBool Hide( TInt aCommand );
	TBool AddAction( TInt aCommand );
	TBool RemoveAction( TInt aCommand );
	TBool Help( TInt aCommand );
	TBool Donate( TInt aCommand );
	TBool SendComment( TInt aCommand );
	TBool About( TInt aCommand );
	TBool Exit( TInt aCommand );
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
	CConnect* iConnect;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // CONNECTVIEW_H
