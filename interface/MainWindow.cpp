#include "MainWindow.h"
#include "CodeEditor.h"
#include "Highlighter.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QLabel>
#include <QIcon>
#include <QFontMetrics>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <fstream>
#include <cstdlib>

#include "Lexical.h"
#include "Syntactic.h"
#include "Semantic.h"

QString MODIFIED("Modificado");
QString NOT_MODIFIED("Não modificado");

MainWindow::MainWindow() :
    QMainWindow()
{
    setUp();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setUp()
{
    central_widget = new QWidget(this);
    v_layout       = new QVBoxLayout(central_widget);
    h_layout       = new QHBoxLayout(central_widget);
    editor         = new CodeEditor(central_widget);
    messages       = new QTextEdit(central_widget);
    bt_new      = new QToolButton(central_widget);
    bt_open     = new QToolButton(central_widget);
    bt_save     = new QToolButton(central_widget);
    bt_copy     = new QToolButton(central_widget);
    bt_paste    = new QToolButton(central_widget);
    bt_cut      = new QToolButton(central_widget);
    bt_compile  = new QToolButton(central_widget);
    bt_gen_code = new QToolButton(central_widget);
    bt_team     = new QToolButton(central_widget);
    highlighter = new Highlighter(editor->document());

    setUpButtons();
    h_layout->addWidget(bt_new);
    h_layout->addWidget(bt_open);
    h_layout->addWidget(bt_save);
    h_layout->addWidget(bt_copy);
    h_layout->addWidget(bt_paste);
    h_layout->addWidget(bt_cut);
    h_layout->addWidget(bt_compile);
    h_layout->addWidget(bt_gen_code);
    h_layout->addWidget(bt_team);

    connect(bt_new,     SIGNAL(clicked()), this, SLOT(actionNew()));
    connect(bt_open,    SIGNAL(clicked()), this, SLOT(actionOpen()));
    connect(bt_save,    SIGNAL(clicked()), this, SLOT(actionSave()));
    connect(bt_copy,    SIGNAL(clicked()), this, SLOT(actionCopy()));
    connect(bt_paste,   SIGNAL(clicked()), this, SLOT(actionPaste()));
    connect(bt_cut,     SIGNAL(clicked()), this, SLOT(actionCut()));
    connect(bt_compile, SIGNAL(clicked()), this, SLOT(actionCompile()));
    connect(bt_gen_code,SIGNAL(clicked()), this, SLOT(actionGenCode()));
    connect(bt_team,    SIGNAL(clicked()), this, SLOT(actionTeam()));
    connect(editor,     SIGNAL(textChanged()), this, SLOT(textChanged()));

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setPointSize(10);
    messages->setFont(font);

    messages->setReadOnly(true);
    messages->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    messages->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    messages->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    messages->setMaximumHeight(QFontMetrics(font).height()*6+8);
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    v_layout->addLayout(h_layout);
    v_layout->addWidget(editor);
    v_layout->addWidget(messages);

    statusBar()->setVisible(true);
    central_widget->setLayout(v_layout);
    setCentralWidget(central_widget);
    resize(1024, 720);
    actionNew();
}

void MainWindow::setUpButtons()
{
    bt_new->     setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_open->    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_save->    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_copy->    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_paste->   setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_cut->     setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_compile-> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_gen_code->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_team->    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    bt_new->setIcon(QIcon(":res/images/new.png"));
    bt_new->setIconSize(QSize(50,50));
    bt_new->setText(tr("Novo [ctrl-n]"));
    bt_new->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_new->setShortcut(QKeySequence::New);

    bt_open->setIcon(QIcon(":res/images/open.png"));
    bt_open->setIconSize(QSize(50,50));
    bt_open->setText(tr("Abrir [ctrl-o]"));
    bt_open->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_open->setShortcut(QKeySequence::Open);

    bt_save->setIcon(QIcon(":res/images/save.png"));
    bt_save->setIconSize(QSize(50,50));
    bt_save->setText(tr("Salvar [ctrl-s]"));
    bt_save->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_save->setShortcut(QKeySequence::Save);

    bt_copy->setIcon(QIcon(":res/images/copy.png"));
    bt_copy->setIconSize(QSize(50,50));
    bt_copy->setText(tr("Copiar [ctrl-c]"));
    bt_copy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_copy->setShortcut(QKeySequence::Copy);

    bt_paste->setIcon(QIcon(":res/images/paste.png"));
    bt_paste->setIconSize(QSize(50,50));
    bt_paste->setText(tr("Colar [ctrl-v]"));
    bt_paste->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_paste->setShortcut(QKeySequence::Paste);

    bt_cut->setIcon(QIcon(":res/images/cut.png"));
    bt_cut->setIconSize(QSize(50,50));
    bt_cut->setText(tr("Recortar [ctrl-x]"));
    bt_cut->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_cut->setShortcut(QKeySequence::Cut);

    bt_compile->setIcon(QIcon(":res/images/compile.png"));
    bt_compile->setIconSize(QSize(50,50));
    bt_compile->setText(tr("Compilar [F8]"));
    bt_compile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_compile->setShortcut(Qt::Key_F8);

    bt_gen_code->setIcon(QIcon(":res/images/gen_code.png"));
    bt_gen_code->setIconSize(QSize(50,50));
    bt_gen_code->setText(tr("Gerar Código [F9]"));
    bt_gen_code->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_gen_code->setShortcut(Qt::Key_F9);

    bt_team->setIcon(QIcon(":res/images/team.png"));
    bt_team->setIconSize(QSize(50,50));
    bt_team->setText(tr("Equipe [F1]"));
    bt_team->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bt_team->setShortcut(Qt::Key_F1);
}

void MainWindow::actionNew()
{
    editor->setPlainText(tr(""));
    messages->setText(tr(""));
    statusBar()->showMessage(NOT_MODIFIED);
    file_name = "";
}

void MainWindow::actionOpen()
{
    file_name = QFileDialog::getOpenFileName(this, tr("Save File"), QString(),
            tr("All Files (*)"));

    if (!file_name.isEmpty())
    {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Erro"), tr("O arquivo não pode ser aberto."));
        }
        else
        {
            QTextStream stream(&file);
            QString line, file_content;
            line = stream.readLine();
            while (!line.isNull())
            {
                file_content += line;
                file_content += "\r\n";
                line = stream.readLine();
            }
            editor->setPlainText(file_content);
            messages->setText(tr(""));
            statusBar()->showMessage(NOT_MODIFIED + tr("  -  ") + file_name);
            file.close();
        }
    }
}

void MainWindow::actionSave()
{
    if (file_name.isEmpty())
    {
        file_name = QFileDialog::getSaveFileName(this, tr("Save File"), QString());
        if (file_name.isEmpty())
            return;
    }

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::information(this, tr("Erro"), tr("O arquivo não pode ser aberto."));
    }
    else
    {
        QTextStream stream(&file);
        QString contents = editor->toPlainText();
        stream << contents;
        file.close();
        messages->setText(tr(""));
        statusBar()->showMessage(NOT_MODIFIED + tr("  -  ") + file_name);
    }
}

void MainWindow::actionCopy()
{
    editor->copy();
}

void MainWindow::actionPaste()
{
    editor->paste();
}

void MainWindow::actionCut()
{
    editor->cut();
}

void MainWindow::actionCompile()
{
    QByteArray tmpBuff = editor->toPlainText().toLatin1();
    const char* program = tmpBuff.data();
    
    if (!program[0])
    {
        messages->setText(tr("nenhum programa para compilar"));
        return;
    }

    if (file_name.isEmpty())
    {
        QMessageBox::information(this, tr("Erro"),
            tr("Salve o programa antes de compilar."));
        return;
    }
    
    QString outFile = file_name;
    int extensionIndex = outFile.lastIndexOf(QChar('.'));
    if (extensionIndex > 0)
        outFile.chop(extensionIndex);
    outFile += ".il";

    std::fstream outCode(outFile.toStdString().c_str(),
                         std::fstream::out | std::fstream::trunc);
    Lexical lexical(program);
    Syntactic syntactic;
    Semantic semantic(outCode);

    QString out;
    try
    {
        syntactic.parse(&lexical, &semantic);
        out = tr("Programa compilado com sucesso.");
    }
    catch (LexicalError& e)
    {
        out = e.getMessage();
    }
    catch (SyntacticError& e)
    {
        out = e.getMessage();
    }
    catch (SemanticError& e)
    {
        out = e.getMessage();
    }
    catch (...)
    {
        out = tr("Erro inesperado durente a compilação");
    }

    outCode.close();
    messages->setText(out);
}

void MainWindow::actionGenCode()
{
    messages->setText(tr("Geração de código ainda não foi implementada"));
}

void MainWindow::actionTeam()
{
    messages->setText(tr("Alunos: Caíque Reinhold e William Maurício Glück"));
}

void MainWindow::textChanged()
{
    statusBar()->showMessage(MODIFIED);
}