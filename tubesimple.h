//
// Created by qraim on 04/04/23.
//

#ifndef TUBESIMPLE_TUBESIMPLE_H
#define TUBESIMPLE_TUBESIMPLE_H

#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QShortcut>
#include <QIcon>
#include <QPixmap>
#include <QDesktopWidget>
#include <QFormLayout>

#include <iostream>


class tubesimple : public QWidget {
Q_OBJECT

public:
    tubesimple(QWidget *parent = nullptr);

private:

    QComboBox materiau;

    QLineEdit debit;
    QLineEdit diametre;
    QLineEdit longueur;
    QLineEdit denivele;

    QLineEdit Perte;
    QLineEdit Piezo;
    QLineEdit Vitesse;

    QPushButton Calcul;

    void keyPressEvent(QKeyEvent *event);

    void focusNextInput();

    void focusPreviousInput();

    void calculer();
};


#endif //TUBESIMPLE_TUBESIMPLE_H
