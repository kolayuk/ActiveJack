/*============================================================================
 Name        : CAboutView from AboutView.h
 Author	  	 : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version	 : 1.0
 Copyright   : 2010
 Description : Declares view for application.
============================================================================*/
#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

//SYSTEM INCLUDES
#include <aknview.h>
#include <eikmenup.h>

//USER INCLUDES
// CONSTANTS
// FORWARD DECLARATIONS
class CAboutContainer;

// CLASS DECLARATION
class CAboutView : public CAknView
{
public:
	static CAboutView* NewL();
	static CAboutView* NewLC();
	~CAboutView();

public:
	CAboutView();
	void ConstructL();
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleClientRectChange();

private:
	void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();

private: // Data
	CAboutContainer* iContainer;
};
#endif
