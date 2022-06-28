#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "obrero.h"
#include "controlador.h"
#include "acerca.h"

#define VERSION "0.2"

QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();

private slots:
    void on_btnCalcular_clicked();

    void on_action_Nuevo_triggered();

    void on_action_Calcular_triggered();

    void on_action_Salir_triggered();

    void on_action_Guardar_triggered();

    void on_actionAcerca_del_Salario_triggered();

private:
    Ui::Salarios *ui;
    Controlador *m_controlador;
    void limpiar();
    void calcular();
};
#endif // SALARIOS_H
