/*
 * fproto.c
 * a quick look what prototypes are allowed
 * last update:
 *	4 sep 2021 -bjr: created
 * 
 */

int f(int) ;	// names are not needed
int g(int x) ;	// if a  name is included, another name can be used later

int f(int i ) { return i ; }
int g(int y) { return y ; }
int main(int argc, char * argv[]) { return 0 ; }

