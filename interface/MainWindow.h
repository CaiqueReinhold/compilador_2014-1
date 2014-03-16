#include <QMainWindow>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QTextEdit;
class CodeEditor;

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:


private:
    QWidget* central_widget;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;
    CodeEditor* editor;
    QTextEdit* messages;
    QPushButton* bt_new;
    QPushButton* bt_open;
    QPushButton* bt_save;
    QPushButton* bt_copy;
    QPushButton* bt_paste;
    QPushButton* bt_cut;
    QPushButton* bt_compile;
    QPushButton* bt_gen_code;
    QPushButton* bt_team;

    void set_up();
};