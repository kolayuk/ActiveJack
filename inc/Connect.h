/*
========================================================================
 Name        : Connect.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef CONNECT_H
#define CONNECT_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
#include <eiklbo.h>
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CAknDoubleStyleListBox;
class CEikTextListBox;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Container class for Connect
 * 
 * @class	CConnect Connect.h
 */
class CConnect : public CCoeControl
	,MEikListBoxObserver	{
public:
	// constructors and destructor
	CConnect();
	static CConnect* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	static CConnect* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	virtual ~CConnect();

public:
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );
	void HandleResourceChange( TInt aType );
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
	void InitializeControlsL();
	void LayoutControls();
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	static void AddListBoxItemL( 
			CEikTextListBox* aListBox,
			const TDesC& aString );
	static RArray< TInt >* GetSelectedListBoxItemsLC( CEikTextListBox* aListBox );
	static void DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox );
	CAknDoubleStyleListBox* ListBox();
	static void CreateListBoxItemL( TDes& aBuffer, 
			const TDesC& aMainText,
			const TDesC& aSecondaryText );
	void AddListBoxResourceArrayItemL( TInt aResourceId );
	void SetupListBoxIconsL();
	TBool HandleMarkableListCommandL( TInt aCommand );
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CAknDoubleStyleListBox* iListBox;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [Overridden Methods]
protected: 
	void HandleListBoxEventL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	void Edit( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	void EditInList( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	void HandleListBoxEnterKeyPressedL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	// ]]] end [User Handlers]
	
public: 
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		EListBox,
		
		// ]]] end generated region [Generated Contents]
		
		// add any user-defined entries here...
		
		ELastControl
		};
	enum TListBoxImages
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		EListBoxFirstUserImageIndex
		
		// ]]] end generated region [Generated Enums]
		
		};
	
	// [[[ begin [MEikListBoxObserver support]
private: 
	typedef void ( CConnect::*ListBoxEventHandler )( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent );
	
	void AddListBoxEventHandlerL( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent, 
			ListBoxEventHandler aHandler );
	
	struct TListBoxEventDispatch 
		{ 
		CEikListBox* src; 
		TListBoxEvent event; 
		ListBoxEventHandler handler;
		};
		
	RArray< TListBoxEventDispatch > iListBoxEventDispatch;
	// ]]] end [MEikListBoxObserver support]
	
	};
				
#endif // CONNECT_H
