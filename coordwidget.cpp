#include <QtGui>
#include "coordwidget.h"

CoordWidget::CoordWidget(QWidget *parent) :
    QWidget(parent)
{
    originalPalette = QApplication::palette();

    createTextWidget();
    createProgressBar();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(textWidget, 0, 0);
    mainLayout->addWidget(progressBar, 1, 0);
    setLayout(mainLayout);
}

void CoordWidget::advanceProgressBar()
{
    int curVal = progressBar->value();
    int maxVal = progressBar->maximum();
    progressBar->setValue(curVal + (maxVal - curVal) / 100);
}

void CoordWidget::createTextWidget()
{
    textWidget = new QTabWidget;
    textWidget->setSizePolicy(QSizePolicy::Preferred,
                              QSizePolicy::Ignored);

    QWidget *tab1 = new QWidget;
    tableWidget = new QTableWidget(50, 3);
    QStringList headers;
    headers << "Latitude" << "Longitude" << "Altitude";
    tableWidget->setHorizontalHeaderLabels(headers);

    QHBoxLayout *tab1hbox = new QHBoxLayout;
    tab1hbox->setMargin(5);
    tab1hbox->addWidget(tableWidget);
    tab1->setLayout(tab1hbox);

    QWidget *tab2 = new QWidget;
    textEdit = new QTextEdit;

    textEdit->setPlainText(tr("Twinkle, twinkle, little star,\n"
                              "How I wonder what you are.\n"
                              "Up above the world so high,\n"
                              "Like a diamond in the sky.\n"
                              "Twinkle, twinkle, little star,\n"
                              "How I wonder what you are!\n"));

    QHBoxLayout *tab2hbox = new QHBoxLayout;
    tab2hbox->setMargin(5);
    tab2hbox->addWidget(textEdit);
    tab2->setLayout(tab2hbox);

    textWidget->addTab(tab1, tr("&Table"));
    textWidget->addTab(tab2, tr("Text &Edit"));
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
