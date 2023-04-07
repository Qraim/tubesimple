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
#include <QDoubleValidator>
#include <memory>

#include <iostream>


class tubesimple : public QWidget {
Q_OBJECT

public:

    tubesimple(QWidget *parent = nullptr);
    ~tubesimple();

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

    ///
    /// @brief Gère l'événement de pression de touche du clavier
    ///
    /// @param event : Événement de pression de touche
    ///
    void keyPressEvent(QKeyEvent *event) override;

    ///
    /// @brief Change le champ actif pour le champ suivant
    ///
    void focusNextInput();

    ///
    /// @brief Change le champ actif pour le champ précédent
    ///
    void focusPreviousInput();

    ///
    /// @brief Calculer les résultats et les afficher dans le tableau
    ///
    void calculer();

    ///
    /// @brief Vérifier que tous les champs de saisie sont remplis
    ///
    void checkInputs();

    ///
    /// @brief Effacer les résultats dans le tableau
    ///
    void clearresult();

};


#endif //TUBESIMPLE_TUBESIMPLE_H
