#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H
#include <QTableWidget>
#include <QKeyEvent>
#include <QModelIndex>
//#include "regcashmain.h"

class customTable:public QTableWidget
{
   Q_OBJECT
   private:
    float prezzo;
   public:
      customTable(QWidget* parent=0):QTableWidget(parent){}
   protected:
      void keyPressEvent(QKeyEvent *e)
      {
         if(e->key()==Qt::Key_Backspace)
         {
            //qInfo("hai premuto backspace");
            //QTableWidget.SelectRows();
            //QTableWidget::removeRow(QTableWidget::SelectedClicked);
            //float prezzo = QTableWidget.model()->data(QTableWidget.model()->index(0,4)).toFloat();
            QModelIndexList indexes = QTableWidget::selectionModel()->selection().indexes();


            QModelIndex index = indexes.at(0);
            prezzo=this->item(index.row(),4)->text().toFloat();
                //qint16 riga=;

            QTableWidget::removeRow(index.row());
            //connect(QTableWidget,SIGNAL(backSpacePressed(float)),this,SLOT(test()));

            emit backSpacePressed(prezzo);

         }
         else { QTableWidget::keyPressEvent(e); }
      }
   signals:
       void backSpacePressed(float);
};


#endif // CUSTOMTABLE_H
