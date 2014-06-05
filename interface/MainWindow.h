#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QToolButton;
class QTextEdit;
class CodeEditor;
class QLabel;

class Highlighter;

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void actionNew();
    void actionOpen();
    void actionSave();
    void actionCopy();
    void actionPaste();
    void actionCut();
    void actionCompile();
    void actionGenCode();
    void actionTeam();
    void textChanged();

private:
    QWidget* central_widget;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;
    CodeEditor* editor;
    QTextEdit* messages;
    QToolButton* bt_new;
    QToolButton* bt_open;
    QToolButton* bt_save;
    QToolButton* bt_copy;
    QToolButton* bt_paste;
    QToolButton* bt_cut;
    QToolButton* bt_compile;
    QToolButton* bt_gen_code;
    QToolButton* bt_team;
    Highlighter* highlighter;

    QString file_name;

    void setUp();
    void setUpButtons();
};

#endif