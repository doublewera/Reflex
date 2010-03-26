/****************************************************************************
**
** Copyright (C) Trolltech Hren Trolltech. Too many goto ;)
** Edited by Wera O. Barinova 2009
**
** This file WAS part of the QtGui module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#

static inline bool isHexDigit(const char c)
{
    return (c >= '0' && c <= '9')
           || (c >= 'a' && c <= 'f')
           || (c >= 'A' && c <= 'F')
           ;
}

//QLatin1Char('\\')
//skipSpace();

bool Parser::parseFunction(QString *name, QString *args)
{
    *name = lexem();
    name->chop(1);
    skipSpace();
    const int start = index;
    if (!until(RPAREN)) return false;
    for (int i = start; i < index - 1; ++i)
        args->append(symbols.at(i).lexem());
    /*
    if (!nextExpr(&arguments)) return false;
    if (!next(RPAREN)) return false;
    */
    skipSpace();
    return true;
}

bool Parser::parseHexColor(QColor *col)
{
    col->setNamedColor(lexem());
    if (!col->isValid()) return false;
    skipSpace();
    return true;
}

bool Parser::testAndParseUri(QString *uri)
{
    const int rewind = index;
    if (!testFunction()) return false;

    QString name, args;
    if (!parseFunction(&name, &args)) {
        index = rewind;
        return false;
    }
    if (name.toLower() != QLatin1String("url")) {
        index = rewind;
        return false;
    }
    *uri = args;
    removeOptionalQuotes(uri);
    return true;
}

bool Parser::testSimpleSelector()
{
    return testElementName()
           || (test(HASH))
           || testClass()
           || testAttrib()
           || testPseudo();
}

bool Parser::next(TokenType t)
{
    if (hasNext() && next() == t)
        return true;
    return recordError();
}

bool Parser::test(TokenType t)
{
    if (index >= symbols.count())
        return false;
    if (symbols.at(index).token == t) {
        ++index;
        return true;
    }
    return false;
}

QString Parser::unquotedLexem() const
{
    QString s = lexem();
    if (lookup() == STRING) {
        s.chop(1);
        s.remove(0, 1);
    }
    return s;
}

QString Parser::lexemUntil(TokenType t)
{
    QString lexem;
    while (hasNext() && next() != t)
        lexem += symbol().lexem();
    return lexem;
}

bool Parser::until(TokenType target, TokenType target2)
{
    int braceCount = 0;
    int brackCount = 0;
    int parenCount = 0;
    if (index) {
        switch(symbols.at(index-1).token) {
        case LBRACE: ++braceCount; break;
        case LBRACKET: ++brackCount; break;
        case FUNCTION:
        case LPAREN: ++parenCount; break;
        default: ;
        }
    }
    while (index < symbols.size()) {
        TokenType t = symbols.at(index++).token;
        switch (t) {
        case LBRACE: ++braceCount; break;
        case RBRACE: --braceCount; break;
        case LBRACKET: ++brackCount; break;
        case RBRACKET: --brackCount; break;
        case FUNCTION:
        case LPAREN: ++parenCount; break;
        case RPAREN: --parenCount; break;
        default: break;
        }
        if ((t == target || (target2 != NONE && t == target2))
            && braceCount <= 0
            && brackCount <= 0
            && parenCount <= 0)
            return true;

        if (braceCount < 0 || brackCount < 0 || parenCount < 0) {
            --index;
            break;
        }
    }
    return false;
}

bool Parser::testTokenAndEndsWith(TokenType t, const QLatin1String &str)
{
    if (!test(t)) return false;
    if (!lexem().endsWith(str, Qt::CaseInsensitive)) {
        prev();
        return false;
    }
    return true;
}
