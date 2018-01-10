#ifndef CLANG_TRACE_HIGHLIGHTER_H
#define CLANG_TRACE_HIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

class clang_trace_highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit clang_trace_highlighter(QTextDocument *parent = 0);
    ~clang_trace_highlighter();
    void sl_setter_current_keyword(QString keyword);
    QString current_keyword_trace_point = "";

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
        quint32 id_rule = 0;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat tracePointFormat;
    QTextCharFormat preprocessorFormat;
    QTextCharFormat typesFormat;
    //QTextCharFormat operatorFormat;
    const quint32 id_trace = 1;



public slots:

};

#endif // CLANG_TRACE_HIGHLIGHTER_H
