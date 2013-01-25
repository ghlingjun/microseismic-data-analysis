#include <QtGui>
#include "coordwidget.h"

/**
  author: Ethan
  date: 2013-1-15
  */
CoordWidget::CoordWidget(QWidget *parent) :
    QWidget(parent)
{
    originalPalette = QApplication::palette();

    createTextWidget();
//    createProgressBar();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(textWidget, 0, 0);
//    mainLayout->addWidget(progressBar, 1, 0);
    setLayout(mainLayout);
}

void CoordWidget::createTextWidget()
{
    textWidget = new QTabWidget;
    textWidget->setSizePolicy(QSizePolicy::Preferred,
                              QSizePolicy::Ignored);

//    QWidget *tab1 = new QWidget;
//    tableWidget = new QTableWidget(50, 3);
//    QStringList headers;
//    headers << "Latitude" << "Longitude" << "Altitude";
//    tableWidget->setHorizontalHeaderLabels(headers);

//    QHBoxLayout *tab1hbox = new QHBoxLayout;
//    tab1hbox->setMargin(5);
//    tab1hbox->addWidget(tableWidget);
//    tab1->setLayout(tab1hbox);

    QWidget *textTab = new QWidget;
    textEdit = new QTextEdit;

    textEdit->setPlainText(tr("Every line is a coordinate(the max coordinate is 200)."
                              "Write like this: \n{\n"
                              "C1,1.1,3.2,2.1;\n"
                              "C2,5.3,4.3,3.2;\n"
                              "C3,3.3,3.1,5.3;\n"
                              "C4,4.3,2.1,2.3;\n"
                              "\n}"));
//    "Twinkle, twinkle, little star,\n"
//    "How I wonder what you are.\n"
//    "Up above the world so high,\n"
//    "Like a diamond in the sky.\n"
//    "Twinkle, twinkle, little star,\n"
//    "How I wonder what you are!\n"
    QHBoxLayout *textTabhbox = new QHBoxLayout;
    textTabhbox->setMargin(5);
    textTabhbox->addWidget(textEdit);
    textTab->setLayout(textTabhbox);

//    textWidget->addTab(tab1, tr("&Table"));
    textWidget->addTab(textTab, tr("Coordinate &Edit"));
}

QTextEdit* CoordWidget::getTextEdit()
{
    return textEdit;
}

void CoordWidget::createProgressBar()
{
    progressBar = new QProgressBar;
    progressBar->setRange(0, 10000);
    progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceProgressBar()));
    timer->start(1000);
}

void CoordWidget::advanceProgressBar()
{
    int curVal = progressBar->value();
    int maxVal = progressBar->maximum();
    progressBar->setValue(curVal + (maxVal - curVal) / 100);
}
