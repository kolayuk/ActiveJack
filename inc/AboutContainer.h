/*============================================================================
 Name        : CAboutContainer from AboutContainer.h
 Author	  	 : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version	 : 1.0
 Copyright   : 2010
 Description : Declares container control for application.
============================================================================*/
#ifndef ABOUTCONTAINER_H
#define ABOUTCONTAINER_H

//SYSTEM INCLUDES
#include <coecntrl.h>
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <fbs.h>

//USER INCLUDES
//CLASS DECLARATION
class CAboutContainer : public CCoeControl
{
public:
	void ConstructL(const TRect& aRect);
	CAboutContainer();
	~CAboutContainer();

private:
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void DrawStringCentered(const CFont *font, const TDesC &string, TInt& top, TInt width, CWindowGc& gc) const;
	void SetIconSize(const TRect& aRect);
	void HandleResourceChange(TInt aType);

private: //data
	CAknsBasicBackgroundControlContext* iBgContext;
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	CFbsBitmap *iBitmap;
	CFbsBitmap *iMask;
};
#endif


