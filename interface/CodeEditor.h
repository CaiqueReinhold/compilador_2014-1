#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QWidget>
#include <QSize>
#include <QPlainTextEdit>

class QPaintEvent;
class QResizeEvent;
class CodeEditor;

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor* editor);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    CodeEditor* editor;
};

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget* p = 0);

    void LineNumberAreaPaintEvent(QPaintEvent*);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void updateLineNumberArea(const QRect&, int);

private:
    QWidget* lineNumberArea;

};

#endif // CODEEDITOR_H
