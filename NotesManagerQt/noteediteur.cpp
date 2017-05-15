#include "noteediteur.h"

ArticleEditeur::ArticleEditeur(Article &a, QWidget *parent) : QWidget(parent),article(&a)
{
    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    text=new QTextEdit(this);
    idlabel=new QLabel("identificateur",this);
    titrelabel=new QLabel("titre",this);
    textlabel=new QLabel("text",this);
    sauver=new QPushButton("Sauver",this);
    quitter=new QPushButton("Quitter",this);
    cid=new QHBoxLayout;
    cid->addWidget(idlabel);
    cid->addWidget(id);
    ctitre=new QHBoxLayout;
    ctitre->addWidget(titrelabel);
    ctitre->addWidget(titre);
    ctext=new QHBoxLayout;
    ctext->addWidget(textlabel);
    ctext->addWidget(text);
    ccouche=new QVBoxLayout;
    ccouche->addLayout(cid);
    ccouche->addLayout(ctitre);
    ccouche->addLayout(ctext);
    ccouche->addWidget(sauver);
    ccouche->addWidget(quitter);
    id->setText(article->getId());
    titre->setText(article->getTitle());
    text->setText(article->getText());
    id->setDisabled(true);
    setLayout(ccouche);
 
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(titre,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(text,SIGNAL(textChanged()),this,SLOT(activerSauver()));
    //QObject::connect(quitter,SIGNAL(clicked()),this,SLOT(closeArticle()));



    sauver->setDisabled(true);
    //quitter->setDisabled(true);
}
/*void closeArticle(){
    if(quitter->setEnabled==true){
        QMessageBox::information(this,"Voulez vous sauvegarder","Article sauvegardé !");
    }
}*/
void ArticleEditeur::saveArticle(){
    article->setTitle(titre->text());
    article->setText(text->toPlainText());
    QMessageBox::information(this,"Sauvegarder","Article sauvegardé !");
    sauver->setDisabled(true);
}

void ArticleEditeur::activerSauver(QString str){
    sauver->setEnabled(true);
    quitter->setEnabled(true);
}
