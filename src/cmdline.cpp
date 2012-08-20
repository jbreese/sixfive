#include "cmdline.h"

namespace cmdline {

std::vector<Argument> options;

int argIndex;
std::vector<Argument> arguments;

bool (*argHandler)(std::vector<Argument> *);

bool registerOption( Argument a ) {
	if ( a.sOpt.compare( "" ) == 0 ) {
		arguments.push_back( a );
		return true;
	} else {
		options.push_back( a );
		return true;
	}
	return false;
}

bool registerArgHandler( bool (*handler)(std::vector<Argument> *) ) {
	argHandler = handler;
	return true;
}

bool parse( int argc, char *argv[] ) {
	for ( int i = 0; i < argc; i++ ) { 
	
		char *next;
		int ix = i;
		bool invalid = false;
		if ( i < argc - 1 )
			next = argv[i+1];
		char *p = strstr(argv[i], "--");
		char *q = strstr(argv[i], "-");
		
		if ( p == argv[i] ) {
			// Long option
			p += 2;
			for (unsigned int j = 0; j < options.size(); j++) {
				if (options[j].lOpt.compare(p) == 0) {
					if (options[j].hasValue) {
						options[j].value = std::string(next);
						i++;
					}
					options[j].callback(&options[j]);
					break;
				}
			}
		} else if ( q == argv[i] ) {
			// Short option
			q += 1;
			for (unsigned int j = 0; j < options.size(); j++) {
				if (options[j].sOpt.compare(q) == 0) {
					if (options[j].hasValue) {
						options[j].value = std::string(next);
						i++;
					}
					options[j].callback(&options[j]);
					break;
				}
			}
		} else {
			arguments.push_back( (Argument){
				std::string( "" ),
				std::string( "" ),
				true,
				std::string( argv[i] ),
				NULL} );
		}
	
		if ( invalid ) {
			std::cout << "Invalid argument: " << argv[ix] << std::endl;
			return false;
		}
		
		}
		if ( argHandler( &arguments ) ) return true;
	
		return false;
	}

}
