#ifndef AZIONI_H
#define AZIONI_H

const int NO_ACTION = -1;


//Form Articoli
//-------------
const int INSERIMENTO_ARTICOLO=1;
const int MODIFICA_ARTICOLO=2;

//Lista Report
//------------
const int REPORT_LISTA_ARTICOLI=0;
const int REPORT_ARTICOLI_NO_GIACENZA=1;
const int REPORT_ARTICOLI_VENDUTI=2;
const int REPORT_ARTICOLI_PIU_VENDUTI=3;
const int REPORT_ARTICOLI_PIU_PROFITTO=4;


//WebService
//----------
const QString FULL_PRODUCTS="fullproduct";  //Get list of all product
const QString RECV_STOCK_PRODUCTS="";       //Recv stock of all product from the Shop On LIne
const QString SEND_STOCK_PRODUCT="";        //Send stock of all product to the Shop On line
const QString DECREASE_PRODUCT="";          //Decrease 1 qty of product from the Shop On Line
const QString INCREASE_PRODUCT="";          //Increase 1 qty of product in the Shop On Line

#endif // AZIONI_H
