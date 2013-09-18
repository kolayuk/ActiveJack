/*============================================================================
 Name        : CAboutView from AboutView.h
 Author	  	 : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version	 : 1.0
 Copyright   : 2010
 Description : CAboutView implementation
 ============================================================================*/
//SYSTEM INCLUDES
#include <aknviewappui.h>
#include <avkon.hrh>

//USER INCUDES
#include "AboutView.h"
#include "AboutContainer.h"
#include "Constants.h"
#include RSG_FILE

CAboutView* CAboutView::NewL()
{
	CAboutView* self = CAboutView::NewLC();
	CleanupStack::Pop(self);
	return self;
}

CAboutView* CAboutView::NewLC()
{
	CAboutView* self = new (ELeave) CAboutView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CAboutView::CAboutView()
{
}

void CAboutView::ConstructL()
{
	BaseConstructL(R_ABOUT_VIEW);
}

CAboutView::~CAboutView()
{
}

TUid CAboutView::Id() const
{
	return KAboutViewId;
}

void CAboutView::HandleCommandL(TInt aCommand)
{
	switch (aCommand)
	{
		default:
		{
			AppUi()->HandleCommandL(aCommand);
			break;
		}
	}
}

void CAboutView::HandleClientRectChange()
{
	if (iContainer != NULL)
	{
		iContainer->SetRect(ClientRect());
	}
}

void CAboutView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
{
	iContainer = new (ELeave) CAboutContainer();
	iContainer->SetMopParent(this);
	iContainer->ConstructL(ClientRect());
	AppUi()->AddToStackL(*this, iContainer);
}

void CAboutView::DoDeactivate()
{
	AppUi()->RemoveFromViewStack(*this, iContainer);
	delete iContainer, iContainer = NULL;
}
