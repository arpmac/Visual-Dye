//---------------------------------------------------------------------------
/**************************** CHANGES HISTORY *********************************/
/* mod. dll_001, 24/01/2005, E. Campra                                        */
/* descrizione: sinottico macchina variabile a seconda di machine_type FIXME  */
/* mod. dll_002, 14/05/2012, E. Campra                                        */
/* descrizione: sinottico macchina variabile a seconda di machine_type FIXME  */
/* mod. dll_003, 14/05/2012, E. Campra                                        */
/* descrizione: sinottico macchina variabile a seconda di machine_type FIXME  */
/******************************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <iniFiles.hpp>

#include <map>
using namespace std;
#include "DataModF.h"
#include "SynopticF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
char dll_release[] = "1.5"; // mod. 006
String FLanguage;
TDataMod *DataMod;
sObemFunz PrgFunctions[NUM_MAX_FUN];
#define ALARM_TABLE_SIZE 41
 // commentato vecchia tabella allarmi
//char ALARM_TABLE[ALARM_TABLE_SIZE][80];
map<UINT,WideString> ALARM_TABLE;
map<UINT,WideString> WARNING_TABLE; // mod. 066

sObemFunz PrgFunctions_ENG[NUM_MAX_FUN]={
/* Le descrizioni devono essere almeno 1 carattere + corte dello spazio riservato */
/* Il save_funz_code deve essere univoco! */
  /* 1.abil
     | 2.comment
     | | 3.temp_ptr
     | | | 4.time_ptr
     | | | | 5.multiple_jump: indica il ptr al parametro tempo nelle funzioni mul_jump
     | | | | | 6.mj_abil
     | | | | | | 7.mj_fun
     | | | | | | | 8.mj_new_temp
     | | | | | | | | 9.plc_funz_code
     | | | | | | | | |            10.save_funz_code */
     {1,0,0,0,0,0,0,0,41,2,"SELECTION WATER"
 /*
 px_enabled
 | px_default
 | |
*/
,0,1,"Eau (1-V7 2-V13) ",2,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},



     {1,0,2,0,0,0,0,0,FUN_MAC_FILL,1,"FILLING MACHINE"
,1,2,"Water type       (1=cold / 2=hot)",2,1
,1,10,"End temperature             [°C]",140,10
,1,0,"Termic control          (0=N,1=Y)",1,0
,1,0,"Waiting                     (sec)",999,0
,0,0,"Level ",0,0
,1,0,"Speed main pump",100,0},




    {1,2,0,0,0,0,0,0,FUN_SAMPLING,3,"SAMPLING"
,0,0,"",0,0
,1,1,"Comment                   (1/999)",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* N.B. Nello scarico setto il temp_ptr ad un valore che so essere 0 */

    {1,0,2,0,0,0,0,0,FUN_DRAIN,4,"DRAIN"
,1,1,"Type (1 - 2 - 3 - 4 HT)",4,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {1,0,0,0,0,0,0,0,52,14,"DRAIN EXP TANK"
,1,1,"type ( 1-2-3)",3,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {1,0,0,0,1,0,0,0, 8,5,"BY PASS RECY-CLE"
,1,1,"Time                      [min]",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {1,0,1,2,0,0,0,0,FUN_TEMP_CTRL,6,"TEMPERATURE CONTROL"
,1,10,"End temperature              [°C]",140,10    //->V codice def!
,1,1,"Gradient             [°Cx100/min]",999,1
,1,0,"Maintenance                 [min]",999,0
,0,90,"End temperature by pass[°C]      ",90,5
,0,0,"",0,0
,0,0,"",0,0},

    {1,6,0,0,0,0,0,0,36,33,"CHEK pH"
,1,7,"Set pH x10    ",140,10
,1,0,"Gap pH x10    ",20,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,1,0,"Comment",999,1},

    {1,6,0,0,0,0,0,0,37,7,"ADD SODA OR SALT"
,1,1,"Soda [1] Salt[2]",2,1
,1,100,"Speed pump Est\Int",100,40
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,1,0,"Comment"             ,999,1			},

    {1,6,0,2,0,0,0,0,43,8,"pH ACID"
,1,7,"Value of pH x10",140,10
,1,0,"Time to catch the value[min]",90,1
,1,0,"Value of pH error x10",15,1
,0,0,"",0,0
,0,0, "",0,0
,1,1,"Comment",999,1},

    {1,6,0,2,0,0,0,0,42,9,"pH BASIC"
,1,7,"Value of pH x10",140,10
,1,0,"Time to reach value[min]",90,1
,1,0,"Value of pH error x10",15,1
,0,0,"",0,0
,0,0,"",0,0
,1,1,"Comment",999,1},
    {1,0,0,0,0,0,0,0,44,28,"RINSING pH PROBE"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0   },

    {1,0,5,3,0,0,0,0,FN_TIME_RINSE,10,"WASHING"
,0,0,"",0,0
,1,0,"Stop pump                (0=N/1=Y)",1,0
,1,0,"Time                         [min]",999,0
,1,60,"Speed pump              [40-100%]",100,40
,0,0, "",0,0
,0,0,"" ,0,0},





    {1,0,0,0,0,0,0,0,11,11,"SPEED PUMP"
,1,0,"Time Rotazion I/O           [sec]",9999,0
,1,0,"Time Rotazion O/I           [sec]",9999,0
,1,0,"Speed I/O                [0-100%]",100,0
,1,0,"Speed O/I                [0-100%]",100,0
,0,0,"Delta_P I/O                [m*10]",200,0
,0,0,"Delta_P O/I                [m*10]",200,0},



    {1,0,0,1,0,0,0,0,53,12,"ONLY CIRCULATION PUMP"
,1,1,"Time                      [min]",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* Funzioni della cucina colori */

    {1,6,0,0,0,0,0,0,FUN_PRD_PREP,20,"CALLING PRODUCTS "
,1,1,"Tank (1-2)",2,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,1,1,"Comment                   (1-999)",999,1   },

{1,6,0,0,0,0,0,0,21,24,"CONTROL KITCHEN 1"
,0,1,"Tank                        (1/2)",2,1
,1,1,"Filling         (1=cold / 2=hot)" ,2,1
,1,1,"Set filling                   [%]",100,0
,1,0,"Time mixer                  [min]",999,0
,1,0,"Temperature                  [°C]",90,0
,1,1,"Comment                   (1-999)",999,1   },

    {0,0,0,0,0,0,0,0,30,27,"RE_CYCLE DYE "
,0,1,"Tank                   (1/3)",3,1
,0,0,"",3,1
,0,0,"",999,1
,0,0,"",999,0
,0,0,"",0,0
,0,0,"Commento                  (1-999)",999,1   },

   {1,0,0,0,0,0,0,0,26,21,"RINSING AFTER TRANSFERT CC1"
,1,1,"Sort of water",2,1
,1,1,"Number of rinsing toward machine",2,1
,1,0,"Number of rinsing toward sewer",2,1
,1,0,"Level [%]",100,10
,1,0,"Temper. rinsing toward machine[C°]",80,0
,1,0,"Temperature rinsing toward sewer",80,0},



    {1,6,0,0,0,0,0,0,FUN_PRD_TRASF,25,"TRANSFERT DYE"
,1,1,"Tank (1/2)",2,1
,0,0,"",0,0
,1,1,"1=Machine / 2=P.Tank",2,1
,1,0,"Time                       [min]",999,0
,1,5,"Type 1lin/3-5-7 Exp. >10 Custom",100,0
,1,1,"Comment                  (1/999)",999,1   },



    {0,0,0,0,0,0,0,0,29,22,"RICYCLE MACHINE"
,0,1,"Tank                        (1/2)",2,1
,1,0,"Max level",100,10
,1,0,"Minimun level",100,10
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    


    {1,0,0,0,0,0,0,0,31,26,"RINSING KITCHEN TOWARD SEWER"
,1,1,"Tank (1/2)",2,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* Funzioni per i dosaggi automatici */

    {0,0,0,0,0,0,0,0,REQ_VE,50,"RICH. PRODOTTI V.ESP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {0,0,0,0,0,0,0,0,TRANSF_VE,51,"TRASF. PRODOTTI V.ESP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {0,0,0,0,0,0,0,0,TRANSF_VP,61,"TRASF PRODOTTI V.PREP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* Vaso d'espansione */

    {0,0,0,1,0,0,0,0,62,13,"SOAK"
,1,1,"Time         [min]",90,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},


/* VP */

    {1,0,0,0,0,0,0,0,PRP_TANK_FILL,40,"PREPARATION TANK CONTROL"
,1,1,"Water (1-V7 2-V13 3-V14 4-VA 5-VB) ",5,1
,1,10,"Temperature                 [°C]",90,10
,0,1,"Level                       (1/5)",5,1
,1,0,"Time Re-cycle               [min]",999,0
,0,0,"",0,0
,0,0,"",0,0},

    {1,0,0,0,0,0,0,0,39,23,"BRINE"
,1,10,"LITRES",400,10
,0,0," ",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},


    {0,0,0,0,0,0,0,0,REQ_VP,60,"RICH. PRODOTTI V.PREP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {1,0,0,0,0,0,0,0,15,41,"DRAIN PREPARATION TANK"
,1,0,"Type 1-2-3",3,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {1,0,3,0,0,0,0,0,TRANSF_VP,42,"DELIVERY"
,1,0,"Washing                 (0=N/1=Y)",1,0
,0,1,"Type water                  (1/2)",2,1
,0,0,"",0,0
,0,0,"Last level (1)/ whole liquor(2)",0,0
,1,0,"Drain type 1-2-3",3,1
,0,0,"",0,0},

    {1,0,0,0,0,0,0,0,17,43,"RECOVERY"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

    {0,2,0,0,0,0,0,0,FUN_SAMPLING,44,"BENESTARE VP"
,0,0,"",0,0
,1,0,"Commento                  (1/999)",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* ----------------------------FUNZIONI RISERVATE------------------------------- */
    {0,0,0,0,0,0,0,0,END_OF_PRG,31,"END CYCLE"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
    {0,0,0,0,0,0,0,0,29,32,"INDIRIZZO IP"
,1,0,"Primo ottetto          (0/255)",255,0
,1,0,"Secondo ottetto        (0/255)",255,0
,1,0,"Terzo ottetto          (0/255)",255,0
,1,0,"Quarto ottetto         (0/255)",255,0
,0,0,"",0,0
,0,0,"",0,0},
};

sObemFunz PrgFunctions_ITA[NUM_MAX_FUN]={
/* Le descrizioni devono essere almeno 1 carattere + corte dello spazio riservato */
/* Il save_funz_code deve essere univoco! */
/* 1.abil
   | 2.comment
   | | 3.temp_ptr
   | | | 4.time_ptr
   | | | | 5.multiple_jump: indica il ptr al parametro tempo nelle funzioni mul_jump
   | | | | | 6.mj_abil
   | | | | | | 7.mj_fun
   | | | | | | | 8.mj_new_temp
   | | | | | | | | 9.plc_funz_code
   | | | | | | | | |            10.save_funz_code*/
  {1,0,2,0,0,0,0,0,FUN_MAC_FILL,1,"RIEMPIMENTO MACCHINA"
/*
 px_enabled
 | px_default
 | |
*/
,1,1,"Tipo 1-2                    (1/2)",2,1
,1,10,"Temperatura finale           [°C]",140,10
,1,0,"Controllo termico       (0=N,1=S)",1,0
,1,0,"Attesa                      (sec)",999,0
,0,1,"Livello                     (1/8)",8,1
,0,0,"",0,0},

  {0,2,0,0,0,0,0,0,FUN_SAMPLING,2,"DISPONIBILE"
,0,0,"",0,0
,0,0,"",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,2,0,0,0,0,0,0,FUN_SAMPLING,3,"CAMPIONATURA"
,0,0,"",0,0
,1,1,"Commento                  (1/999)",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* N.B. Nello scarico setto il temp_ptr ad un valore che so essere 0 */

  {1,0,2,0,0,0,0,0,FUN_DRAIN,4,"SCARICO"
,1,1,"Tipo 1-2 (1 normale / 2 HT)",2,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {0,0,0,0,1,0,0,0, 8,5 ,"BY PASS RICIRCOLO"
,1,1,"Tempo                      [min]",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,1,2,0,0,0,0,FUN_TEMP_CTRL,6,"CONTROLLO TEMPERATURA"
,1,10,"Temperatura finale           [°C]",140,10    //->V codice def!
,1,1,"Gradiente            [°Cx100/min]",999,1
,1,0,"Mantenimento                [min]",999,0
,0,90,"End temperature by pass[°C]      ",90,5
,0,0,"",0,0
,0,0,"",0,0},

  {0,0,0,0,0,0,0,0,60,33,"CONTROLLO ph"
,1,7,"Valore ph+10",140,10
,1,0,"Errore ph*10",20,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,6,3,0,0,0,0,FN_TIME_RINSE,7,"LAVAGGIO A TEMPO"
,1,2,"Tipo acqua                  (1/2)",2,1
,1,0,"Stop pompe              (0=N/1=S)",1,0
,1,0,"Tempo                       [min]",999,0
,1,60,"Velocità pompa          [40-100%]",100,40
,0,0, "Temperature                  [C°]",90,10
,0,10,"Temperatura fittizia"             ,0,0},

  {0,0,6,0,0,0,0,0,FN_BATH_RINSE,8,"DISPONIBILE"
,0,0,"",3,1
,0,0,"",1,0
,0,0,"",50,1
,0,0,"",100,40
,0,0,"",0,0
,0,10,"",0,0},

  {1,0,3,0,0,0,0,0,FN_TEMP_RINSE,9,"LAVAGGIO A TEMPERATURA"
,1,1,"Tipo acqua                  (1/2)",2,1
,1,0,"Stop pompe              (0=N/1=S)",1,0
,1,10,"Temperatura finale           [°C]",140,10
,1,60,"Velocità pompa              100%]",100,40
,0,0, "Valore portata             [DL/M]",100,0
,0,0,"",0,0},

  {1,0,0,0,0,0,0,0,11,10,"CONTROLLO POMPA"
,1,0,"Tempo rotazione I/O         [sec]",9999,0
,1,0,"Tempo rotazione O/I         [sec]",9999,0
,1,0,"Velocità I/O             [0-100%]",100,0
,1,0,"Velocità O/I             [0-100%]",100,0
,0,0,"Delta_P I/O                [m*10]",200,0
,0,0,"Delta_P O/I                [m*10]",200,0},

  {0,0,0,0,0,0,0,0, 58,11,"DISPONIBILE"
,0,0,"",500,0
,0,0,"",500,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,0,1,0,0,0,0,53,12,"ROT. POMPA SENZA CONT. TEMP."
,1,1,"Tempo                       [min]",999,1
,0,0,"Fermo pompa             (0=N/1=S)",1,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* Funzioni della cucina colori */

  {1,6,0,0,4,0,0,0,FUN_PRD_PREP,20,"PREPARARA COLORE"
,0,1,"Barilotto                   (1/2)",2,1
,1,1,"Tipo acqua                  (1/2)",2,1
,1,1,"Set litri                     [L]",600,0
,1,0,"Tempo mixer                 [min]",999,0
,1,0,"Temperatura                  [°C]",90,0
,1,1,"Commento                  (1-999)",999,1   },

  {1,0,0,0,0,0,0,0,29,27          ,"RICIRCOLO COLORE "
,0,2,"Barilotto                   (1/3)",3,1
,0,0,"",3,1
,0,0,"",999,1
,0,0,"",999,0
,0,1,"1 colore 0 macchina",0,0
,0,0,"Commento                  (1-999)",999,1   },

  {0,6,0,0,4,0,0,0,FUN_PRD_PREP,28,"DISPONIBILE"
,0,0,"",3,1
,0,0,"",3,1
,0,0,"",999,1
,0,0,"",999,0
,0,0,"",90,0
,0,0,"",999,1   },

  {1,6,0,4,0,0,0,0,FUN_PRD_TRASF,21,"TRANSFERIMENTO COLORE"
,1,1,"Barilotto                   (1/2)",2,1
,0,1,"Acqua fredda                (1/2)",2,1
,0,1,"Macchina(1)-VP(2)           (1/2)",2,1
,1,0,"Tempo                       [min]",999,0
,1,5,"Tipo 0lin/ 3-5-7 Exp. >100 utente " ,100,0
,1,1,"Commento                 (1/999) ",999,1   },

  {0,6,0,4,0,0,0,0,FUN_PRD_TRASF,24,"DSPONIBILE"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0   },

  {1,0,0,0,0,0,0,0,29,22,"RICIRCOLO CON MACCHINA"
,0,2,"Barilotto                   (1/2)",2,1
,0,0,"",999,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"1 colore 0 macchina              ",0,0
,0,0,"",0,0},

  {0,2,0,0,0,0,0,0,FUN_SAMPLING,23,"DISPONIBILE"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {0,2,0,0,0,0,0,0,FUN_SAMPLING,25,"DISPONIBILE"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,0,0,0,0,0,0,31,26,"LAVAGGIO BARILOTTO"
,0,1,"Barilotto                   (1/2)",3,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

/* Funzioni per i dosaggi automatici */

{0,0,0,0,0,0,0,0,REQ_VE,50,"RICH. PRODOTTI V.ESP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {0,0,0,0,0,0,0,0,TRANSF_VE,51,"TRASF. PRODOTTI V.ESP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {0,0,0,0,0,0,0,0,TRANSF_VP,61,"TRASF PRODOTTI V.PREP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* Vaso d'espansione */

  {0,0,0,1,0,0,0,0,62,13,"IMBIBENZA"
,1,1,"Time         [min]",90,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {0,0,0,0,1,0,0,0,30,14,"MIXER VASO ESPANSIONE"
,1,1,"Time                       [min]",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* VP */

  {1,0,0,0,0,0,0,0,PRP_TANK_FILL,40,"PREPARA VASCA PREP."
,0,1,"Tiipo acqua                  (1/2)",2,1
,1,10,"Temperatura                  [°C]",90,10
,0,1,"Litri                            ",500,10
,1,0,"Tempo ricircolo             [min]",999,0
,1,0,"Tempo mixer                 [min]",999,0
,0,0,"",0,0},

  {0,0,0,0,0,0,0,0,REQ_VP,60,"RICH. PRODOTTI V.PREP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,0,0,0,0,0,0,15,41,"SCARICO VASCA PREP."
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,3,0,0,0,0,0,TRANSF_VP,42,"MANDATA"
,1,0,"Lavaggio                (0=N/1=Y)",1,0
,0,1,"Tipo acqua                  (1/2)",2,1
,1,10,"Temperatura                      ",90,10
,0,0,""                                 ,1,0
,0,0,"",0,0
,0,0,"",0,0},

  {1,0,0,0,0,0,0,0,17,43,"RECUPERO"
,0,0,"",1,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},

  {0,2,0,0,0,0,0,0,FUN_SAMPLING,44,"BENESTARE VP"
,0,0,"",0,0
,1,0,"Commento                  (1/999)",999,1
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
/* ----------------------------FUNZIONI RISERVATE------------------------------- */
  {0,0,0,0,0,0,0,0,END_OF_PRG,31,"END CYCLE"
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0
,0,0,"",0,0},
  {0,0,0,0,0,0,0,0,29,32,"INDIRIZZO IP"
,1,0,"Primo ottetto          (0/255)",255,0
,1,0,"Secondo ottetto        (0/255)",255,0
,1,0,"Terzo ottetto          (0/255)",255,0
,1,0,"Quarto ottetto         (0/255)",255,0
,0,0,"",0,0
,0,0,"",0,0},
};


char ALARM_TABLE_ENG[ALARM_TABLE_SIZE][80] = {
 /* 0*/     "",
 /* 1*/	   "Alarm STOP pressed",
 /* 2*/	   "Alarm safety devices",
 /* 3*/	   "Alarm thermic main pump",
 /* 4*/	   "Alarm thermic static pump",
 /* 5*/	   "Alarm thermic prep.tank pump",
 /* 6*/	   "Alarm thermic INVERTER",
 /* 7*/	   "Alarm reduce load exact pos.",
 /* 8*/	   "Alarm thermic parallel pump",
 /* 9*/	   "Alarm thermic tansf.pump dye kitchen",
 /*10*/	   "Alarm thermic mixer TANK 1",
 /*11*/	   "Allarme termico mixer cucina 2",
 /*12*/	   "Alarm probe PT100 vessel",
 /*13*/	   "Alarm probe PT100 preparation tank",
 /*14*/	   "Alarm probe PT100 dey kitchen 1",
 /*15*/	   "Alarm probe PT100 dey kitchen 2",
 /*16*/	   "Alarm probe PT100 drain H.T.",
 /*17*/	   "Comunication error pc-plc",
 /*18*/	   "EMERGENCY push button",
 /*19*/	   "Alarm probe PT100 dey kitchen 3",
 /*20*/	   "Alarm parallel valves position",
 /*21*/	   "",
 /*22*/	   "",
 /*23*/	   "",
 /*24*/	   "",
 /*25*/	   "Allarme mixer vaso espansione",
 /*26*/	   "Allarme mixer cucina 3",
 /*27*/	   "Advice add soda",
 /*28*/	   "",
 /*29*/	   "Advice add salt",
 /*30*/	   "Allarme temperatura bassa per scarico alta temperatura",
 /*31*/	   "Allarme temperatura vaso espansione",
 /*32*/	   "",
 /*33*/	   "",
 /*34*/	   "",
 /*35*/	   "Alarm not correct posizion pump circ.",
 /*36*/	   "Alarm no correct position V51",
 /*37*/	   "",
 /*38*/	   "Alarm pH low",
 /*39*/	   "Allarm pH high",
 /*40*/	   ""
 };

char ALARM_TABLE_ITA[ALARM_TABLE_SIZE][80] = {
/* 0*/     "",
/* 1*/	   "Allarme STOP premuto",
/* 2*/	   "Allarme dispositivi sicurezza",
/* 3*/	   "Allarme termico pompa principale",
/* 4*/	   "Allarme termico pompa statica",
/* 5*/	   "Allarme termico vasca di preparazione",
/* 6*/	   "Allarme termico INVERTER",
/* 7*/	   "Allarme movimento bracci",
/* 8*/	   "Allarme termico pompa parallelo",
/* 9*/	   "Allarme termico pompa trasf. cucina",
/*10*/	   "Allarme termico mixer cucina 1",
/*11*/	   "Allarme termico mixer cucina 2",
/*12*/	   "Allarme sonda PT100 macchina",
/*13*/	   "Allarme PT100 vasca preparazione",
/*14*/	   "Allarme PT100 cucina colori 1",
/*15*/	   "Allarme PT100 cucina colori 2",
/*16*/	   "Allarme mancata lettura stop sensore bracci",
/*17*/	   "Allarme comunicazione PC-PLC",
/*18*/	   "Emergenza",
/*19*/	   "Allarme PT100 cucina colori 3",
/*20*/	   "Allarme valvole parallelo",
/*21*/	   "Allarme sensore DP interno/esterno",
/*22*/	   "Allarme sensore DP esterno/interno",
/*23*/	   "Allarme livello trasferimento cucina colori",
/*24*/	   "Allarme livello alto in macchina",
/*25*/	   "Allarme mixer vaso espansione",
/*26*/	   "Allarme mixer cucina 3",
/*27*/	   "Allarme PT100 acqua miscelata",
/*28*/	   "Allarme generico",
/*29*/	   "Allarme generico",
/*30*/	   "Allarme temperatura bassa per scarico alta temperatura",
/*31*/	   "Allarme pH basso",
/*32*/	   "Allarme pH alto",
/*33*/	   "Allarme generico",
/*34*/	   "Allarme generico",
/*35*/	   "Allarme generico",
/*36*/	   "Allarme centralina olio",
/*37*/	   "Errata posizione cesto/n aprire coperchio per reset",
/*38*/	   "Alarm perso livello max macchina ",
/*39*/	   "Allarme no segnale da contalitri",
/*40*/	   "Alarm troppa differenza tra i livelli"
};
//---------------------------------------------------------------------------

__fastcall TDataMod::TDataMod(TComponent* Owner)
	: TDataModule(Owner){

    TIniFile *ini = new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
    FLanguage = ini->ReadString("Config","Language","ITA");

    if (FLanguage == "ENG"){
        memcpy((void *)PrgFunctions,(void *)PrgFunctions_ENG,sizeof(sObemFunz)*NUM_MAX_FUN);
       // memcpy((void *)ALARM_TABLE,(void *)ALARM_TABLE_ENG,sizeof ALARM_TABLE);
    } else if (FLanguage == "ITA"){
        memcpy((void *)PrgFunctions,(void *)PrgFunctions_ITA,sizeof(sObemFunz)*NUM_MAX_FUN);
       // memcpy((void *)ALARM_TABLE,(void *)ALARM_TABLE_ITA,sizeof ALARM_TABLE);
    } else if (FLanguage == "FRE"){
        memcpy((void *)PrgFunctions,(void *)PrgFunctions_FRE,sizeof(sObemFunz)*NUM_MAX_FUN);
       // memcpy((void *)ALARM_TABLE,(void *)ALARM_TABLE_FRE,sizeof ALARM_TABLE);
    }
/*
      else if (FLanguage == "RUS"){
        memcpy((void *)PrgFunctions,(void *)PrgFunctions_RUS,sizeof(sObemFunz)*NUM_MAX_FUN);
       // memcpy((void *)ALARM_TABLE,(void *)ALARM_TABLE_RUS,sizeof ALARM_TABLE);
    }
*/

    // the ALARM_TABLE
	Synoptic_1->ADOQuery1->SQL->Clear();
	Synoptic_1->ADOQuery1->SQL->Add("select * from AlarmDescr order by alarm_id ASC");
	Synoptic_1->ADOQuery1->Open();

    ALARM_TABLE.clear();
	for (Synoptic_1->ADOQuery1->First(); !Synoptic_1->ADOQuery1->Eof; Synoptic_1->ADOQuery1->Next()){
		ALARM_TABLE.insert(make_pair(Synoptic_1->ADOQuery1->FieldByName("alarm_id")->AsInteger,
									 Synoptic_1->ADOQuery1->FieldByName(FLanguage)->AsString));
	}

    // the WARNING_TABLE, mod. 066
	Synoptic_1->ADOQuery1->SQL->Clear();
	Synoptic_1->ADOQuery1->SQL->Add("select * from WarningDescr order by id ASC");
	Synoptic_1->ADOQuery1->Open();

    WARNING_TABLE.clear();
	for (Synoptic_1->ADOQuery1->First(); !Synoptic_1->ADOQuery1->Eof; Synoptic_1->ADOQuery1->Next()){
		WARNING_TABLE.insert(make_pair(Synoptic_1->ADOQuery1->FieldByName("id")->AsInteger,
									 Synoptic_1->ADOQuery1->FieldByName(FLanguage)->AsString));
	}
}
//---------------------------------------------------------------------------

void TDataMod::UpdateBmpCheck(TImage *MyImage,TImageList* ListOfImages,int val){
 	Graphics::TBitmap *Bitmap;

 	if ((*MyImage).Tag/10000 == val)
  	    return;

    // save man cmd val
    int tmp = MyImage->Tag%10000;

 	MyImage->Tag = tmp + val*10000;
    
    Bitmap = new Graphics::TBitmap();
 	(*ListOfImages).GetBitmap(val,Bitmap);
 	(*MyImage).Picture->Graphic=Bitmap;
 	delete Bitmap;
}
//----------------------------------------------------------------------------

// char* TDataMod::GetAlarmMsg(int alarm_code)
WideString TDataMod::GetAlarmMsg(UINT alarm_code)
{
    if (ALARM_TABLE.find(alarm_code) != ALARM_TABLE.end())
        return ALARM_TABLE[alarm_code];
    else
        return ALARM_TABLE[0];
}
//----------------------------------------------------------------------------
 // commentato vecchia funzione  GetAlarmMsg
/*
char* TDataMod::GetAlarmMsg(int alarm_code)
{
    if (alarm_code < 0)
        alarm_code = 0;

    return ALARM_TABLE[alarm_code%ALARM_TABLE_SIZE];
}

*/
//----------------------------------------------------------------------------

char* TDataMod::GetReleaseNbr(void) // mod. 006
{
  return dll_release;
}
//----------------------------------------------------------------------------

WideString TDataMod::GetWarningMsg(UINT id) // mod. 066
{
    if (WARNING_TABLE.find(id) != WARNING_TABLE.end())
        return WARNING_TABLE[id];
    else
        return WARNING_TABLE[0];
}
//----------------------------------------------------------------------------

