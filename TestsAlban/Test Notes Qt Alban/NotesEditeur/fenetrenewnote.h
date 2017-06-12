#ifndef FENETRENEWNOTE_H
#define FENETRENEWNOTE_H

#include <QtWidgets>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QFile>
#include <QLabel>
#include <QListWidget>
#include <QDockWidget>
#include <QMenu>
#include <QLineEdit>
#include <QListWidgetItem>
#include "notes.h"


class FenetreNewNote : public QWidget {
    Q_OBJECT
private:
    QLineEdit* typeEdit;
    // ---- Label -----
    QLabel* idlabel;
    QLabel* titrelabel;
    QLabel* textlabel;
    QLabel* descriptionlabel;
    QLabel* filelabel;
    QLabel* actionlabel;
    QLabel* prioritelabel;
    QLabel* dateEchlabel;
    QLabel* statutlabel;
    // ---- Edit ---- 
    QLineEdit* idEdit;
    QLineEdit* titreEdit;
    QTextEdit* textEdit;
    QTextEdit* descriptionEdit;
    QLineEdit* fileEdit;
    QLineEdit* actionEdit;
    QLineEdit* prioriteEdit;
    QLineEdit* dateEchEdit;
    QLineEdit* statutEdit;    
    // ---- Bouton ----
    QPushButton* valider;
    QPushButton* annuler;
    // --- Layout --- 
    QHBoxLayout* ctype;
    QHBoxLayout* cid;
    QHBoxLayout* ctitre;
    QHBoxLayout* ctext;
    QHBoxLayout* cdescription;
    QHBoxLayout* cfile;
    QHBoxLayout* caction;
    QHBoxLayout* cpriorite;
    QHBoxLayout* cdateEch;
    QHBoxLayout* cstatut;
    QHBoxLayout* cboutons;
    QVBoxLayout* zone;

public:
    FenetreNewNote(QString type, QWidget* parent=0);
    //QString getId() { return id->text(); }

public slots:
    //QString createNote(QString type);
    void creerNote();

};
#endif // FENETRENEWNOTE_H
