#include "notes.h"
#include "notemanager.h"
#include "fenetrenewnote.h"
#include "fenetreprincipale.h"
#include "editeurnote.h"
#include "editeurnotefactory.h"

FenPrincipale::FenPHandler FenPrincipale::fenP_handler=FenPHandler();

FenPrincipale& FenPrincipale::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!fenP_handler.instance) {
    fenP_handler.instance=new FenPrincipale;
  }
  // Retour par ref vers l'instance unique
  return *fenP_handler.instance;
}

void FenPrincipale::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete fenP_handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  fenP_handler.instance=0;
}


FenPrincipale::FenPrincipale()
{
    NotesManager& m=NotesManager::recupererInstance();
    setWindowTitle("PluriNotes");

// ************ Bar des Taches **********

    menuFichier = menuBar()->addMenu("&Fichier");
    menuNote = menuBar()->addMenu("&Note");
    menuNouveau = menuNote->addMenu("&Nouveau");

    actionQuitter = new QAction("&Quitter", this);
    ajouterArticle = new QAction("&Article",this);
    ajouterTache = new QAction("&Tache",this);
    ajouterNoteFichier = new QAction("&NoteFichier",this);

    menuFichier->addAction(actionQuitter);
    menuNouveau->addAction(ajouterArticle);
    menuNouveau->addAction(ajouterTache);
    menuNouveau->addAction(ajouterNoteFichier);

    QObject::connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));

    QObject::connect(ajouterArticle, SIGNAL(triggered()), this, SLOT(afficherNewArticle()));
    QObject::connect(ajouterTache, SIGNAL(triggered()), this, SLOT(afficherNewTache()));
    QObject::connect(ajouterNoteFichier, SIGNAL(triggered()), this, SLOT(afficherNewNoteFichier()));


//  ************ Zone Gauche **********

    dockNote = new QDockWidget(tr("Liste de Notes"));
    dockNote->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // --- Liste de l'ensemble des notes

    listeNote = new QListWidget(dockNote);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        listeNote->addItem(str);
    }
    dockNote->setWidget(listeNote);
    addDockWidget(Qt::LeftDockWidgetArea, dockNote);

    // --- Liste des taches

    dockTache = new QDockWidget(tr("Todo List"));
    dockTache->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeTache = new QListWidget(dockTache);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        if (typeid(it.current()).name()=="tache"){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        listeNote->addItem(str);}
    }
    dockTache->setWidget(listeTache);
    addDockWidget(Qt::LeftDockWidgetArea, dockTache);

    // --- Liste des archives

    dockArchive = new QDockWidget(tr("Notes Archivées"));
    dockArchive->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeArchive = new QListWidget(dockArchive);
    dockArchive->setWidget(listeArchive);
    addDockWidget(Qt::LeftDockWidgetArea, dockArchive);

    // -- Liste des versions

    listeVersion = new QComboBox();
    listeVersion->addItem(tr("Afrique"));
    listeVersion->addItem(tr("Amerique du Nord"));
    
    QObject::connect(listeNote, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(afficheNote(QListWidgetItem*)));


//  **********  Zone Centrale *********** 

    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);
    //ccentral = new QGridLayout;
    //zoneCentrale->setLayout(ccentral);
}

void FenPrincipale::afficheNote(QListWidgetItem* item){
    QString titre=item->text();
    if (titre.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Il n'y a pas de notes à afficher");
        msgBox.exec();
    }
    else{
        NotesManager& m=NotesManager::recupererInstance();
        NotesManager::Iterator it=m.getIterator();
        while(!it.isDone() && it.current().getTitre()!=titre){
            it.next();
        }
        if(!it.isDone()){
            qDebug()<<titre<<"\n";
            qDebug()<<it.current().getType()<<"\n";
            EditeurFactory* ef = EditeurFactory::chooseEditeur(it.current().getType());
            Notes* n(it.current().clone());
            EditeurNote* en = ef->createEditeur(n);
            //EditeurNote* en= new EditeurNote(it.current().getType(),titre,this);
            editnote=en;
            setCentralWidget(editnote);
            editnote->show();
        }
     }
}

void FenPrincipale::afficherNewArticle() {
      FenetreNewNote* fe = new FenetreNewNote("article",this);
      fenNewNote = fe;
      setCentralWidget(fenNewNote);
      fenNewNote->show();
}

void FenPrincipale::afficherNewTache() {
      FenetreNewNote* fe = new FenetreNewNote("tache",this);
      fenNewNote = fe;
      setCentralWidget(fenNewNote);
      fenNewNote->show();
}

void FenPrincipale::afficherNewNoteFichier() {
      FenetreNewNote* fe = new FenetreNewNote("noteFichier",this);
      fenNewNote = fe;
      setCentralWidget(fenNewNote);
      fenNewNote->show();
}

void FenPrincipale::actualiserNote() {
    NotesManager& m=NotesManager::recupererInstance();
    listeNote->clear();
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        QString str=it.current().getTitre();
        listeNote->addItem(str);
    }
}

/*void FenPrincipale::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "(*.xml)");
    //load(fichier);
}*/
