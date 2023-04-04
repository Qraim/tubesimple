//
// Created by qraim on 04/04/23.
//

#include "tubesimple.h"

tubesimple::tubesimple(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400,300);

    QLabel *labelMateriau = new QLabel("Materiau", this);
    QLabel *labelDebit = new QLabel("Debit", this);
    QLabel *labelDiametre = new QLabel("Diametre", this);
    QLabel *labelLongueur = new QLabel("Longueur", this);
    QLabel *labelDenivele = new QLabel("Denivele", this);

    QHBoxLayout *inputLabelsLayout = new QHBoxLayout;
    inputLabelsLayout->addWidget(labelMateriau);
    inputLabelsLayout->addWidget(labelDebit);
    inputLabelsLayout->addWidget(labelDiametre);
    inputLabelsLayout->addWidget(labelLongueur);
    inputLabelsLayout->addWidget(labelDenivele);

    QHBoxLayout *inputsLayout = new QHBoxLayout;
    inputsLayout->addWidget(&materiau);
    inputsLayout->addWidget(&debit);
    inputsLayout->addWidget(&diametre);
    inputsLayout->addWidget(&longueur);
    inputsLayout->addWidget(&denivele);

    QHBoxLayout *resultLabelsLayout = new QHBoxLayout;
    resultLabelsLayout->addWidget(&Perte);
    resultLabelsLayout->addWidget(&Piezo);
    resultLabelsLayout->addWidget(&Vitesse);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLabelsLayout);
    mainLayout->addLayout(inputsLayout);
    mainLayout->addLayout(resultLabelsLayout);

    setLayout(mainLayout);
}

