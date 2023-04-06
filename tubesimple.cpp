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


    // Create grid layout
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *titleLabel = new QLabel("Perte de charge en tube simple", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(titleLabel, 0, 0, 1, 5);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 1);

    // Add elements to grid layout
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

    // Set up the bottom row of result labels
    QHBoxLayout *resultLabelsLayout = new QHBoxLayout;
    QLabel *perteLabel = new QLabel("Pertes de charge (m)", this);
    QLabel *piezoLabel = new QLabel("Variation Piezo (m)", this);
    QLabel *vitesseLabel = new QLabel("Vitesse (m/s)", this);
    resultLabelsLayout->addWidget(perteLabel);
    resultLabelsLayout->addWidget(piezoLabel);
    resultLabelsLayout->addWidget(vitesseLabel);

    // Set up the bottom row of result fields
    QHBoxLayout *resultFieldsLayout = new QHBoxLayout;
    Perte.setReadOnly(true);
    Piezo.setReadOnly(true);
    Vitesse.setReadOnly(true);
    resultFieldsLayout->addWidget(&Perte);
    resultFieldsLayout->addWidget(&Piezo);
    resultFieldsLayout->addWidget(&Vitesse);

    // Add non-editable fields to the layout
    QHBoxLayout *nonEditableFieldsLayout = new QHBoxLayout;

    // Add the "Calculer" button
    Calcul.setText("Calculer");
    QHBoxLayout *calculerLayout = new QHBoxLayout;
    Calcul.setFixedSize(120, 30);
    calculerLayout->addStretch(1); // Add a stretcher to the left of the button
    calculerLayout->addWidget(&Calcul);
    calculerLayout->addStretch(1); // Add a stretcher to the right of the button



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacing(10); // Add a vertical space of 10 pixels
    mainLayout->addLayout(calculerLayout);
    mainLayout->addSpacing(10); // Add a vertical space of 10 pixels
    mainLayout->addLayout(resultLabelsLayout);
    mainLayout->addLayout(resultFieldsLayout);


    // Set the main layout for this widget
    setLayout(mainLayout);

    Calcul.setDisabled(true);
    debit.hasFocus();

    connect(&Calcul, &QPushButton::clicked, this, &tubesimple::calculer);
    connect(&debit, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&diametre, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&longueur, &QLineEdit::textChanged, this, &tubesimple::checkInputs);
    connect(&denivele, &QLineEdit::textChanged, this, &tubesimple::checkInputs);

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

    if(event->key() == Qt::Key_Return){
        if(Calcul.isEnabled()){
            Calcul.click();
        } else {
            focusNextInput();
        }
    } else if (event->key() == Qt::Key_Control) {
        focusPreviousInput();
        return;
    } else if (event->key() == Qt::Key_Tab) {
        focusNextInput();
        event->accept(); // Prevent the default tab behavior
        return;
    } else if (event->modifiers() & Qt::Key_Return) {
        if (Calcul.isEnabled()) { // Si calcul est actif
            calculer();
            return;
        }
    } else {
        QWidget::keyPressEvent(event);
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

    float D = debit.text().toFloat();
    float Dia = diametre.text().toFloat();
    float L = longueur.text().toFloat();
    float deniveles = 0;
    float  k =0;
    float a=0;
    float b = 0 ;


    if(!denivele.text().isEmpty()){
        deniveles = denivele.text().toFloat();
    }

    float flowRate = D / 3600; // Convert m³/h to m³/s
    float pipeDiameter = Dia / 1000; // Convert mm to m

    float pipeArea = M_PI * pow(pipeDiameter / 2, 2);
    float v = flowRate / pipeArea;

    QString material = materiau.currentText();

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

    float pertecharge = k*pow((D*1000/3600),a)*pow((Dia),b)*L;

    float variation = pertecharge+deniveles;

    Perte.setText(QString::number(pertecharge, 'f', 2));
    Piezo.setText(QString::number(variation, 'f', 2));

    QString str = "";
    if (v > 2) {
        Vitesse.setStyleSheet("color: red;  background-color: white ");
        str = QString::number(v, 'f', 2);
    } else {
        Vitesse.setStyleSheet("");
        str = QString::number(v, 'f', 2);
    }

    Vitesse.setText(str);
}



void tubesimple::checkInputs() {

    debit.setStyleSheet("");
    diametre.setStyleSheet("");
    longueur.setStyleSheet("");

    float D = debit.text().toFloat();
    float Dia = diametre.text().toFloat();
    float L = longueur.text().toFloat();

    bool deb = D<=0;
    bool diam = Dia<=0;
    bool Long = L<=0;

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

    if (debit.text().isEmpty() || diametre.text().isEmpty() || longueur.text().isEmpty() ) {
        clearresult();
        Calcul.setDisabled(true);
        return;
    } else if(!deb && !diam && !Long){
        Calcul.setDisabled(false);
    }
}

void tubesimple::clearresult(){
    Vitesse.setText("");
    Piezo.setText("");
    Perte.setText("");
}


