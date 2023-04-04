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

    QLabel Perte;
    QLabel Piezo;
    QLabel Vitesse;

};


#endif //TUBESIMPLE_TUBESIMPLE_H
