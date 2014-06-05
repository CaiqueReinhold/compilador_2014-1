#include "Highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkMagenta);
    keywordFormat.setFontWeight(QFont::Bold);

    commentFormat.setForeground(QColor(153, 200, 51));

    quotationFormat.setForeground(Qt::blue);
    
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bmain\\b" << "\\bglobal\\b"
                    << "\\bboolean\\b" << "\\bdo\\b" << "\\belse\\b"
                    << "\\bend\\b" << "\\bfalse\\b" << "\\btrue\\b"
                    << "\\bfloat\\b" << "\\bif\\b" << "\\binteger\\b"
                    << "\\bprint\\b" << "\\bprintln\\b" << "\\bscan\\b"
                    << "\\bstring\\b" << "\\bvoid\\b" << "\\bwhile\\b"
                    << "\\breturn\\b" << "\\blocal\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("#[^\n]*");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    startBlockComment = QRegExp("\\{");
    endBlockComment = QRegExp("\\}");
    setCurrentBlockState(0);
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = startBlockComment.indexIn(text);
    while (startIndex >= 0) {
        int endIndex = endBlockComment.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + endBlockComment.matchedLength();
        }
        setFormat(startIndex, commentLength, commentFormat);
        startIndex = startBlockComment.indexIn(text, startIndex + commentLength);
    }
}