#if !defined(MAINWINDOW_H)
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSettings>
#include <QStringList>
#include <QString>
#include <QVector>
#include <QThread>
#include <QMutex>

#include "worker.h"

namespace Ui
{
    class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private slots:
        void on_loadFilesButton_clicked();
        void on_encodeFilesButton_clicked();
        void onErrored(QString err);
        void onFinished(QString input_file_name);

    private:
        Ui::MainWindow* ui;
        QStringList m_files;
        void refreshList();
        QSettings m_settings;
        void updateLastOpenedLocation(QString dir_path);
        QVector<QThread*> m_threads;
        QVector<Worker*> m_workers;
        QMutex m_mutex;
};

#endif // MAINWINDOW_H
