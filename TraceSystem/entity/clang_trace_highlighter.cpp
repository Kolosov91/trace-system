#include "clang_trace_highlighter.h"

clang_trace_highlighter::clang_trace_highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QBrush(QColor(0,148,255)));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bconst\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b" << "\\bsignals\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bvirtual\\b" << "\\bvolatile\\b"
                    << "\\bgoto\\b" << "\\breturn\\b" << "\\bif\\b" << "\\belse\\b"
                    << "\\bswitch\\b" << "\\bcase\\b" << "\\bfor\\b" << "\\btrue\\b" << "\\bfalse\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //////

    typesFormat.setForeground(QBrush(QColor::fromRgb(0xFF05E1)));
    QStringList typesPatterns;
    typesPatterns  << "\\bshort\\b" << "\\bsigned\\b" << "\\bunsigned\\b"
                   << "\\bvoid\\b" << "\\bu32\\b" << "\\bu16\\b" << "\\bu8\\b"
                   << "\\bs32\\b" << "\\bs16\\b" << "\\bs8\\b"
                   << "\\bchar\\b" << "\\bdouble\\b" << "\\bint\\b" << "\\bbool\\b";
    foreach (const QString &pattern, typesPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = typesFormat;
        highlightingRules.append(rule);
    }

    //////

    QStringList preprocessorPatterns;

    preprocessorFormat.setForeground(QBrush(QColor::fromRgb(0xE0A906)));

    preprocessorFormat.setFontWeight(QFont::Bold);
    preprocessorFormat.setFontItalic(true);

    preprocessorPatterns << "#if" << "#else" << "#include" << "#define"
                         << "#ifdef" << "#endif";

    foreach (const QString &pattern, preprocessorPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = preprocessorFormat;
        highlightingRules.append(rule);
    }

    //////

//    QStringList operatorPatterns;

//    operatorFormat.setForeground(QBrush(QColor::fromRgb(0xFF7B07)));

//    operatorPatterns << "\\b:" << "\\b+" << "\\b-" << "\\b==" << "\\b+=" << "\\b-="
//                     << "\\b!" << "\\b!=" << "\\b||" << "\\b&&" << "\\b|" << "\\b&"
//                     << "\\b|=" << "\\b&=" << "\\b?";

//    foreach (const QString &pattern, operatorPatterns)
//    {
//        rule.pattern = QRegExp(pattern);
//        rule.format = operatorFormat;
//        highlightingRules.append(rule);
//    }

    ///

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    tracePointFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("\\bTRACE_POINT+(?=\\()");
    rule.format = tracePointFormat;
    rule.id_rule = id_trace;
    highlightingRules.append(rule);

    rule.id_rule = 0;
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);



    multiLineCommentFormat.setForeground(Qt::darkGreen);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
 }

clang_trace_highlighter::~clang_trace_highlighter()
{

}

void clang_trace_highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0)
         {
             int end = 0; bool isTrace = false;
             QTextCharFormat fmt = rule.format;
             if (id_trace == rule.id_rule)
             {
                 end = text.indexOf(";", index);
                 int begin = text.indexOf("(", index);
                 QStringList trace_args = text.mid(begin+1, end-begin-2).split(",");
                 QString arg1 = trace_args.at(0);
                 if (!this->current_keyword_trace_point.isEmpty())
                     if (arg1.compare(this->current_keyword_trace_point) == 0)
                     {
                        fmt.setBackground(Qt::darkRed);
                        fmt.setForeground(Qt::white);
                        isTrace = true;
                     }
             }
             int length = expression.matchedLength();
             if (isTrace)
                setFormat(index, end - index, fmt);
             else
                setFormat(index, length, fmt);
             index = expression.indexIn(text, index + length);
         }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);
     while (startIndex >= 0)
     {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1)
         {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         }
         else
         {
             commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
}

void clang_trace_highlighter::sl_setter_current_keyword(QString keyword)
{
    this->current_keyword_trace_point = keyword;
}
