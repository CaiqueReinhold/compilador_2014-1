#ifndef SYNTAX_H
#define SYNTAX_H

#include <QSyntaxHighlighter>
#include <QVector>
#include <QRegExp>
#include <QTextCharFormat>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
     void highlightBlock(const QString &text);

 private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat quotationFormat;

    QRegExp startBlockComment;
    QRegExp endBlockComment;
};

#endif