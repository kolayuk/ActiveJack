/*============================================================================
 Name        : Utils from Utils.h
 Author      : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version     : 1.0
 Copyright   :
 Description : Declares common utils
 ============================================================================*/
#ifndef UTILS_H
#define UTILS_H

#include <e32base.h>
#include <c32comm.h>
#include <e32math.h>
#include <BADESCA.H>

#include "Constants.h"

namespace Utils
{
	void CompleteWithAppPathM(TDes &aPath);
	void OpenBrowser(const TDesC& aUrl);
}

#endif // UTILS_H
// End of File
