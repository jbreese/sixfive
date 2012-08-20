#include "cmdline.h"

#include <string>

using namespace std;

bool setArchitecture( cmdline::Argument * );

int main( int argc, char** argv ) {

	// Set up command-line arguments
	cmdline::registerOption( (cmdline::Argument){
			string( "a" ), string( "arch" ),				// -a or --arch
			true, "",										// associated arg
			&setArchitecture								// callback function
		} );
	cmdline::parse( argc, argv );

    return 0;
}

bool setArchitecture( cmdline::Argument *arg ) {
	
	return true;
}
