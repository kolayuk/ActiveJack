/*
========================================================================
 Name        : DisconnectView.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <AAction.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "AAction.hrh"
#include "DisconnectView.h"
#include "Connect.hrh"
#include "Disconnect.hrh"
#include "Disconnect.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <MenuActions.h>
#include <AActionAppUi.h>
#include <logger.h>
#include <logger.h>
#include <const.h>



/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CDisconnectView::CDisconnectView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iDisconnect = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CDisconnectView::~CDisconnectView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iDisconnect;
	iDisconnect = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CDisconnectView
 */
CDisconnectView* CDisconnectView::NewL()
	{
	CDisconnectView* self = CDisconnectView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CDisconnectView
 */
CDisconnectView* CDisconnectView::NewLC()
	{
	CDisconnectView* self = new ( ELeave ) CDisconnectView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CDisconnectView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_DISCONNECT_DISCONNECT_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	}

/**
 * @return The UID for this view
 */
TUid CDisconnectView::Id() const
	{
	return TUid::Uid( EDisconnectViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CDisconnectView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EDisconnectViewControlPaneRightId:
			commandHandled = Hide( aCommand );
			break;
		case EDisconnectViewMenuItem1Command:
			commandHandled = AddAction( aCommand );
			break;
		case EDisconnectView_MenuItemCommand:
			commandHandled = Edit( aCommand );
			break;
		case EDisconnectViewMenuItem2Command:
			commandHandled = RemoveAction( aCommand );
			break;
		case EDisconnectView_MenuItem2Command:
			commandHandled = Switch( aCommand );
			break;
		case EDisconnectViewMenuItem3Command:
			commandHandled = Help( aCommand );
			break;
		case EDisconnectViewMenuItem6Command:
			commandHandled = About( aCommand );
			break;
		case EDisconnectView_MenuItem1Command:
			commandHandled = OtherProducts( aCommand );
			break;
		case EDisconnectViewMenuItem7Command:
			commandHandled = Exit( aCommand );
			break;
		case EDisconnectOpenSettings:
			CMenuActions::OpenSetting();
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EDisconnectViewControlPaneRightId )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	// ]]] end generated region [Generated Code]
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CDisconnectView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iDisconnect == NULL )
		{
		iDisconnect = CreateContainerL();
		iDisconnect->SetMopParent( this );
		AppUi()->AddToStackL( *this, iDisconnect );
		} 
	// ]]] end generated region [Generated Contents]
	Update();
	}

/**
 */
void CDisconnectView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iDisconnect != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iDisconnect );
		delete iDisconnect;
		iDisconnect = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CDisconnectView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CDisconnectView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_DISCONNECT_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CDisconnectView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CDisconnect::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CDisconnect
 */
CDisconnect* CDisconnectView::CreateContainerL()
	{
	return CDisconnect::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::AddAction( TInt aCommand )
	{
	CMenuActions::AddAction(Id());
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::RemoveAction( TInt aCommand )
	{
	if (iDisconnect->ListBox()->Model()->ItemTextArray()->MdcaCount()>0){CMenuActions::DelAction(Id(),iDisconnect->ListBox()->CurrentItemIndex());}
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::Help( TInt aCommand )
	{
	CMenuActions::Help();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::About( TInt aCommand )
	{
	CMenuActions::About();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::Exit( TInt aCommand )
	{
	CMenuActions::Exit();
	return ETrue;
	}
				
/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::Hide( TInt aCommand )
	{
	CMenuActions::Hide();
	return ETrue;
	}
void CDisconnectView::Update()
	{
	_LOG(_L("CDisconnectView::Update()"));
	((CDesC16Array*)iDisconnect->ListBox()->Model()->ItemTextArray())->Reset();
	for (TInt i=0; i<((CAActionAppUi*)AppUi())->iDisconnectSettings->Count();i++)
		{
		TBuf<255> aText=((CAActionAppUi*)AppUi())->iDisconnectSettings->MdcaPoint(i);
		TBuf<3> aSeparator(KSeparator);
		CDesCArray* arr = new (ELeave) CDesCArrayFlat(3);
		_LOG(aText);
		while (aText.Find(aSeparator)!=KErrNone)
			{
			TInt f=aText.Find(aSeparator);
			if (f==KErrNotFound){break;}
			arr->AppendL(aText.Left(f));
			aText.Copy(aText.Right(Abs(f-aText.Length()+aSeparator.Length())));
			}
		arr->AppendL(aText);
		TBuf<512> buffer;
		TBuf<255> setting;
		TLex conv; TInt intval;
		conv.Assign(arr->MdcaPoint(0));
		conv.Val(intval);
		setting.Copy(CMenuActions::CreateText(intval,arr));
		CDesC16Array* actions=((CDesC16Array*)CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_ACTIONS));
		iDisconnect->CreateListBoxItemL(buffer,actions->MdcaPoint(intval),setting);
		iDisconnect->AddListBoxItemL(iDisconnect->ListBox(),buffer);
		delete arr; delete actions;
		}
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::Edit( TInt aCommand )
	{
	if (iDisconnect->ListBox()->Model()->ItemTextArray()->MdcaCount()>0) 
		{CMenuActions::EditAction(Id(),iDisconnect->ListBox()->CurrentItemIndex());}
	return ETrue;
	}
void CDisconnectView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
	{
	if ((iDisconnect->ListBox()->Model()->NumberOfItems()==0)&&aResourceId==R_DISCONNECT_MENU_PANE1_MENU_PANE)
		{
		aMenuPane->SetItemDimmed(EDisconnectViewMenuItem2Command,ETrue);
		aMenuPane->SetItemDimmed(EDisconnectView_MenuItemCommand,ETrue);
		}
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::OtherProducts( TInt aCommand )
	{
	CMenuActions::OtherProducts();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CDisconnectView::Switch( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EConnectViewId));
	return ETrue;
	}
				
