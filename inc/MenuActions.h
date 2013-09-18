/*
 ============================================================================
 Name		: MenuActions.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CMenuActions declaration
 ============================================================================
 */

#ifndef MENUACTIONS_H
#define MENUACTIONS_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <badesca.h>
// CLASS DECLARATION


struct TApplicationInfo
{
	TFileName iCaption;
	TUid iUid;
	static TInt Compare(const TApplicationInfo& aInfo1, const TApplicationInfo& aInfo2)
	{
		return aInfo1.iCaption.CompareC(aInfo2.iCaption);
	}
};

class CMenuActions : public CBase
	{
public:
	// Constructors and destructor
	~CMenuActions();
	static CMenuActions* NewL();
	static CMenuActions* NewLC();
	static void Hide();
	static void Exit();
	static void AddAction(TUid aView);
	static void  DelAction(TUid aView,TInt aIndex);
	static void  EditAction(TUid aView,TInt aIndex);
	static void Help();
	static void About();
	static void OtherProducts();
	static void OpenSetting();
	static TPtrC CreateText(TInt aPrefix,CDesC16Array* aArray);
private:
	CMenuActions();
	void ConstructL();
	static TInt ActionDialog(CDesCArray* aArr, TDes& aTitle);
	static TInt NumberQuery(TDes& aText,TInt& aNumber);
	static TUint32 ApplicationDialog(TDes& aTitle);
	static TInt CreateSetting(CDesCArray* Setting,TDes& aData);
	static TInt ProfileDialog();
	};

#endif // MENUACTIONS_H
