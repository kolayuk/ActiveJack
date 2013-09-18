/*
========================================================================
 Name        : AActionDocument.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef AACTIONDOCUMENT_H
#define AACTIONDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CAActionDocument AActionDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CAActionDocument : public CAknDocument
	{
public: 
	// constructor
	static CAActionDocument* NewL( CEikApplication& aApp );
	void UpdateTaskNameL(CApaWindowGroupName* aWg);
private: 
	// constructors
	CAActionDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // AACTIONDOCUMENT_H
