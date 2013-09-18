/*============================================================================
 Name        : Constants.h
 Author      : Fokin Alexander -= ICQ: 285271527 | E-mail: alexander_fokin@symdeveloper.ru =-
 Copyright   : 2010
 Description : Constants.h - header file
============================================================================*/
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <e32base.h>
#include "Uid.h"

const TUid KAppUid = {APP_UID};

const TUid KAboutViewId 	= {3};
const TUid KSettingsViewId 	= {4};

#ifdef __WINS__
_LIT(KImageFileName,"z:\\resource\\apps\\ActiveJack.mif");
#else
_LIT(KImageFileName,"c:\\resource\\apps\\ActiveJack.mif");
#endif

_LIT(KOurPageInOvi, "http://store.ovi.mobi/publisher/Alexander+Fokin");

#endif // CONSTANTS_H

// End of File







