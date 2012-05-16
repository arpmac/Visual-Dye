//---------------------------------------------------------------------------
// mod. 054
#include <vcl.h>
#pragma hdrstop

#include <iniFiles.hpp>

#include "SynopticF.h"
#include "KeyboardF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

extern String FLanguage;

TKeyboard *Keyboard;
//---------------------------------------------------------------------------

__fastcall TKeyboard::TKeyboard(TComponent* Owner)
	: TForm(Owner)
{
    Caption = Synoptic_1->UniGetMsg(trKeyboard,FLanguage);
    EraseAllBtn->Caption = Synoptic_1->UniGetMsg(trEraseAll,FLanguage);
}
//---------------------------------------------------------------------------

void __fastcall TKeyboard::SpeedButton1Click(TObject *Sender){

    if (Editor->Text.Length() >= Editor->MaxLength)
  	    return;

 	Editor->Text =
        Editor->Text + String(((TSpeedButton*)Sender)->Caption).LowerCase();
}
//---------------------------------------------------------------------------

void __fastcall TKeyboard::SpeedButton48Click(TObject *Sender){
	int j;

 	if ((j = Editor->Text.Length()) < 1)
  	    return;
        
 	Editor->Text = Editor->Text.SetLength(j-1);
}
//---------------------------------------------------------------------------

void __fastcall TKeyboard::EraseAllBtnClick(TObject *Sender){

	Editor->Text = "";
}
//---------------------------------------------------------------------------

bool TKeyboard::CheckPassword(void)
{
    TIniFile *ini = new TIniFile(ExtractFilePath(Application->ExeName) + "\\Local.ini");
    String PasswordText = ini->ReadString("Config","Password","obem");
    delete ini;

    Editor->MaxLength = PWD_LENGHT;
    Caption = Synoptic_1->UniGetMsg(trInsertPwd,FLanguage);
    Editor->PasswordChar = '*';
    Position = poScreenCenter;
    ShowModal();

    if (Editor->Text == PasswordText)
        return true;
    else
        return false;
}
//----------------------------------------------------------------------------

