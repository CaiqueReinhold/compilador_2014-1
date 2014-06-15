#include "codeeditor.h"

#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QString>
#include <QTextBlock>

//LINE_NUMBER_AREA IMPLEMENTATION
LineNumberArea::LineNumberArea(CodeEditor* editor):
    QWidget(editor)
{
    this->editor = editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(editor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    editor->LineNumberAreaPaintEvent(event);
}
//LINE_NUMBER_AREA IMPLEMENTATION

//CODE_EDITOR_IMPLEMENTATION
CodeEditor::CodeEditor(QWidget* parent) :
    QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
    setWordWrapMode(QTextOption::NoWrap);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    setFont(font);
    
    //makes size of a tab the same as 4 spaces
    setTabStopWidth(fontMetrics().width(QLatin1Char(' '))*4);
}

int CodeEditor::lineNumberAreaWidth()
{
    //size of 3 character plus 10 pixels for margin
    return fontMetrics().width(QLatin1Char('9'))*3 + 10;
}

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
}

void CodeEditor::resizeEvent(QResizeEvent* event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::LineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(240,240,240));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    int curr_line = textCursor().block().blockNumber();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(blockNumber==curr_line?QColor(0, 0, 0):QColor(120, 120, 120));
            painter.drawText(0, top, lineNumberArea->width()-10, fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
//CODE_EDITOR_IMPLEMENTATION

