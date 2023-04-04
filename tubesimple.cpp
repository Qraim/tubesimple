//
// Created by qraim on 04/04/23.
//

#include "tubesimple.h"
#include <math.h>

tubesimple::tubesimple(QWidget *parent) : QWidget(parent)
{
    // Create grid layout
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *titleLabel = new QLabel("Perte de charge en tube simple", this);
    gridLayout->addWidget(titleLabel, 0, 1, 1, 5);

    // Add elements to grid layout
    gridLayout->addWidget(new QLabel("Materiau", this), 1, 0);
    gridLayout->addWidget(&materiau, 2, 0);
    gridLayout->addWidget(new QLabel("Debit (L/s)", this), 1, 1);
    debit.setFixedWidth(110);
    gridLayout->addWidget(&debit, 2, 1);
    gridLayout->addWidget(new QLabel("Diametre (mm)", this), 1, 2);
    diametre.setFixedWidth(110);
    gridLayout->addWidget(&diametre, 2, 2);
    gridLayout->addWidget(new QLabel("Longueur (m)", this), 1, 3);
    longueur.setFixedWidth(110);
    gridLayout->addWidget(&longueur, 2, 3);
    gridLayout->addWidget(new QLabel("Denivele (m)", this), 1, 4);
    denivele.setFixedWidth(110);
    gridLayout->addWidget(&denivele, 2, 4);

    // Set up the bottom row of result labels
    QHBoxLayout *resultLabelsLayout = new QHBoxLayout;
    QLabel *perteLabel = new QLabel("Pertes de charge", this);
    QLabel *piezoLabel = new QLabel("Variation Piezo", this);
    QLabel *vitesseLabel = new QLabel("Vitesse", this);
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
    Calcul.setFixedSize(100,20);
    calculerLayout->addWidget(&Calcul);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(calculerLayout);
    mainLayout->addLayout(resultLabelsLayout);
    mainLayout->addLayout(resultFieldsLayout); // Add this line

    // Set the main layout for this widget
    setLayout(mainLayout);

    connect(&Calcul, &QPushButton::clicked, this, &tubesimple::calculer);
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
        return;
        // gérer l'appuie sur la touche entrée
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
    float Dia = diametre.text().toFloat(); // Récupération des variables
    float L = longueur.text().toFloat();
    float deniveles = denivele.text().toFloat();

    float v = D/(M_PI*pow((Dia/2),2));

    float pertecharge = (L/Dia)*(pow(v,2)/9.81);

    float variation = pertecharge+deniveles;

    Perte.setText(QString::fromStdString(std::to_string(pertecharge)));
    Piezo.setText(QString::fromStdString(std::to_string(variation)));
    Vitesse.setText(QString::fromStdString(std::to_string(v)));

}
