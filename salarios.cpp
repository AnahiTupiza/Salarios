#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    /*
    //Obrero modelo("Juan",25,TipoJornada::Matutina);
    //qDebug()<<modelo.toString();
    Controlador control;
    control.setDatos("Juan",25,TipoJornada::Matutina);
    if (control.calcular()){
        qDebug()<<control.getDatos();
    }else {
        qDebug()<<"No se pudo calcular salarios";
    }
*/
    calcular();
}

void Salarios::on_action_Nuevo_triggered()
{
    //Limpiar widgets
    limpiar();
    //Limpiar el texto de los calculos
    ui->outCalculos->clear();
    //Mostrar la barra de estado
    ui->statusbar->showMessage("Nuevos calculos de salario ",3000);
}


void Salarios::limpiar()
{
    // Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();

}

void Salarios::calcular()
{
    //Obtener datos de la GUI
    QString nombre =ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada =TipoJornada::Matutina;
    }else if(ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }

    //Validar datos
    if(nombre == "" || horas == 0){
        QMessageBox::warning(this,"Advertencia","El nombre y/o el número de horas es incorrecto");
        return;
    }

    //Establecer datos al contador
    m_controlador->setDatos(nombre, horas, jornada);
    // Calcular salarios
    if (m_controlador->calcular()) {
        // Muestra los resultados
        ui->outCalculos->appendPlainText(m_controlador->getDatos());
    } else {
        QMessageBox::critical(this,"Error","No se puede calcular el salario.");
    }
    // Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();

    //Mostrar la barra de estado
    ui->statusbar->showMessage("Salario de " + nombre + " calculado.",5000);
}


void Salarios::on_action_Calcular_triggered()
{
    calcular();
}


void Salarios::on_action_Salir_triggered()
{
    this->close();
}


void Salarios::on_action_Guardar_triggered()
{
    //Abrir un cuadro de dialogo para seleccionar el path y archivo a guardar
    QString nombreArchivo =QFileDialog::getSaveFileName(this,
                                                 "Guardar calculos de salarios",
                                                 QDir::home().absolutePath()+"/salarios.txt",
                                                 "Archivos de salario (*.txt)");
    //Crear un objeto file
    QFile archivo(nombreArchivo);
    //Tratar de abrir el archivo
    if (archivo.open(QFile::WriteOnly|QFile::Truncate)){
        //Crear un objeto "stream" de texto
        QTextStream salida(&archivo);
        //Enviar los datos del resultado a la salida
        salida<<ui->outCalculos->toPlainText();
        //Mostrar mensaje en la barra de estados
        ui->statusbar->showMessage("Datos guardados en: "+ nombreArchivo ,5000);
        //Cerrar el archivo
        archivo.close();

    }else {
        //Manejo de error
        QMessageBox::warning(this,
                             "Guardar archivo",
                             "No se puede acceder el archivo para guardar los datos.");
    }

}


void Salarios::on_actionAcerca_del_Salario_triggered()
{
    //Crear un objeto del cuadro de diálogo
    Acerca *dialog=new Acerca(this);
    //Enviar datos a la otra ventana
    dialog->setVersion(VERSION);
    //Mostrar la venta en modo NODAL
    dialog->exec();
    //luego de cerrar la ventana, se acceden a los datos de la misma
    qDebug()<<dialog->valor();
}

