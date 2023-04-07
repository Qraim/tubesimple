//
// Created by qraim on 04/04/23.
//

#include "tubesimple.h"
#include <math.h>

tubesimple::tubesimple(QWidget *parent) : QWidget(parent)
{
    materiau.addItem("PVC");
    materiau.addItem("Polyéthylène");
    materiau.addItem("Fonte");
    materiau.addItem("Aluminium");


    // Créé la grille
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *titleLabel = new QLabel("Perte de charge en tube simple", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(titleLabel, 0, 0, 1, 5);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 1);

    // On ajoute les éléments à leur place dans la grille
    gridLayout->addWidget(new QLabel("Materiau", this), 1, 0);
    gridLayout->addWidget(&materiau, 2, 0);
    gridLayout->addWidget(new QLabel("Debit (m3/h)", this), 1, 1);
    debit.setFixedWidth(110);
    gridLayout->addWidget(&debit, 2, 1);
    gridLayout->addWidget(new QLabel("Diametre (mm)", this), 1, 2);
    diametre.setFixedWidth(120);
    gridLayout->addWidget(&diametre, 2, 2);
    gridLayout->addWidget(new QLabel("Longueur (m)", this), 1, 3);
    longueur.setFixedWidth(110);
    gridLayout->addWidget(&longueur, 2, 3);
    gridLayout->addWidget(new QLabel("Denivele (m)", this), 1, 4);
    denivele.setFixedWidth(110);
    gridLayout->addWidget(&denivele, 2, 4);

    // La derniere ligne pour les résultats
    QHBoxLayout *resultLabelsLayout = new QHBoxLayout;
    QLabel *perteLabel = new QLabel("Pertes de charge (m)", this);
    QLabel *piezoLabel = new QLabel("Variation Piezo (m)", this);
    QLabel *vitesseLabel = new QLabel("Vitesse (m/s)", this);
    resultLabelsLayout->addWidget(perteLabel);
    resultLabelsLayout->addWidget(piezoLabel);
    resultLabelsLayout->addWidget(vitesseLabel);


    QHBoxLayout *resultFieldsLayout = new QHBoxLayout;
    Perte.setReadOnly(true);
    Piezo.setReadOnly(true);
    Vitesse.setReadOnly(true);
    resultFieldsLayout->addWidget(&Perte);
    resultFieldsLayout->addWidget(&Piezo);
    resultFieldsLayout->addWidget(&Vitesse);

    // Ajoute des champs non écrivable
    QHBoxLayout *nonEditableFieldsLayout = new QHBoxLayout;

    // Ajoute le bouton Calculer
    Calcul.setText("Calculer");
    QHBoxLayout *calculerLayout = new QHBoxLayout;
    Calcul.setFixedSize(120, 30);
    calculerLayout->addStretch(1);
    calculerLayout->addWidget(&Calcul);
    calculerLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(calculerLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(resultLabelsLayout);
    mainLayout->addLayout(resultFieldsLayout);


    // Fixe l'interface globale
    setLayout(mainLayout);

    Calcul.setDisabled(true);
    debit.hasFocus();

    connect(&Calcul, &QPushButton::clicked, this, &tubesimple::calculer);
    connect(&debit, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&diametre, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&longueur, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&denivele, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&materiau, &QComboBox::currentTextChanged, this, &tubesimple::checkInputs);


    QDoubleValidator *debitValidator = new QDoubleValidator(0.01, 1000000, 2, this);
    debit.setValidator(debitValidator);

    QDoubleValidator *diametreValidator = new QDoubleValidator(0.01, 1000000, 2, this);
    diametre.setValidator(diametreValidator);

    QDoubleValidator *longueurValidator = new QDoubleValidator(0.01, 1000000, 2, this);
    longueur.setValidator(longueurValidator);

    QDoubleValidator *deniveleValidator = new QDoubleValidator(0.01, 1000000, 2, this);
    denivele.setValidator(deniveleValidator);

}

tubesimple::~tubesimple() {
    delete debit.validator();
    delete diametre.validator();
    delete longueur.validator();
    delete denivele.validator();
}


void tubesimple::keyPressEvent(QKeyEvent *event) {

    // Si la touche "Entrée" est appuyée
    if(event->key() == Qt::Key_Return){

        // Si le bouton Calcul est actif, on clique dessus
        if(Calcul.isEnabled()){
            Calcul.click();
        }
            // Sinon, on passe à l'input suivant
        else {
            focusNextInput();
        }
    }
        // Si la touche "Ctrl" est appuyée, on passe à l'input précédent
    else if (event->key() == Qt::Key_Control) {
        focusPreviousInput();
        return;
    }
        // Si la touche "Tab" est appuyée, on passe à l'input suivant
    else if (event->key() == Qt::Key_Tab) {
        focusNextInput();
        return;
    }
        // Si la touche "Entrée" avec le modificateur est appuyée
    else if (event->modifiers() & Qt::Key_Return) {

        // Si le bouton Calcul est actif, on calcule les résultats
        if (Calcul.isEnabled()) {
            calculer();
            return;
        }
    }
}



void tubesimple::focusPreviousInput() {

    if (denivele.hasFocus()) {
        longueur.setFocus();
        return;
    } else if (longueur.hasFocus()) {
        diametre.setFocus();
        return;
    } else if (diametre.hasFocus()){
        debit.setFocus();
    }
}

void tubesimple::focusNextInput() {

    if (debit.hasFocus() ) {
        diametre.setFocus();
        return;
    } else if (diametre.hasFocus()) {
        longueur.setFocus();
        return;
    } else if (longueur.hasFocus()) {
        denivele.setFocus();
    }

}

void tubesimple::calculer() {

    float D = debit.text().toFloat(); // Récupère la valeur de debit de la QLineEdit et la convertit en float
    float Dia = diametre.text().toFloat(); // Récupère la valeur de diametre de la QLineEdit et la convertit en float
    float L = longueur.text().toFloat(); // Récupère la valeur de longueur de la QLineEdit et la convertit en float
    float deniveles = 0;
    float  k =0;
    float a=0;
    float b = 0 ;

    // Si l'input de dénivelé n'est pas vide, on le convertit en float et on le stocke dans la variable deniveles
    if(!denivele.text().isEmpty()){
        deniveles = denivele.text().toFloat();
    }

    float flowRate = D / 3600; // Convertit m³/h en m³/s
    float pipeDiameter = Dia / 1000; // Convertit mm en m

    float pipeArea = M_PI * pow(pipeDiameter / 2, 2); // Calcule l'aire de la section transversale du tuyau en m²
    float v = flowRate / pipeArea; // Calcule la vitesse d'écoulement en m/s

    QString material = materiau.currentText(); // Récupère la valeur sélectionnée dans la liste déroulante "materiau"

    // Assigner les valeurs de k, a et b selon le matériau choisi
    if (material == "PVC" || material == "Polyéthylène") {
        k=831743.11;
        a = 1.75;
        b=-4.75;
    } else if (material == "Fonte") {
        k=1458844.82;
        a = 1.83;
        b=-4.89;
    } else if (material == "Aluminium") {
        k=1707785.38;
        a = 1.89;
        b=-4.87;
    }

    float pertecharge = k*pow((D*1000/3600),a)*pow((Dia),b)*L; // Calcule la perte de charge en Pa

    float variation = pertecharge+deniveles; // Calcule la variation de charge en Pa

    Perte.setText(QString::number(pertecharge, 'f', 2)); // Met à jour le texte de la QLineEdit "Perte"
    Piezo.setText(QString::number(variation, 'f', 2)); // Met à jour le texte de la QLineEdit "Piezo"

    QString str = "";
    if (v > 2) { // Si la vitesse d'écoulement est supérieure à 2 m/s, on change la couleur de la QLineEdit "Vitesse" en rouge
        Vitesse.setStyleSheet("color: red;  background-color: white ");
        str = QString::number(v, 'f', 2);
    } else { // Sinon, on enlève la couleur rouge
        Vitesse.setStyleSheet("");
        str = QString::number(v, 'f', 2);
    }

    Vitesse.setText(str); // Met à jour le texte de la QLineEdit "Vitesse"
}



// Cette fonction permet de vérifier que les champs d'entrée sont correctement remplis
void tubesimple::checkInputs() {

    // On réinitialise la couleur des champs d'entrée
    debit.setStyleSheet("");
    diametre.setStyleSheet("");
    longueur.setStyleSheet("");

    // On récupère les valeurs des champs d'entrée
    float D = debit.text().toFloat();
    float Dia = diametre.text().toFloat();
    float L = longueur.text().toFloat();

    // On vérifie si les valeurs des champs d'entrée sont correctes
    bool deb = D<=0;
    bool diam = Dia<=0;
    bool Long = L<=0;

    // Si les valeurs ne sont pas correctes, on met la couleur de fond en rouge
    if(deb)
    {
        debit.setStyleSheet("color: red;  background-color: white ");
    }
    if (diam)
    {
        diametre.setStyleSheet("color: red;  background-color: white ");
    }
    if (Long)
    {
        longueur.setStyleSheet("color: red;  background-color: white ");
    }

    // On vérifie si tous les champs sont remplis
    if (debit.text().isEmpty() || diametre.text().isEmpty() || longueur.text().isEmpty() ) {
        clearresult(); // On efface les résultats précédents
        Calcul.setDisabled(true); // On désactive le bouton de calcul
        return;
    } else if(!deb && !diam && !Long){
        Calcul.setDisabled(false); // On active le bouton de calcul
    }

}

void tubesimple::clearresult(){
    Vitesse.setText("");
    Piezo.setText("");
    Perte.setText("");
}


