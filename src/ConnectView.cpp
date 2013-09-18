/*
========================================================================
 Name        : ConnectView.cpp
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
#include "ConnectView.h"
#include "Connect.hrh"
#include "Disconnect.hrh"
#include "Connect.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <MenuActions.h>
#include <AActionAppUi.h>
#include <logger.h>
#include <const.h>
/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CConnectView::CConnectView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iConnect = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CConnectView::~CConnectView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iConnect;
	iConnect = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CConnectView
 */
CConnectView* CConnectView::NewL()
	{
	CConnectView* self = CConnectView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CConnectView
 */
CConnectView* CConnectView::NewLC()
	{
	CConnectView* self = new ( ELeave ) CConnectView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CConnectView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_CONNECT_CONNECT_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CConnectView::Id() const
	{
	return TUid::Uid( EConnectViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CConnectView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EConnectViewControlPaneRightId:
			commandHandled = Hide( aCommand );
			break;
		case EConnectView_MenuItemCommand:
			commandHandled = AddAction( aCommand );
			break;
		case EConnectView_MenuItem7Command:
			commandHandled = Edit( aCommand );
			break;
		case EConnectView_MenuItem1Command:
			commandHandled = RemoveAction( aCommand );
			break;
		case EConnectView_MenuItem4Command:
			commandHandled = Switch( aCommand );
			break;
		case EConnectView_MenuItem2Command:
			commandHandled = Help( aCommand );
			break;
		case EConnectView_MenuItem5Command:
			commandHandled = About( aCommand );
			break;
		case EConnectView_MenuItem3Command:
			commandHandled = OtherProducts( aCommand );
			break;
		case EConnectView_MenuItem6Command:
			commandHandled = Exit( aCommand );
			break;
		case EConnectOpenSettings:
			CMenuActions::OpenSetting();
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EConnectViewControlPaneRightId )
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
void CConnectView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iConnect == NULL )
		{
		iConnect = CreateContainerL();
		iConnect->SetMopParent( this );
		AppUi()->AddToStackL( *this, iConnect );
		} 
	// ]]] end generated region [Generated Contents]
	Update();
	}

/**
 */
void CConnectView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iConnect != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iConnect );
		delete iConnect;
		iConnect = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CConnectView::HandleStatusPaneSizeChange()
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
void CConnectView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_CONNECT_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CConnectView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CConnect::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CConnect
 */
CConnect* CConnectView::CreateContainerL()
	{
	return CConnect::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::Hide( TInt aCommand )
	{
	CMenuActions::Hide();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::AddAction( TInt aCommand )
	{
	CMenuActions::AddAction(Id());
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::RemoveAction( TInt aCommand )
	{
	if (iConnect->ListBox()->Model()->ItemTextArray()->MdcaCount()>0) {CMenuActions::DelAction(Id(),iConnect->ListBox()->CurrentItemIndex());}
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::Help( TInt aCommand )
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
TBool CConnectView::About( TInt aCommand )
	{
	CMenuActions::About();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::Exit( TInt aCommand )
	{
	CMenuActions::Exit();
	return ETrue;
	}
void CConnectView::Update()
	{
	_LOG(_L("CConnectView::Update()"));
	((CDesC16Array*)iConnect->ListBox()->Model()->ItemTextArray())->Reset();
	for (TInt i=0; i<((CAActionAppUi*)AppUi())->iConnectSettings->Count();i++)
		{
		TBuf<255> aText=((CAActionAppUi*)AppUi())->iConnectSettings->MdcaPoint(i);
		TBuf<3> aSeparator(KSeparator);
		CDesCArray* arr = new (ELeave) CDesCArrayFlat(3);
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
		iConnect->CreateListBoxItemL(buffer,actions->MdcaPoint(intval),setting);
		iConnect->AddListBoxItemL(iConnect->ListBox(),buffer);
		delete arr; delete actions;
		}
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::Edit( TInt aCommand )
	{
	if (iConnect->ListBox()->Model()->ItemTextArray()->MdcaCount()>0) 
		{CMenuActions::EditAction(Id(),iConnect->ListBox()->CurrentItemIndex());}
	return ETrue;
	}
void CConnectView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
	{
	if ((iConnect->ListBox()->Model()->NumberOfItems()==0)&&aResourceId==R_CONNECT_MENU_PANE1_MENU_PANE)
		{
		aMenuPane->SetItemDimmed(EConnectView_MenuItem1Command,ETrue);
		aMenuPane->SetItemDimmed(EConnectView_MenuItem7Command,ETrue);
		}
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::OtherProducts( TInt aCommand )
	{
	CMenuActions::OtherProducts();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConnectView::Switch( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EDisconnectViewId));
	return ETrue;
	}
				
