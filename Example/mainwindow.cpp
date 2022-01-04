#include "mainwindow.h"
#include "FlowLayout.h"
#include "HoverButton.h"

#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto widget = new QWidget;
    auto flowlayout = new FlowLayout;
    flowlayout->addWidget(new QLabel("1"));
    flowlayout->addWidget(new QLabel("2"));
    flowlayout->addWidget(new QLabel("3"));
    flowlayout->addWidget(new QLabel("4"));
    flowlayout->addWidget(new QLabel("5"));
    widget->setLayout(flowlayout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
}

