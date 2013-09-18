/*============================================================================
 Name        : CAboutContainer from AboutContainer.h
 Author	  	 : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version	 : 1.0
 Copyright   : 2010
 Description : Container control implementation
 ============================================================================*/
//SYSTEM INCLUDES
#include <akndef.hrh>
#include <aknutils.h>
#include <APGCLI.H>

//USER INCLUDES
#include "AboutContainer.h"
#include "Constants.h"
#include RSG_FILE
#include "Utils.h"
#include "Version.h"

CAboutContainer::CAboutContainer()
{
}

void CAboutContainer::ConstructL(const TRect& aRect)
{
	CreateWindowL();
	iBgContext = CAknsBasicBackgroundControlContext::NewL(KAknsIIDQsnBgAreaMain, aRect, EFalse);
	TFileName fileName = KImageFileName();

#ifndef __WINS__
	Utils::CompleteWithAppPathM(fileName);
#endif

	AknIconUtils::CreateIconL(iBitmap, iMask, fileName, 16384, 16385);
	SetIconSize(aRect);
	SetRect(aRect);
	ActivateL();
}

CAboutContainer::~CAboutContainer()
{
	delete iBgContext;
	delete iBitmap;
	delete iMask;
}

TTypeUid::Ptr CAboutContainer::MopSupplyObject(TTypeUid aId)
{
	if (iBgContext != NULL)
	{
		return MAknsControlContext::SupplyMopObject(aId, iBgContext);
	}
	return CCoeControl::MopSupplyObject(aId);
}

void CAboutContainer::DrawStringCentered(const CFont *font, const TDesC &string, TInt& top, TInt width, CWindowGc& gc) const
{
	CArrayFixFlat<TPtrC> *arrStr = new CArrayFixFlat<TPtrC> (5);
	CleanupStack::PushL(arrStr);
	TRAPD(err, AknTextUtils::WrapToArrayL(string, width - 10, *font, *arrStr));
	if (err == KErrNone)
	{
		for (int i = 0; i < arrStr->Count(); i++)
		{
			TInt txtWidth = font->TextWidthInPixels((*arrStr)[i]);
			TPoint pt(width / 2 - txtWidth / 2, top);
			gc.DrawText((*arrStr)[i], pt);
			top += font->HeightInPixels() + 5;
		}
	}
	CleanupStack::PopAndDestroy(arrStr);
}

void CAboutContainer::SizeChanged()
{
	if (iBgContext != NULL)
	{
		iBgContext->SetRect(Rect());
	}
}

void CAboutContainer::HandleResourceChange(TInt aType)
{
	if (aType == KEikDynamicLayoutVariantSwitch)
	{
		TRect rect;
		AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
		SetRect(rect);
		SetIconSize(rect);
	}
}

void CAboutContainer::SetIconSize(const TRect& aRect)
{
	TInt icon_width = (TInt)(aRect.Width() / 2);
	TInt icon_height = (TInt)(icon_width / 5.35);
	AknIconUtils::SetSize(iBitmap, TSize(icon_width, icon_height), EAspectRatioPreserved);
	AknIconUtils::SetSize(iMask, TSize(icon_width, icon_height), EAspectRatioPreserved);
}

TInt CAboutContainer::CountComponentControls() const
{
	return NULL; // return nbr of controls inside this container
}

CCoeControl* CAboutContainer::ComponentControl(TInt aIndex) const
{
	switch (aIndex)
	{
		default:
			return NULL;
	}
}

void CAboutContainer::Draw(const TRect& aRect) const
{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Redraw the background using the default skin
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);
	AknsDrawUtils::Background(skin, cc, this, gc, aRect);

	TRgb textColor;
	AknsUtils::GetCachedColor(skin, textColor, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6); // text #6	main area	main area texts	#215

	TRect rect(iBitmap->SizeInPixels());
	TInt client_width = aRect.Width();
	TInt bitmap_width = rect.Width();
	TInt bitmap_height = rect.Height();
	TInt x_coord = (client_width - bitmap_width) / 2;
	TInt y_coord = 10;

	TRect canvas = TRect(x_coord - 5, y_coord - 5, x_coord + bitmap_width + 5, y_coord + bitmap_height + 5);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbWhite);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(KRgbBlack);
	gc.DrawRect(canvas);

	gc.BitBltMasked(TPoint(x_coord, y_coord), iBitmap, rect, iMask, 0);

	gc.SetPenColor(textColor);

	const CFont *font;
	TFileName buff;
	TInt width = Rect().Width();
	font = CEikonEnv::Static()->TitleFont();
	gc.UseFont(font);
	TFileName buff_format;
	CEikonEnv::Static()->ReadResource(buff_format, R_PROGRAM_NAME);

	buff.Format(buff_format, VER_MAJOR, VER_MINOR);

	TInt top = font->HeightInPixels() + bitmap_height + 25;
	DrawStringCentered(font, buff, top, width, gc);
	gc.DiscardFont();

	font = CEikonEnv::Static()->DenseFont();
	gc.UseFont(font);

	CEikonEnv::Static()->ReadResource(buff, R_PUBLISHER_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_AUTOR_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_COPYRIGHT_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_SUPPORT_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_EMAIL_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);
	gc.DiscardFont();
}


