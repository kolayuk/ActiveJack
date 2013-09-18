/*
 ============================================================================
 Name		: OnEventAction.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : COnEventAction declaration
 ============================================================================
 */

#ifndef ONEVENTACTION_H
#define ONEVENTACTION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <hwrmlight.h>
#include <f32file.h>
#include <hwrmvibra.h>
#include <AudioPlayer.h>
#include <aiplayerpluginengine.h>
#include <aiplayerpluginengineobserver.h>
#include <btengconnman.h>



//const TUid  KMusicPlayerAppUid = { 0x102072C3 };

class COnEventAction : public CBase, public MAiPlayerPluginEngineObserver
	{
public:
	void ConstructL();
	~COnEventAction();
	COnEventAction();
	static COnEventAction* NewL();
	static COnEventAction* NewLC();
	void OnEvent(TInt aState, TInt aPosToDo=0);

	void PlayerStateChanged(TMPlayerState aState);
	void TrackInfoChanged(const TDesC& aTitle,const TDesC& aArtist);
	void PlaybackPositionChanged(TInt aPosition);
	void PlaylisIsEmpty();
	void Opening();
	void AlbumArtChanged(CFbsBitmap* aBitmap);

private:
	static void OpenFile(TDes& aFile);
	void PressKey(TInt aKey);
	CHWRMLight* iLight;
	CBTEngConnMan* iBT;
	void Launch(TUid aUid);
	void Close(TUid aUid);
	void Kill(TUid aUid);
	void ToBG(TUid aUid);
	void ToFG(TUid aUid);
	void KeyLock(TInt aVal);
	void SwitchLightSensor(TInt aVal);
	void SetLight(TInt aVal);
	void SimulateStylus(TInt aX,TInt aY);
	void SetProfile(TInt aId);
	void Bluetooth(TInt aStatus);
	void GetS60PlatformVersionL( RFs& aFs, TInt& aMajor, TInt& aMinor );
	CPlayerUtility* iPlayer;
	CHWRMVibra* iVibro;
	CAiPlayerPluginEngine* iPlayerController;
	TBool iLaunchingPlayer;
	};

#endif // ONEVENTACTION_H
