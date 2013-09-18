/*
 ============================================================================
 Name		: OnEventAction.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : COnEventAction implementation
 ============================================================================
 */

#include "OnEventAction.h"
#include <const.h>
#include <AActionAppUi.h>
#include <eikenv.h>
#include <w32std.h>
#include <apgcli.h>
#include <apgtask.h>
#include <aknkeylock.h>
#include <centralrepository.h>
#include <logger.h>
#include <mprofileengine.h>
#include <Hal.h>
#include <f32file.h>
#include <mpxplaybackutility.h>
#include <apgwgnam.h>

COnEventAction* COnEventAction::NewLC()
	{
	COnEventAction* self = new (ELeave) COnEventAction();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

COnEventAction* COnEventAction::NewL()
	{
	COnEventAction* self = COnEventAction::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}
void COnEventAction::ConstructL()
	{
	iPlayerController = CAiPlayerPluginEngine::NewL(*this);
	iVibro=CHWRMVibra::NewL();
	iBT=CBTEngConnMan::NewL(NULL);
	//iVibro->ReserveVibraL(EFalse,ETrue);
	}
COnEventAction::COnEventAction(): MAiPlayerPluginEngineObserver()
         {
         //do nothing
         }
COnEventAction::~COnEventAction()
    {
	delete iPlayerController;
	delete iVibro;
	delete iBT;
    }

void COnEventAction::OnEvent(TInt aState,TInt aPos)
	{
	_LOGDATA2(_L("On event %d %d"),aState,aPos);
	iLaunchingPlayer=EFalse;
	CDesCArray* Settings;
	if (aState)
		{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iConnectSettings;}
	else
		{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iDisconnectSettings;}
	if (((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iSettings[1]==1)
		{TRAPD(err,{if (iVibro) {iVibro->StartVibraL(50,100);}};);}
	RBTDevAddrArray btarr;
	iBT->GetConnectedAddresses(btarr,EBTProfileA2DP);
	if (btarr.Count()>0&&((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iSettings[2]==0) {return;}
	for (TInt i=0; i<Settings->Count();i++)
		{
		if (i<=aPos){continue;}
		TBuf<255> aText=Settings->MdcaPoint(i);
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
		TLex conv; TInt action;
		conv.Assign(arr->MdcaPoint(0)); conv.Val(action);
		if (action==KPrefixPlay){iPlayerController->iPlaybackUtility->CommandL(EPbCmdPlay);}
		if (action==KPrefixPause){iPlayerController->iPlaybackUtility->CommandL(EPbCmdPause);}
		if (action==KPrefixStop){iPlayerController->iPlaybackUtility->CommandL(EPbCmdStop);}
		if (action==KPrefixSetVolume)
			{
			TInt val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val);
			iPlayerController->iPlaybackUtility->SetL(EPbPropertyVolume,val);
			}
		/*
		if (action==KPrefixPressKey)
			{ // press key
			TInt val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val);
			PressKey(val);
			}
		*/
		if (action==KPrefixLaunch)
			{ // launch
			TUint val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val,EHex);
			Launch(TUid::Uid(val));
			if (val==KMusicPlayerAppUid.iUid)
				{
				iLaunchingPlayer=ETrue;
				}
			}
		if (action==KPrefixHide)
			{// hide to background
			TUint val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val,EHex);
			ToBG(TUid::Uid(val));
			}
		if (action==KPrefixSwitchTo)
			{// hide to background
			TUint val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val,EHex);
			ToFG(TUid::Uid(val));
			}
		if (action==KPrefixClose)
			{ // close
			TUint val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val,EHex);
			Close(TUid::Uid(val));
			}
		if (action==KPrefixKeyLockOn){KeyLock(1);}
		if (action==KPrefixKeyLockOff){KeyLock(0);}
		if (action==KPrefixLightSensorOn){SwitchLightSensor(1);}
		if (action==KPrefixLightSensorOff){SwitchLightSensor(0);}
		if (action==KPrefixSetLight)
			{ // set light
			TInt val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val);
			SetLight(val);
			}
		if (action==KPrefixDelay)
			{ // delay
			TInt val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val);
			User::After(val*1000);
			}
		/*
		if (action==KPrefixSimulateStylus)
			{ // stylus
			TInt x,y; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(x);
			conv.Assign(arr->MdcaPoint(2));conv.Val(y);
			SimulateStylus(x,y);
			}
		*/
		if (action==KPrefixProfile)
			{ // profile
			TInt val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val);
			SetProfile(val);
			}
		if (action==KPrefixKill)
			{ // launch
			TUint val; TLex conv;
			conv.Assign(arr->MdcaPoint(1));conv.Val(val,EHex);
			Kill(TUid::Uid(val));
			}
		if (action==KPrefixBluetoothOn){Bluetooth(1);}
		if (action==KPrefixBluetoothOff){Bluetooth(0);}
		if (action==KPrefixSound)
			{
			iPlayer=CPlayerUtility::NewL(arr->MdcaPoint(1));
			}
		if (action==KPrefixOpenFile)
			{
			TBuf<255> file(arr->MdcaPoint(1));
			OpenFile(file);
			}
		}
	}
	
void COnEventAction::PressKey(TInt aKey)
	{
	KeyLock(0);
	User::After(50000);
	TRawEvent lEvent;
	lEvent.Set(TRawEvent::EKeyDown, aKey);
	UserSvr::AddEvent(lEvent);
	User::After(50000);
	lEvent.Set(TRawEvent::EKeyUp, aKey);
	UserSvr::AddEvent(lEvent);
	User::After(50000);
	KeyLock(1);
	}

void COnEventAction::Launch(TUid aUid)
	{
    RApaLsSession apaLsSession;
    User::LeaveIfError(apaLsSession.Connect());
    CleanupClosePushL(apaLsSession);
    TApaAppInfo appInfo;
    TInt retVal = apaLsSession.GetAppInfo(appInfo, aUid);
 
    if(retVal == KErrNone)
        {
        CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
        cmdLine->SetExecutableNameL(appInfo.iFullName);
        cmdLine->SetCommandL(EApaCommandRun);
        User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );
 
        CleanupStack::PopAndDestroy(cmdLine);
        }
    else
        {
        // The application not found!
        }
    CleanupStack::PopAndDestroy(&apaLsSession);
	}

void COnEventAction::Close(TUid aUid)
	{
	RWsSession iWsSession;
	iWsSession.Connect();
	TApaTaskList* list=new (ELeave) TApaTaskList(iWsSession);
	TApaTask task= list->FindApp(aUid);
	if (task.Exists())
		{task.EndTask();}
	iWsSession.Close();
	}
void COnEventAction::Kill(TUid aUid)
	{
	RWsSession iWsSession;
	iWsSession.Connect();
	TApaTaskList* list=new (ELeave) TApaTaskList(iWsSession);
	TApaTask task= list->FindApp(aUid);
	if (task.Exists())
		{task.KillTask();}
	iWsSession.Close();
	}
void COnEventAction::ToBG(TUid aUid)
	{
	RWsSession iWsSession;
	iWsSession.Connect();
	TApaTaskList* list=new (ELeave) TApaTaskList(iWsSession);
	TApaTask task= list->FindApp(aUid);
	if (task.Exists())
		{task.SendToBackground();}
	iWsSession.Close();
	}

void COnEventAction::ToFG(TUid aUid)
	{
	RWsSession iWsSession;
	iWsSession.Connect();
	TApaTaskList* list=new (ELeave) TApaTaskList(iWsSession);
	TApaTask task= list->FindApp(aUid);
	if (task.Exists())
		{task.BringToForeground();}
	iWsSession.Close();
	}
void COnEventAction::KeyLock(TInt aVal)
	{
	RAknKeylock2 kl;
	kl.Connect();
	if (aVal){kl.EnableWithoutNote();}
	else {kl.DisableWithoutNote();}
	kl.Close();
	}
void COnEventAction::SwitchLightSensor(TInt aVal)
	{
	CRepository* CR=CRepository::NewL(TUid::Uid(0x10200C8C));
	CR->Set(0x3,aVal);
	delete CR;
	}
void COnEventAction::SetLight(TInt aVal)
	{
	CRepository* CR=CRepository::NewL(TUid::Uid(0x10200C8C));
	CR->Set(0x1,aVal);
	delete CR;
	}
void COnEventAction::SimulateStylus(TInt aX,TInt aY)
	{
	TRawEvent lEvent;
	lEvent.Set(TRawEvent::EButton1Down,aX,aY);
	UserSvr::AddEvent(lEvent);
	User::After(50000);
	lEvent.Set(TRawEvent::EButton1Up, aX,aY);
	UserSvr::AddEvent(lEvent);
	}
void COnEventAction::SetProfile(TInt aId)
	{
	MProfileEngine* eng=CreateProfileEngineL();
	eng->SetActiveProfileL(aId);
	eng->Release();
	}
void COnEventAction::Bluetooth(TInt aStatus)
	{
	TBuf<255> cmd,exe; cmd.Num(aStatus);
	TInt major, minor;
	GetS60PlatformVersionL(CEikonEnv::Static()->FsSession(),major,minor);
	if ((major==3&&minor>1)||major>3) {exe.Copy(KBTFile32);}
	else {exe.Copy(KBTFile30);}
	RProcess proc;
	User::LeaveIfError(proc.Create(exe,cmd));
	proc.Resume();
	proc.Close();
	}

void COnEventAction::OpenFile(TDes& aFile)
	{
	RApaLsSession session;
	User::LeaveIfError(session.Connect());
	CleanupClosePushL(session);
	TUid uid;
	TDataType dataType;
	User::LeaveIfError(session.AppForDocument(aFile, uid, dataType));
	TThreadId threadId;
	User::LeaveIfError(session.StartDocument(aFile, dataType, threadId));
	CleanupStack::PopAndDestroy(&session);
	}
void COnEventAction::GetS60PlatformVersionL( RFs& aFs, TInt& aMajor, TInt& aMinor )
    {
	_LIT(KS60ProductIDFile, "Series60v*.sis");
	_LIT(KROMInstallDir, "z:\\system\\install\\");
    TFindFile ff( aFs );
    CDir* result;
    User::LeaveIfError( ff.FindWildByDir( KS60ProductIDFile, KROMInstallDir, result ) );
    CleanupStack::PushL( result );
    User::LeaveIfError( result->Sort( ESortByName|EDescending ) );
    aMajor = (*result)[0].iName[9] - '0';
    aMinor = (*result)[0].iName[11] - '0';
    CleanupStack::PopAndDestroy(); // result
    }

void COnEventAction::PlayerStateChanged(TMPlayerState aState)
	{
	if (aState==EMPlayerStateStopped)
		{
		if (iLaunchingPlayer)
			{
			iPlayerController->iPlaybackUtility->CommandL(EPbCmdPlay);
			}
		}
	}
void COnEventAction::TrackInfoChanged(const TDesC& aTitle,const TDesC& aArtist){}
void COnEventAction::PlaybackPositionChanged(TInt aPosition){}
void COnEventAction::PlaylisIsEmpty(){}
void COnEventAction::Opening(){}
void COnEventAction::AlbumArtChanged(CFbsBitmap* aBitmap){}

/*
TInt COnEventAction::isAppLaunched(TAny* aObj)
	{
	_LOG(_L("Tick"));
	COnEventAction* obj=((COnEventAction*)aObj);
	RWsSession iWsSession;
	iWsSession.Connect();
	TInt id=iWsSession.GetFocusWindowGroup();
	CApaWindowGroupName* wg=CApaWindowGroupName::NewL(iWsSession);
	wg->ConstructFromWgIdL(id);
	TUid uid=wg->AppUid();
	delete wg;
	
	TApaTaskList lst(iWsSession);
	TApaTask fgr=lst.FindByPos(0);
	TApaTask pl=lst.FindApp(obj->iLaunchingUid);
	iWsSession.Close();
	if (pl.WgId()==fgr.WgId())
		{
		obj->iWaitTimer->Cancel();
		obj->OnEvent(obj->iState,obj->iPos);
		_LOG(_L("App started"));
		return 0;
		}
	return 1;
	}
*/
