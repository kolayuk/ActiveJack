/*
 ============================================================================
 Name		: MenuActions.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CMenuActions implementation
 ============================================================================
 */

#include "MenuActions.h"
#include <eikenv.h>
#include <aknselectionlist.h>
#include <aknlists.h>
#include <AActionAppUi.h>
#include <ConnectView.h>
#include <DisconnectView.h>
#include <AAction.hrh>
#include <AAction.RSG>
#include <eiklbo.h>
#include <eikclbd.h> 
#include <const.h>
#include <logger.h>
#include <aknquerydialog.h>
#include <APGCLI.H>
#include <Connect.h>
#include <Disconnect.h>
#include <hlplch.h>
#include <mprofileengine.h>
#include <mprofilesnamesarray.h>
#include <mprofilename.h>
#include <aknnavi.h>
#include <Utils.h>
#include <AboutView.h>
#include <Constants.h>
#include <FileSelectDialog.h>
#include <mpxcommonframeworkdefs.h>
CMenuActions::CMenuActions()
	{
	// No implementation required
	}

CMenuActions::~CMenuActions()
	{
	}

CMenuActions* CMenuActions::NewLC()
	{
	CMenuActions* self = new (ELeave) CMenuActions();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMenuActions* CMenuActions::NewL()
	{
	CMenuActions* self = CMenuActions::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMenuActions::ConstructL()
	{

	}
void CMenuActions::Hide()
	{
	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	}
void CMenuActions::Exit()
	{
	if ((((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iConnectSettings->Count()>0)||(((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iDisconnectSettings->Count()>0))
		{

		CAknQueryDialog* delete_query = CAknQueryDialog::NewL(CAknQueryDialog::ENoTone);
		TBuf<255> text;
		CEikonEnv::Static()->ReadResource(text, R_EXIT_WARNING);
		delete_query->SetPromptL(text);
		delete_query->PrepareLC(R_EXIT_HIDE_QUERY);
		if (delete_query->RunLD())
			{User::Exit(0);}
		else {CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);}
		}
	else {User::Exit(0);}
	}
void CMenuActions::About()
	{
	CAknNavigationControlContainer* naviPane = ( CAknNavigationControlContainer* )CEikonEnv::Static()->AppUiFactory()->StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
	naviPane->Pop();
	TVwsViewId id;
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->GetActiveViewId(id);
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iPrevView=id.iViewUid;
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->ActivateLocalViewL(KAboutViewId);
	}
void CMenuActions::AddAction(TUid aView)
	{
	_LOG(_L("CMenuActions::AddAction"));
	CDesCArray* Settings;
	TBuf<512> full;
	if (aView==TUid::Uid(EConnectViewId))
		{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iConnectSettings;}
	else if (aView==TUid::Uid(EDisconnectViewId))
		{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iDisconnectSettings;}
	if (!CreateSetting(Settings,full)){return;}
	Settings->AppendL(full);
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->WriteSettings();
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->UpdateView(aView);
	}
void CMenuActions::DelAction(TUid aView, TInt aIndex)
	{
	CAknQueryDialog* delete_query = CAknQueryDialog::NewL(CAknQueryDialog::ENoTone);
	TBuf<255> text;
	CEikonEnv::Static()->ReadResource(text, R_DELETE_TEXT);
	delete_query->SetPromptL(text);
	delete_query->PrepareLC(R_DELETE_QUERY);
	if (!delete_query->RunLD())
		{return;}
	
	CDesCArray* Settings;
	CEikListBox* lb;
	if (aView==TUid::Uid(EConnectViewId))
			{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iConnectSettings;}
	else if (aView==TUid::Uid(EDisconnectViewId))
			{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iDisconnectSettings;}
	if (aView==TUid::Uid(EConnectViewId))
			{lb=((CConnectView*)((CAActionAppUi*)CEikonEnv::Static()->AppUi())->View(aView))->iConnect->ListBox();}
	else if (aView==TUid::Uid(EDisconnectViewId))
			{lb=((CDisconnectView*)((CAActionAppUi*)CEikonEnv::Static()->AppUi())->View(aView))->iDisconnect->ListBox();}
	TInt newi,i=lb->CurrentItemIndex();
	Settings->Delete(aIndex);
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->WriteSettings();
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->UpdateView(aView);
	if (lb->Model()->NumberOfItems()>0){if (i!=0){lb->SetCurrentItemIndexAndDraw(i-1);}else {lb->SetCurrentItemIndexAndDraw(i);}}
	lb->DrawNow();
	}

void CMenuActions::Help()
	{
	/*
	CArrayFix <TCoeHelpContext>* buf = ((CAActionAppUi*)CEikonEnv::Static()->AppUi())->HelpContextL();
	HlpLauncher::LaunchHelpApplicationL(CEikonEnv::Static()->WsSession(), buf);
	*/
	if (User::Language()==16)
		{Utils::OpenBrowser(_L("http://symdeveloper.ru/ru/products/activejack"));}
	else
		{Utils::OpenBrowser(_L("http://symdeveloper.ru/en/products/activejack"));}
	}
TInt CMenuActions::ActionDialog(CDesCArray* aArr,TDes& aTitle)
	{
	TInt sel=0;
	for (TInt i=0; i<aArr->Count();i++){TBuf<255> t;t.Copy(_L("\t")); t.Append(aArr->MdcaPoint(i));t.Append(_L("\t")); aArr->Delete(i); aArr->InsertL(i,t);}
	CAknSelectionListDialog* dlg=CAknSelectionListDialog::NewL(sel,aArr,R_AVKON_DIALOG_EMPTY_MENUBAR);
	dlg->PrepareLC(R_ACTION_SELECTOR);
	dlg->SetTitleL(aTitle);
	((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
	//((CEikListBox*)dlg->Control(ESelectionListControl))->SetCurrentItemIndex(def);
	TInt popupOk=dlg->RunLD();
	if (!popupOk)
		{
		return -1;
		}
	else 
		{
		TBuf<255> a;
		a.Append(_L("Action Dialog Selected: "));
		a.AppendNum(sel);
		_LOG(a);
		return sel;
		}
	}
TInt CMenuActions::NumberQuery(TDes& aText,TInt& aNumber)
{
	CAknNumberQueryDialog* Dialog = CAknNumberQueryDialog::NewL(aNumber,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_NUMBER_QUERY);
	Dialog->SetPromptL(aText);
	return Dialog->RunLD();	
}
TInt CMenuActions::ProfileDialog()
	{
	TInt sel=0; TBuf<255> txt;
	CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
	RArray<TInt> Ids;
	MProfileEngine* eng=CreateProfileEngineL();
	MProfilesNamesArray* arr=eng->ProfilesNamesArrayLC();
	for (TInt i=0; i<arr->MdcaCount();i++)
		{
		txt.Copy(_L("\t"));
		const MProfileName* name=arr->ProfileName(i);
		txt.Append(name->Name());
		txt.Append(_L("\t"));
		itemList->AppendL(txt);
		Ids.Append(name->Id());
		}
	CleanupStack::PopAndDestroy();//arr
	eng->Release();
	CAknSelectionListDialog* dlg=CAknSelectionListDialog::NewL(sel,itemList,R_AVKON_DIALOG_EMPTY_MENUBAR);
	dlg->PrepareLC(R_ACTION_SELECTOR);
	dlg->SetTitleL(_L("AAction"));
	((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
	//((CEikListBox*)dlg->Control(ESelectionListControl))->SetCurrentItemIndex(def);
	TInt popupOk=dlg->RunLD();
	if (!popupOk)
		{
		return -1;
		}
	else 
		{
		TUint32 Id=Ids[sel];
		return Id;
		}		
	}
TUint32 CMenuActions::ApplicationDialog(TDes& aTitle)
	{
	TInt sel=0;
		TInt def=0;
		TBuf<255> result;
		CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
		TInt i=0;
		RApaLsSession AppSession;
		AppSession.Connect();
		RArray<TApplicationInfo> apps;
		TApaAppInfo appInfo;
		AppSession.GetAllApps();
		TBuf<255> UidTxt;
		while (AppSession.GetNextApp(appInfo)==KErrNone)
			{
			if (appInfo.iCaption.Length()<2){continue;}
			TApplicationInfo info;
			info.iCaption=appInfo.iCaption;
			info.iUid=appInfo.iUid;
			apps.Append(info);
			}
		AppSession.Close();
		TLinearOrder<TApplicationInfo> sortOrder(TApplicationInfo::Compare); 
		apps.Sort(sortOrder);
		for (TInt i=0;i<apps.Count();i++)
			{
			TBuf<255> item;
			item.Copy(_L("\t"));
			item.Append(apps[i].iCaption);
			item.Append(_L(" ["));
			UidTxt.Num((TUint)apps[i].iUid.iUid,EHex);
			UidTxt.UpperCase();
			item.Append(UidTxt);
			item.Append(_L("]"));
			item.Append(_L("\t"));
			itemList->AppendL(item);
			}
		CAknSelectionListDialog* dlg=CAknSelectionListDialog::NewL(sel,itemList,R_AVKON_DIALOG_EMPTY_MENUBAR);
		dlg->PrepareLC(R_ACTION_SELECTOR);
		dlg->SetTitleL(aTitle);
		((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
		//((CEikListBox*)dlg->Control(ESelectionListControl))->SetCurrentItemIndex(def);
		TInt popupOk=dlg->RunLD();

		if (!popupOk)
			{
			delete itemList;
			apps.Close();
			return -1;
			}
		else 
			{
			TUint32 Uid=apps[sel].iUid.iUid;
			delete itemList;
			apps.Close();
			return Uid;
			}
		
	}
TPtrC CMenuActions::CreateText(TInt action,CDesC16Array* arr)
	{
	TBuf<255> result;
	/*
	if (action==KPrefixSimulateStylus)
		{
		result.Copy(_L("("));
		result.Append(arr->MdcaPoint(1));
		result.Append(_L(", "));
		result.Append(arr->MdcaPoint(2));
		result.Append(_L(")"));
		}
	*/
	if (action==KPrefixProfile)
		{
		TLex conv; TInt val;
		conv.Assign(arr->MdcaPoint(1)); conv.Val(val);
		MProfileEngine* eng=CreateProfileEngineL();
		MProfilesNamesArray* arr=eng->ProfilesNamesArrayLC();
		val=arr->FindById(val);
		if (val!=KErrNotFound)
			{
			result.Copy(arr->ProfileName(val)->Name());
			}
		CleanupStack::PopAndDestroy(); // arr
		eng->Release();
		}
	if (action==KPrefixKill||action==KPrefixLaunch||action==KPrefixClose||action==KPrefixHide||action==KPrefixSwitchTo)
		{
		RApaLsSession ls;
		ls.Connect();
		TUint u;
		TLex conv(arr->MdcaPoint(1)); conv.Val(u,EHex);
		TUid uid=TUid::Uid(u);
		TApaAppInfo info;
		ls.GetAppInfo(info,uid);
		result.Copy(info.iCaption);
		ls.Close();
		}
	else {result.Copy(arr->MdcaPoint(1));}
	return result;
	}

void CMenuActions::EditAction(TUid aView,TInt aIndex)
	{
	CDesCArray* Settings; TBuf<255> data;
	if (aView==TUid::Uid(EConnectViewId))
		{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iConnectSettings;}
	else if (aView==TUid::Uid(EDisconnectViewId))
		{Settings=((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iDisconnectSettings;}
	if (!CreateSetting(Settings,data)){return;}
	Settings->Delete(aIndex);
	Settings->InsertL(aIndex,data);
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->WriteSettings();
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->UpdateView(aView);
	}
TInt CMenuActions::CreateSetting(CDesCArray* Settings,TDes& aData)
	{
	CAknNavigationControlContainer* naviPane = ( CAknNavigationControlContainer* )CEikonEnv::Static()->AppUiFactory()->StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
	naviPane->Pop();
	TBuf<255> prefix, param,full;
	CDesCArray* arr=(CDesCArray*)CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_ACTIONS);
	TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_ACTION_DIALOG_TITLE);
	TInt action=ActionDialog(arr,title);
	delete arr;
	if (action==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_); return 0;}
	if (action==KPrefixPlay)
		{//play/pause
		param.Copy(KEmptyParam);
		}
	if (action==KPrefixPause)
		{//play/pause
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixSetVolume)
		{
		TInt val=0;
		TBuf<255> format,title; CEikonEnv::Static()->ReadResource(format,R_VOLUME_TITLE);
		title.Format(format,KPbPlaybackVolumeLevelMin,KPbPlaybackVolumeLevelMax);
		if(!NumberQuery(title,val)){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val);
		}
	else if (action==KPrefixStop)
		{//stop
		param.Copy(KEmptyParam);
		}
	/*
	else if (action==KPrefixPressKey)
		{// press key
		TInt val=0;
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_PRESSKEY_TITLE);
		if(!NumberQuery(title,val)){return 0;}
		param.Num(val);
		}
	*/
	else if (action==KPrefixLaunch)
		{ //launch app
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_APPLICATION_TITLE);
		TUint32 val=ApplicationDialog(title);
		if(val==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val,EHex);
		param.UpperCase();
		}
	else if (action==KPrefixHide)
		{// hide app
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_APPLICATION_TITLE);
		TUint32 val=ApplicationDialog(title);
		if(val==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val,EHex);
		param.UpperCase();
		}
	else if (action==KPrefixSwitchTo)
		{//switch to app
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_APPLICATION_TITLE);
		TUint32 val=ApplicationDialog(title);
		if(val==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val,EHex);
		param.UpperCase();
		}
	else if (action==KPrefixClose)
		{//close app
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_APPLICATION_TITLE);
		TUint32 val=ApplicationDialog(title);
		if(val==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val,EHex);
		param.UpperCase();
		}
	else if (action==KPrefixKeyLockOn)
		{//key lock
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixKeyLockOff)
		{//key unlock
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixLightSensorOn)
		{//turn light sensor on
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixLightSensorOff)
		{//turn light sensor off
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixSetLight)
		{// set light
		TBuf<255> n;TInt pos=0; n.Num(KPrefixLightSensorOff); n.Append(KSeparator); n.Append(KEmptyParam);
		if (Settings->Find(n,pos,ECmpNormal)!=0){Settings->InsertL(Settings->Count(),n);}
		TInt val=0;
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_LIGHT_TITLE);
		if(!NumberQuery(title,val)){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val);
		}
	else if (action==KPrefixDelay)
		{// set light
		TInt val=0;
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_DELAY_TITLE);
		if(!NumberQuery(title,val)){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val);
		}
	/*
	else if (action==KPrefixSimulateStylus)
		{
		TInt x=0,y=0;
		TBuf<255> title1,title2; CEikonEnv::Static()->ReadResource(title1,R_STYLUS_TITLE1);CEikonEnv::Static()->ReadResource(title2,R_STYLUS_TITLE2);
		if(!NumberQuery(title1,x)){return 0;}
		if(!NumberQuery(title2,y)){return 0;}
		param.Num(x);
		param.Append(KSeparator);
		param.AppendNum(y);
		}
	*/
	else if (action==KPrefixProfile)
		{
		TInt val=ProfileDialog();
		if(val==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val);
		}
	else if (action==KPrefixKill)
		{//close app
		TBuf<255> title; CEikonEnv::Static()->ReadResource(title,R_APPLICATION_TITLE);
		TUint32 val=ApplicationDialog(title);
		if(val==-1){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Num(val,EHex);
		param.UpperCase();
		}
	else if (action==KPrefixBluetoothOn)
		{
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixBluetoothOff)
		{
		param.Copy(KEmptyParam);
		}
	else if (action==KPrefixSound)
		{
		TBuf<255> fn,title(_L("title"));
		TTypeOfSelect sel=EFile;
		TBuf<255> KMask(_L("*.mp3"));
		TBuf<255> root;
		TInt ok=CFileSelectDialog::RunDlgLD(title,sel,root,KMask,fn);
		if (!ok){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Copy(fn);
		}
	else if (action==KPrefixOpenFile)
		{
		TBuf<255> fn,title(_L("title"));
		TTypeOfSelect sel=EFile;
		TBuf<255> KMask(_L("*.*"));
		TBuf<255> root;
		TInt ok=CFileSelectDialog::RunDlgLD(title,sel,root,KMask,fn);
		if (!ok){naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);return 0;}
		param.Copy(fn);
		}
	prefix.Num(action);
	full.Copy(prefix);
	full.Append(KSeparator);
	full.Append(param);
	_LOG(full);
	aData.Copy(full);
	naviPane->PushL(*((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iNaviDecorator_);
	return 1;
	}
void CMenuActions::OtherProducts()
	{
	TFileName message;
	CEikonEnv::Static()->ReadResource(message, R_BUF_GOTOBUY_DLGMSG);
	CAknQueryDialog* dialog = new (ELeave) CAknQueryDialog();
	dialog->SetPromptL(message);
	TInt ret = dialog->ExecuteLD(R_CONTINUE_CANCEL_QUERY);
	if (ret == EEikBidOk)
		{
		Utils::OpenBrowser(KOurPageInOvi);
		}
	}
void CMenuActions::OpenSetting()
	{
	CEikonEnv::Static()->InfoMsg(_L("OpenSettings"));
	CAknNavigationControlContainer* naviPane = ( CAknNavigationControlContainer* )CEikonEnv::Static()->AppUiFactory()->StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
	naviPane->Pop();
	TVwsViewId id;
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->GetActiveViewId(id);
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->iPrevView=id.iViewUid;
	((CAActionAppUi*)CEikonEnv::Static()->AppUi())->ActivateLocalViewL(KSettingsViewId);
	}
