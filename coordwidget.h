#ifndef COORDWIDGET_H
#define COORDWIDGET_H

#include <QtOpenGL>

class QLineEdit;
class QProgressBar;
class QScrollBar;
class QSlider;
class QSpinBox;
class QTabWidget;
class QTableWidget;
class QTextEdit;

class CoordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CoordWidget(QWidget *parent = 0);

signals:

public slots:

private slots:
    void advanceProgressBar();

private:
    void createTextWidget();
    void createProgressBar();

    QPalette originalPalette;

    QTabWidget *textWidget;
    QTableWidget *tableWidget;
    QTextEdit *textEdit;

    QProgressBar *progressBar;
};

#endif // COORDWIDGET_H
