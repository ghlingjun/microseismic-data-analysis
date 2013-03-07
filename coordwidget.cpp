#include <QtGui>
#include <QtSql>

#include "coordwidget.h"

/**
  author: Ethan
  date: 2013-1-15
  */
CoordWidget::CoordWidget(QWidget *parent) :
    QWidget(parent)
{
    originalPalette = QApplication::palette();

//    createTextWidget();
    createTbl();
//    createProgressBar();

    QGridLayout *mainLayout = new QGridLayout;
//    mainLayout->addWidget(textWidget, 0, 0);
    mainLayout->addWidget(tableView, 0, 0);
//    mainLayout->addWidget(progressBar, 1, 0);
    setLayout(mainLayout);
}

void CoordWidget::createTbl()
{
    DataModel *dataModel = DataModel::getInstance();

//    QSqlTableModel model;
//    initializeModel(&model);
//    tableView = createView(QObject::tr("Table Model"), &model);

//    QSqlTableModel *model = new QSqlTableModel;
    dataModel->initializeModel();
    tableView = dataModel->createView(QObject::tr("Table Model"));
//    tableView->show();
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

void CoordWidget::initializeModel(QSqlTableModel *model)
 {
     model->setTable("msdata");
//     model->setQuery("select id,name,x,y,z,time from msdata");
//     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->select();

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("X"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Y"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Z"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Longitude"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("Latitude"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("Altitude"));
     model->setHeaderData(8, Qt::Horizontal, QObject::tr("Pressure"));
     model->setHeaderData(9, Qt::Horizontal, QObject::tr("Time"));
 }

QTableView * CoordWidget::createView(const QString &title, QSqlTableModel *model)
 {
     QTableView *view = new QTableView;
     view->setSizePolicy(QSizePolicy::Preferred,
                         QSizePolicy::Ignored);
     view->setModel(model);
//     view->setWindowTitle(title);
     return view;
 }
