/*
 *  meshscanner.l
 *
 *  Created on: Apr. 12th, 2021
 *      Author: Dr. R. Poller
 *
 *  Synopsis
 *  	flex lexical analyser definition file for processing FE mesh data
 *
 *	flex version: 2.6.4
 */
 
%option c++
%option noyywrap
%option yylineno

/*
 * The option noyywrap means that only one file will be processed
 * at a time.
 *
 * The option yylineno makes the declaration and follow-up of a
 * variable recording the current line number of the input unnecessary.
 *
 */

%{

#include "meshplot.h"
#include "meshparser.tab.hpp"
#include "parsescan.h"

/*
 * The macro YY_DECL determines the signature of the lexer (yylex()).
 *
 * It is relaced by its content in the file lex.yy.cc so that it will
 * be the heading line of the corresponding member function of the
 * class indicated in the macro definition.
 *
 * Without the definitio below, the signature of yylex() will be the
 * default
 *
 *		int yyFlexLexer::yylex(void)
 *
 */

#define YY_DECL int MeshScanner::yylex(yy::parser::semantic_type *yylval)

using token = yy::parser::token;

%}

WSPC		[ \t]

EOLN		\r\n

REALNUM		[+-]?[0-9]*"."[0-9]*([+-]?[eE][0-9]+)?
POSINT		[1-9][0-9]*

LINE_COMMENT	"//".*{EOLN}
BLOCK_COMMENT	"/*"(.|{EOLN})*"*/"

NODESET_BEGIN	^"*nodes"{WSPC}*{EOLN}
ELEMSET_BEGIN	^"*elements"{WSPC}*{EOLN}
SET_END			^"*end"{WSPC}*{EOLN}

%%

{LINE_COMMENT}

{BLOCK_COMMENT}

{NODESET_BEGIN}	return token::NODESET_BEGIN;

{ELEMSET_BEGIN}	return token::ELEMSET_BEGIN;
			
{SET_END}		return token::SET_END;

{REALNUM}		{ yylval->realval = atof(yytext);
			  	  return token::COORD; }

{POSINT}		{ yylval->label = atoi(yytext);
			  	  return token::LABEL; }

{WSPC}+

{EOLN}			return token::EOLN;

.				return token::CHAR;

%%

/*
	The definition of the virtual function int yylex()
	of class yyFlexLexer declared in <FlexLexer.h>
	
	Its content is irrelevant since the yylex() function
	defined by YY_DECL above will be used instead.
	
*/

int yyFlexLexer::yylex(void) {
	return 0;
}
