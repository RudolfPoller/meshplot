/*
 * ansparsescan.h
 *
 *  Created on: Apr. 28th, 2021
 *      Author: Dr. Rudolf Poller
 *
 *  Task
 *  	Definitions for the cooperation of bison and flex
 *
 */

#ifndef ANSPARSESCAN_H_
#define ANSPARSESCAN_H_

#include <string>

/*
 * The purpose of the class MeshScanner below is to allow
 * for the usage of yylex with other signature than
 * int yylex(void) made possible by bison.
 *
 * In the definition of the class below, the original virtual
 * function of yylex as a member of yyFlexLexer given in
 * <FlexLexer.h> is hidden by the new declaration.
 *
 */

class ansMeshScanner : public ansFlexLexer {
public:
	ans::parser::symbol_type anslex(int);
};


/*
 * Override of the function `int ansFlexLexer::yylex(void)'.
 * This function is not used.
 * Rem.: bison renames yylex to anslex
 */

int ansFlexLexer::yylex(void) {
	return 0;
}


#endif /* ANSPARSESCAN_H_ */
