/*
========================================================================
 Name        : AActionAppUi.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <aknnavide.h>
#include <aknnavi.h>
#include <akntabgrp.h>
#include <AAction.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "AActionAppUi.h"
#include "AAction.hrh"
#include "Disconnect.hrh"
#include "Connect.hrh"
#include "AActionApplication.h"
#include "ConnectView.h"
#include "DisconnectView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <aknglobalmsgquery.h>
#include <bautils.h>
#include <const.h>
#include <OnEventAction.h>
#include <apgwgnam.h>
#include <SettingListView.h>
#include <AboutView.h>
/**
 * Construct the CAActionAppUi instance
 */ 
CAActionAppUi::CAActionAppUi(): MCRCallBack()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iNaviDecorator_ = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CAActionAppUi::~CAActionAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( iNaviDecorator_ != NULL )
		{
		delete iNaviDecorator_;
		iNaviDecorator_ = NULL;
		}
	// ]]] end generated region [Generated Contents]
	delete iActions;
	}

// [[[ begin generated function: do not modify
void CAActionAppUi::InitializeContainersL()
	{
	CAknNavigationControlContainer* naviPane = ( CAknNavigationControlContainer* )
		StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
	iNaviDecorator_ = naviPane->ResourceDecorator();
	if ( iNaviDecorator_ != NULL )
		{
		iNaviTabs1 = ( CAknTabGroup* ) iNaviDecorator_->DecoratedControl();
		iNaviDecorator_->MakeScrollButtonVisible(ETrue);
		iNaviDecorator_->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
		}
				
	iConnectView = CConnectView::NewL();
	AddViewL( iConnectView );
	SetDefaultViewL( *iConnectView );
	SetActiveTabByViewId( iConnectView->Id() );
	iDisconnectView = CDisconnectView::NewL();
	AddViewL( iDisconnectView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */

void CAActionAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	if (aCommand==EAknSoftkeyOk)
		{
		CAknNavigationControlContainer* naviPane = ( CAknNavigationControlContainer* )CEikonEnv::Static()->AppUiFactory()->StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
		naviPane->PushL(*iNaviDecorator_);
		ActivateLocalViewL(iPrevView);
		}
		
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CAActionAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CAActionAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	TVwsViewId activeViewId;
	if ( GetActiveViewId( activeViewId ) == KErrNone 
		&& iNaviTabs1->TabIndexFromId( activeViewId.iViewUid.iUid ) 
			== KErrNotFound )
		{
		return EKeyWasNotConsumed;
		}
	
	TInt active = iNaviTabs1->ActiveTabIndex();
	TInt count = iNaviTabs1->TabCount();
	
	switch ( aKeyEvent.iCode )
		{
		case EKeyLeftArrow:
			if ( active > 0 )
				{
				active--;
				ActivateLocalViewL( TUid::Uid( iNaviTabs1->TabIdFromIndex( active ) ) );
				return EKeyWasConsumed;
				}
			break;
		case EKeyRightArrow:
			if ( active + 1 < count )
				{
				active++;
				ActivateLocalViewL( TUid::Uid( iNaviTabs1->TabIdFromIndex( active ) ) );
				return EKeyWasConsumed;
				}
			break;
		default:
			return EKeyWasNotConsumed;
		}
	
				
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CAActionAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( aNewlyActivatedViewId.iAppUid == KUidAActionApplication )
		{
		SetActiveTabByViewId( aNewlyActivatedViewId.iViewUid );
		}
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CAActionAppUi::ConstructL()
	{
	iConnectSettings=new(ELeave) CDesCArrayFlat(3);
	iDisconnectSettings=new(ELeave) CDesCArrayFlat(3);
	
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KFirstStartFile))
		{
		CEikonEnv::Static()->FsSession().Delete(KFirstStartFile);
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KDisconnectSettingsPath)){CEikonEnv::Static()->FsSession().Delete(KDisconnectSettingsPath);}
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KConnectSettingsPath)){CEikonEnv::Static()->FsSession().Delete(KConnectSettingsPath);}
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)){CEikonEnv::Static()->FsSession().Delete(KSettingPath);}
		}
	
	ReadSettings();
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	CAboutView* about_view = CAboutView::NewL();
	AddViewL(about_view);
	CSettingListView* setview=CSettingListView::NewL();
	AddViewL(setview);
	// ]]] end generated region [Generated Contents]
	iActions=COnEventAction::NewL();
	iObserver=CCenRepObserver::NewL(*this);
	iObserver->StartObservingL();
#ifndef _DEBUG
	HideApplicationFromFSW(ETrue);
#endif
	}

TBool CAActionAppUi::GlobalMsgQuery(TPtrC aText,TPtrC aHeader)
	{
	
	    TInt queryAnswer = 1;
	    char* querystr = NULL;
	    int querystr_l = 0;
	    char* headerstr = NULL;
	    int headerstr_l = 0;
	    TRequestStatus msgQueryStatus = KRequestPending;
	    TRequestStatus timerStatus = KRequestPending;
	    int delayInSeconds = 0;
	    TInt timeout = 0;
	    
	    TTimeIntervalMicroSeconds32 timeoutValue = TTimeIntervalMicroSeconds32(timeout);

	    CAknGlobalMsgQuery *msgQueryDialog = NULL;
	    
	    TRAPD(err,
	        {
	            msgQueryDialog = CAknGlobalMsgQuery::NewL();
	        });
	    CleanupStack::PushL(msgQueryDialog);
	    TRAPD(err1,
	        {
	            msgQueryDialog->ShowMsgQueryL(msgQueryStatus,aText,R_AVKON_SOFTKEYS_OK_CANCEL,aHeader, KNullDesC);
	        });
	    if(err1 != KErrNone||err!=KErrNone){
	       CleanupStack::PopAndDestroy(msgQueryDialog);
	    } 
		User::WaitForRequest(msgQueryStatus);
	    
	    CleanupStack::PopAndDestroy(msgQueryDialog);
	    return msgQueryStatus.Int() == EAknSoftkeyOk ? 1 : 0;		
	}
// [[[ begin generated function: do not modify
void CAActionAppUi::SetActiveTabByViewId( TUid aViewId )
	{
	if ( iNaviTabs1 != NULL 
		&& iNaviTabs1->TabIndexFromId( aViewId.iUid ) != KErrNotFound )
		{
		iNaviTabs1->SetActiveTabById( aViewId.iUid );
		}
	}
// ]]] end generated function

void CAActionAppUi::ReadSettings()
	{
	TInt err=KErrNone;
	
	iSettings.Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
			TBuf<255> val;
			RFile filesave;
			TBuf<10> t;
			TFileText ft;
			TInt IntVal;
			filesave.Open(CEikonEnv::Static()->FsSession(), KSettingPath, EFileRead);
			ft.Set(filesave);
			while (ft.Read(val)==KErrNone)
				{
				TLex conv(val);
				conv.Val(IntVal);
				iSettings.Append(IntVal);
				}
			filesave.Close();
			}
		else
			{
			TParse parse;
			CEikonEnv::Static()->FsSession().Parse(KSettingPath,parse);
			if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
				{
				CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
				}
			iSettings.Append(KSettingAutostart);
			iSettings.Append(KSettingVibrate);
			iSettings.Append(KSettingBT);
			}
	
	
	iConnectSettings->Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KConnectSettingsPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
		TBuf<255> val;
		RFile filesave;
		TBuf<10> t;
		TFileText ft;
		filesave.Open(CEikonEnv::Static()->FsSession(), KConnectSettingsPath, EFileRead);
		ft.Set(filesave);
		while (ft.Read(val)==KErrNone)
			{
			iConnectSettings->AppendL(val);
			}
		filesave.Close();
		}
	else
		{
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(KConnectSettingsPath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{
			CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
			}
		}
	
		iDisconnectSettings->Reset();
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KDisconnectSettingsPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
			TBuf<255> val;
			RFile filesave;
			TBuf<10> t;
			TFileText ft;
			filesave.Open(CEikonEnv::Static()->FsSession(), KDisconnectSettingsPath, EFileRead);
			ft.Set(filesave);
			while (ft.Read(val)==KErrNone)
				{
				iDisconnectSettings->AppendL(val);
				}
			filesave.Close();
			}
		else
			{
			TParse parse;
			CEikonEnv::Static()->FsSession().Parse(KDisconnectSettingsPath,parse);
			if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
				{
				CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
				}
			}
	}
void CAActionAppUi::WriteSettings()
	{
		RFs iFS=CEikonEnv::Static()->FsSession();
		RFile filesave;
		TInt err1=filesave.Replace(iFS, KConnectSettingsPath, EFileWrite);
		TFileText ft;
		ft.Set(filesave);
		TInt i;
		for (i=0;i<iConnectSettings->Count();i++)
			{
			ft.Write(iConnectSettings->MdcaPoint(i));
			}
		filesave.Close();
		
		filesave.Replace(iFS, KDisconnectSettingsPath, EFileWrite);
		ft.Set(filesave);
		for (i=0;i<iDisconnectSettings->Count();i++)
			{
			ft.Write(iDisconnectSettings->MdcaPoint(i));
			}
		filesave.Close();
		
		filesave.Replace(iFS, KSettingPath, EFileWrite);
		ft.Set(filesave);
		TBuf<255> temp;
		for (i=0;i<iSettings.Count();i++)
			{
			temp.Num(iSettings[i]);
			ft.Write(temp);
			}
		filesave.Close();
	}
void CAActionAppUi::UpdateView(TUid aView)
	{
	if (aView==TUid::Uid(EConnectViewId))
		{
		iConnectView->Update();
		}
	else if (aView==TUid::Uid(EDisconnectViewId))
		{
		iDisconnectView->Update();
		}
	}
void CAActionAppUi::ValueChanged(TInt aValue)
	{
	CApaWindowGroupName* gn = CApaWindowGroupName::NewL(CEikonEnv::Static()->WsSession(), CEikonEnv::Static()->WsSession().GetFocusWindowGroup());
	if (gn->AppUid()!=TUid::Uid(0x100058b3))
		{iActions->OnEvent(aValue,-1);}
	delete gn;
	}

CArrayFix <TCoeHelpContext>* CAActionAppUi::HelpContextL() const
{
CArrayFixFlat <TCoeHelpContext>* array = new (ELeave) CArrayFixFlat <TCoeHelpContext>(1);
CleanupStack::PushL(array);
TUid uid=TUid::Uid(0x2003732C);
array->AppendL(TCoeHelpContext(uid, _L("ActiveJack_Information")));
CleanupStack::Pop(array);
return array;
}

TBool CAActionAppUi::ProcessCommandParametersL( CApaCommandLine &aCommandLine )
   {
	
   if(aCommandLine.OpaqueData().Length() > 0)
     {
     // Opaque data exists, app. was manually started from the menu
     }
   else
     {
     // App. was auto-started ->exit if auto-start flag in settings is OFF
#ifndef _DEBUG
	   CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	   if (iSettings[0]==0){Exit();}
#endif
     }
   return CEikAppUi::ProcessCommandParametersL( aCommandLine );
  }
