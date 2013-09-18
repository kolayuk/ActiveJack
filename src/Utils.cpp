/*============================================================================
 Name        : Utils.cpp
 Author      : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version     : 1.0
 Copyright   :
 Description : Common utils
 ============================================================================*/
//SYSTEM INCLUDES
#include <f32file.h>
#include <utf.h>
#include <hash.h>
#include <SysUtil.h>
#include <EZGzip.h>
#include <CHARCONV.H>
#include <BAUTILS.H>
#include <APAID.H>
#include <APGCLI.H>
#include <APGTASK.H>
#include <eikenv.h>

//USER INCLUDES
#include "Utils.h"
#include "Constants.h"

namespace Utils
{
	void CompleteWithAppPathM(TDes &aPath)
	{
		TFileName fullAppName = RProcess().FileName();
		TParse parse;
		TParse parse1;
		parse.Set(fullAppName, NULL, NULL);
		parse1.Set(aPath, NULL, NULL);

		if(parse1.DrivePresent())
		{
			aPath[0] = parse.Drive()[0];
		}
		else
		{
			aPath.Insert(0, parse.Drive());
		}
#ifdef __WINS__
		aPath[0] = 'c';
#endif
	}

#ifndef __WINS__
	const TInt KBrowserUid = 0x10008D39;
#else
	const TInt KBrowserUid = 0x1020724D;
#endif

	void OpenBrowser(const TDesC& aUrl)
	{
		TUid id(TUid::Uid(KBrowserUid));
		TApaTaskList taskList(CEikonEnv::Static()->WsSession());
		TApaTask task = taskList.FindApp(id);

		if (task.Exists())
		{
			HBufC8* param8 = HBufC8::NewLC(100);
			param8->Des().Append(aUrl);
			// Uid is not used
			task.SendMessage(TUid::Uid(0), *param8);
			CleanupStack::PopAndDestroy();
		}
		else
		{
			RApaLsSession appArcSession;
			// connect to AppArc server
			User::LeaveIfError(appArcSession.Connect());
			TThreadId id;
			TInt ret = appArcSession.StartDocument(aUrl, TUid::Uid(KBrowserUid), id);
			appArcSession.Close();
		}
	}
}

// End of File
