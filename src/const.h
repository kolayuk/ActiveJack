/*
 * const.h
 *
 *  Created on: 03.01.2011
 *      Author: mvideo
 */

#ifndef CONST_H_
#define CONST_H_

const TUid KAccessoryCRUid={0x101F8765};
const TUint32 KAccessoryCRKey=0x2;

#ifdef _DEBUG
_LIT(KCallBackUrl,"http://kolaysoft.ru/comments/add.php?project=AAction_D&message=");
#else
_LIT(KCallBackUrl,"http://kolaysoft.ru/comments/add.php?project=AAction&message=");
#endif


_LIT(KConnectSettingsPath,"C:\\System\\Apps\\ActiveJack\\connect.ini");
_LIT(KDisconnectSettingsPath,"C:\\System\\Apps\\ActiveJack\\disconnect.ini");
_LIT(KFirstStartFile,"C:\\system\\apps\\ActiveJack\\firststart");
_LIT(KSettingPath,"C:\\System\\Apps\\ActiveJack\\config.ini");
const TInt KSettingAutostart=1;
const TInt KSettingVibrate=1;
const TInt KSettingBT=1;

_LIT(KEmptyParam," ");
_LIT(KSeparator,"   ");

const TInt KPrefixPlay=0;
const TInt KPrefixPause=1;
const TInt KPrefixStop=2;
const TInt KPrefixSetVolume=3;
const TInt KPrefixLaunch=4;
const TInt KPrefixHide=5;
const TInt KPrefixSwitchTo=6;
const TInt KPrefixClose=7;
const TInt KPrefixKill=8;
const TInt KPrefixKeyLockOn=9;
const TInt KPrefixKeyLockOff=10;
const TInt KPrefixLightSensorOn=11;
const TInt KPrefixLightSensorOff=12;
const TInt KPrefixSetLight=13;
const TInt KPrefixDelay=14;
const TInt KPrefixProfile=15;
const TInt KPrefixBluetoothOn=16;
const TInt KPrefixBluetoothOff=17;
const TInt KPrefixSound=18;
const TInt KPrefixOpenFile=19;
_LIT(KBTFile30,"ActiveJackBT_30.exe");
_LIT(KBTFile32,"ActiveJackBT_32.exe");

#endif /* CONST_H_ */
