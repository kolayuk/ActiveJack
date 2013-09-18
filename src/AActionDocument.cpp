/*
========================================================================
 Name        : AActionDocument.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "AActionDocument.h"
#include "AActionAppUi.h"
// ]]] end generated region [Generated User Includes]
#include <apgwgnam.h>
/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CAActionDocument::CAActionDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CAActionDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CAActionDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CAActionDocument
 */
CAActionDocument* CAActionDocument::NewL( CEikApplication& aApp )
	{
	CAActionDocument* self = new ( ELeave ) CAActionDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CAActionDocument::CreateAppUiL()
	{
	return new ( ELeave ) CAActionAppUi;
	}
void CAActionDocument::UpdateTaskNameL(CApaWindowGroupName* aWg)
	{
	CAknDocument::UpdateTaskNameL(aWg);
#ifndef _DEBUG
	aWg->SetHidden(ETrue);
	aWg->SetSystem(ETrue);
#endif
	}
