#include <iostream>	
#include "mergeBed.h"

using namespace std;

// define our program name
#define PROGRAM_NAME "mergeBed"

// define the version
#define VERSION "1.1.0"

// define our parameter checking macro
#define PARAMETER_CHECK(param, paramLen, actualLen) (strncmp(argv[i], param, min(actualLen, paramLen))== 0) && (actualLen == paramLen)

// function declarations
void ShowHelp(void);

int main(int argc, char* argv[]) {

	// our configuration variables
	bool showHelp = false;

	// input files
	string bedFile;
	int maxDistance = 0;

	// input arguments
	bool numEntries = false;
	bool haveMaxDistance = false;
	bool haveBed = false;

	// check to see if we should print out some help
	if(argc <= 1) showHelp = true;

	for(int i = 1; i < argc; i++) {
		int parameterLength = (int)strlen(argv[i]);

		if(PARAMETER_CHECK("-h", 2, parameterLength) || 
		PARAMETER_CHECK("--help", 5, parameterLength)) {
			showHelp = true;
		}
	}

	if(showHelp) ShowHelp();

	// do some parsing (all of these parameters require 2 strings)
	for(int i = 1; i < argc; i++) {

		int parameterLength = (int)strlen(argv[i]);

 		if(PARAMETER_CHECK("-i", 2, parameterLength)) {
			haveBed = true;
			bedFile = argv[i + 1];
			i++;
		}
		else if(PARAMETER_CHECK("-n", 2, parameterLength)) {
			numEntries = true;
			i++;
		}
                else if(PARAMETER_CHECK("-d", 2, parameterLength)) {
		  haveMaxDistance = true;
		  maxDistance = atoi(argv[i + 1]);
		  i++;
                }
		else {
		  cout << endl << "*****ERROR: Unrecognized parameter: " << argv[i] << " *****" << endl << endl;
			showHelp = true;
		}		
	}

	// make sure we have both input files
	if (!haveBed) {
	  cout << endl << "*****" << endl << "*****ERROR: Need -i BED file. " << endl << "*****" << endl;
	  showHelp = true;
	}
	
	if (!showHelp) {
	  BedMerge *bm = new BedMerge(bedFile, numEntries, maxDistance);
		bm->MergeBed();
		return 0;
	}
	else {
		ShowHelp();
	}
}

void ShowHelp(void) {
	
	cout << "=======================================================" << endl;
	cout << PROGRAM_NAME << " v" << VERSION << endl ;
	cout << "Aaron Quinlan, Ph.D." << endl;
	cout << "aaronquinlan@gmail.com" << endl ;
	cout << "Hall Laboratory" << endl;
	cout << "Biochemistry and Molecular Genetics" << endl;
	cout << "University of Virginia" << endl; 
	cout << "=======================================================" << endl << endl;
	cout << "Description: Merges overlapping bed entries into a sinle interval." << endl << endl;
	cout << "***NOTE: Only BED3 - BED6 formats allowed.***"<< endl << endl;

	cout << "Usage: " << PROGRAM_NAME << " [OPTIONS] -i <input.bed>" << endl << endl;
	
	cout << "OPTIONS: " << endl;
	cout << "\t" << "-n\t\t\t"	<< "Report the number of BED entries that were merged. (=1 if no merging occured)" << endl << endl;
	cout << "\t" << "-d\t\t\t"      << "Maximum distance between features allowed for features to be merged. (Default=0)" << endl << endl;
	// end the program here
	exit(1);
	
}
