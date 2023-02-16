#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

#include <QFileDialog>
#include <QFileInfo>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLastOpenedLocation(QString recent_file_path)
{
    m_settings.setValue("last_opened_location",recent_file_path);
}

void MainWindow::refreshList()
{
    if(!m_files.empty())
    {
        qDebug() << "refreshing List";
        ui->inputFilesListWidget->clear();
        for (int i = 0; i < m_files.size(); i++)
            ui->inputFilesListWidget->addItem(m_files.at(i));
    }
}

void MainWindow::on_loadFilesButton_clicked()
{
    QString last_opened_location = m_settings.value("last_opened_location").toString();
    if(last_opened_location.isNull())
        last_opened_location = "/Users/nav/Projects_CCPP";
    m_files = QFileDialog::getOpenFileNames(
        this,
        tr("Select WAV files"),
        last_opened_location,
        tr("Audio (*.wav)")
    );
    if(!m_files.empty())
    {
        updateLastOpenedLocation(m_files.at(0));
        refreshList();
    }
}

void MainWindow::on_encodeFilesButton_clicked()
{
    if(!m_files.isEmpty())
    {
        for (int i = 0; i < m_files.size(); i++)
        {
            QString i_file = m_files.at(i);
            QThread* thread = new QThread;
            Worker* worker = new Worker(i_file);
            m_threads.push_back(thread);
            m_workers.push_back(worker);
            worker->moveToThread(thread);
            connect(worker, SIGNAL(errored(QString)), this, SLOT(onErrored(QString)));
            connect(worker, SIGNAL(finished(QString)),this,SLOT(onFinished(QString)));
            connect(thread, SIGNAL(started()), worker, SLOT(process()));
            connect(worker, SIGNAL(finished(QString)), thread, SLOT(quit()));
            connect(worker, SIGNAL(finished(QString)), worker, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
        }
    }
}

void MainWindow::onFinished(QString input_file_name){

    m_mutex.lock();
    qint32 file_ix = m_files.indexOf(input_file_name);
    m_files.removeAt(file_ix);
    m_threads.remove(file_ix);
    m_workers.remove(file_ix);
    refreshList();
    m_mutex.unlock();
}

void MainWindow::onErrored(QString err){
    qDebug() << "ERROR: " <<  err;
}