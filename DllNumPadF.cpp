//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DllNumPadF.h"
#include "DataModF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TNumPad *NumPad;
//---------------------------------------------------------------------------
__fastcall TNumPad::TNumPad(TComponent* Owner)
	: TForm(Owner){
	}
//---------------------------------------------------------------------------
__fastcall TNumPad::TNumPad(TComponent* Owner,short a,short b,short c)
	: TForm(Owner),operating_mode(a),funct_num(b),param_num(c){

  switch (operating_mode){
  	/* fall through! */
    case OM_INSERT_FUN:
    	SetCorrectParameterNumber();
		case OM_INSERT_STEP:
    	Caption=PrgFunctions[funct_num].Funct;
    	ShowParamDescr();
    }
  InputValueN->Text="";
	}
//---------------------------------------------------------------------------
/* Setta il valore esatto di param_num in base ai parametri abilitati */
void TNumPad::SetCorrectParameterNumber(void){
	switch (param_num){
  	/* !Fall trough! */
    case 0:
    	if(PrgFunctions[funct_num].p1_enabled){
      	param_num=1;
    		break;
        }
      else
        tmp_data_rep[0]=PrgFunctions[funct_num].p1_default;
    case 1:
    	if(PrgFunctions[funct_num].p2_enabled){
      	param_num=2;
    		break;
        }
      else
        tmp_data_rep[1]=PrgFunctions[funct_num].p2_default;
    case 2:
    	if(PrgFunctions[funct_num].p3_enabled){
      	param_num=3;
    		break;
        }
      else
        tmp_data_rep[2]=PrgFunctions[funct_num].p3_default;
    case 3:
    	if(PrgFunctions[funct_num].p4_enabled){
      	param_num=4;
    		break;
        }
      else
        tmp_data_rep[3]=PrgFunctions[funct_num].p4_default;
    case 4:
    	if(PrgFunctions[funct_num].p5_enabled){
      	param_num=5;
    		break;
        }
      else
        tmp_data_rep[4]=PrgFunctions[funct_num].p5_default;
    case 5:
    	if(PrgFunctions[funct_num].p6_enabled){
      	param_num=6;
    		break;
        }
      else
        tmp_data_rep[5]=PrgFunctions[funct_num].p6_default;
    case 6:
    	ModalResult=mrOk;
    }
  }
//---------------------------------------------------------------------------
void __fastcall TNumPad::InputValueConfClick(TObject *Sender){
  if(InputValueN->Text=="")
  	return;

  if(CheckForLimits(InputValueN->Text.ToInt(),param_num)){
  	InputValueN->Text="";
  	return;
    }
	switch (operating_mode){
    case OM_INSERT_FUN:
    	tmp_data_rep[param_num-1]=(short)InputValueN->Text.ToInt();
  		InputValueN->Text="";
      SetCorrectParameterNumber();
      ShowParamDescr();
    break;
    case OM_INSERT_STEP:
    case OM_CUSTOM_MODE:
      ModalResult=mrOk;
    break;
    }
  }
//---------------------------------------------------------------------------
bool TNumPad::CheckForLimits(int param_value, int param_num){

	if(operating_mode==OM_CUSTOM_MODE){
    if(param_value<lower_limit || param_value>upper_limit)
    	return true;
    return false;    
  	}

	switch (param_num){
    case 1:
    	if(param_value>PrgFunctions[funct_num].p1_max || param_value<PrgFunctions[funct_num].p1_min)
      	return true;
    break;
    case 2:
    	if(param_value>PrgFunctions[funct_num].p2_max || param_value<PrgFunctions[funct_num].p2_min)
      	return true;
    break;
    case 3:
    	if(param_value>PrgFunctions[funct_num].p3_max || param_value<PrgFunctions[funct_num].p3_min)
      	return true;
    break;
    case 4:
    	if(param_value>PrgFunctions[funct_num].p4_max || param_value<PrgFunctions[funct_num].p4_min)
      	return true;
    break;
    case 5:
    	if(param_value>PrgFunctions[funct_num].p5_max || param_value<PrgFunctions[funct_num].p5_min)
      	return true;
    break;
    case 6:
    	if(param_value>PrgFunctions[funct_num].p6_max || param_value<PrgFunctions[funct_num].p6_min)
      	return true;
    break;
    }
  return false;
  }
//---------------------------------------------------------------------------
void TNumPad::ShowParamDescr(void){
  String aux;
  
	switch(param_num){
  	case 1:
      aux=PrgFunctions[funct_num].p1_descript;
    break;
    case 2:
     	aux=PrgFunctions[funct_num].p2_descript;
    break;
    case 3:
     	aux=PrgFunctions[funct_num].p3_descript;
    break;
    case 4:
     	aux=PrgFunctions[funct_num].p4_descript;
    break;
    case 5:
     	aux=PrgFunctions[funct_num].p5_descript;
    break;
    case 6:
     	aux=PrgFunctions[funct_num].p6_descript;
    break;
    }
  ViewParamDescr->Caption=aux;
  }
//---------------------------------------------------------------------------
void __fastcall TNumPad::SpeedButton1Click(TObject *Sender){

	if(InputValueN->Text.Length()<4)
		InputValueN->Text=InputValueN->Text+((TSpeedButton*)Sender)->Tag;
	}
//---------------------------------------------------------------------------
void __fastcall TNumPad::SpeedButton11Click(TObject *Sender){
	int j;

 	if((j=InputValueN->Text.Length())<1)
  	return;
 	InputValueN->Text=InputValueN->Text.SetLength(j-1);
}
//---------------------------------------------------------------------------

