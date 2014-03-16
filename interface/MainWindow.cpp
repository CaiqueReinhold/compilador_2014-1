#include "MainWindow.h"
#include "CodeEditor.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>

MainWindow::MainWindow() :
    QMainWindow()
{
    set_up();
}

MainWindow::~MainWindow()
{
    delete central_widget;
}

void MainWindow::set_up()
{
    central_widget = new QWidget(this);
    v_layout       = new QVBoxLayout(central_widget);
    h_layout       = new QHBoxLayout(central_widget);
    editor         = new CodeEditor(central_widget);
    messages       = new QTextEdit(central_widget);
    bt_new      = new QPushButton("new", central_widget);
    bt_open     = new QPushButton("open", central_widget);
    bt_save     = new QPushButton("save", central_widget);
    bt_copy     = new QPushButton("copy", central_widget);
    bt_paste    = new QPushButton("paste", central_widget);
    bt_cut      = new QPushButton("cut", central_widget);
    bt_compile  = new QPushButton("compile", central_widget);
    bt_gen_code = new QPushButton("generate code", central_widget);
    bt_team     = new QPushButton("team", central_widget);

    messages->setReadOnly(true);
    messages->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    messages->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    messages->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    h_layout->addWidget(bt_new);
    h_layout->addWidget(bt_open);
    h_layout->addWidget(bt_save);
    h_layout->addWidget(bt_copy);
    h_layout->addWidget(bt_paste);
    h_layout->addWidget(bt_cut);
    h_layout->addWidget(bt_compile);
    h_layout->addWidget(bt_gen_code);
    h_layout->addWidget(bt_team);

    v_layout->addLayout(h_layout);
    v_layout->addWidget(editor);
    v_layout->addWidget(messages);

    central_widget->setLayout(v_layout);
    setCentralWidget(central_widget);
    resize(1024, 720);
}