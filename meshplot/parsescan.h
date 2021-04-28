/*
 * parsescan.h
 *
 *  Created on: Apr. 13th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *  	Definitions for the cooperation of bison and flex
 *
 */

#ifndef PARSESCAN_H_
#define PARSESCAN_H_

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

class MeshScanner : public yyFlexLexer {
public:
	symbol_type yylex(int);
};


#endif /* PARSESCAN_H_ */
