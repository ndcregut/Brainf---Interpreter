#include <iostream>	// For usual input/output
#include <cstdlib>	// For exit function
#include <fstream>	// For file manipulation

using namespace std;

int main(int argc, char const *argv[])
{
	
	// Check to make sure there are two arguments
	if (argc != 2) { 
		// If not, report error and quit application
		cout << "Correct usage of this program is ./<executable> <bftextdoc>.txt"
			<< endl
			<< "Quitting program." << endl;
		exit(EXIT_FAILURE);
	}

	// Open file for reading
	ifstream ifs(argv[1]);
	// If file does not open correctly output error and quit application
	if (!ifs.is_open()){
		cout << "File does not exist, quitting program." << endl;
		exit(EXIT_FAILURE);
	}

	// declare variables
	int bytes[100] = {0};	// Store values for each byte
	int bitIndex = 0;		// Keep track of where we are in bytes array
	int loop[100] = {0};	// Keep track of how many times we are looping through a while
							// Used for multiplying addition in a while loop
	int loopIndex = 0;		// Keep track of where we are in the loop array
	int loopstarter[100] = {-1}; // Used to keep track which byte starts a loop
	int addsub = 0;			// Used to keep track of how many numbers we are adding/subtracting
	int loops = 0;          // Used to keep track of how many loops are happening in outer loop
	bool flag = true;		// Used to keep track of whether or not we get another character
							// At the end of the while loop

	// Grab first character from file
	int c = ifs.get();

	// continue to run until reached end of file
	while (c != EOF) {
		flag = true;
		
		// Check if we are adding
		if (c == '+') {
			// add to addsub
			addsub++;

			// Continue to add to addsub while continuing to
			// read in '+'
			while (((c = ifs.get()) != EOF) && c == '+') {
				addsub++;
			}

			// Check if we are currently in a loop
			if (loop[loopIndex] > 0) {
				// If so multiply addsub by the times we would loop
				addsub *= loop[loopIndex];
				if (loopstarter[loopIndex] != bitIndex && loops < 3) {
					for (int i = loopIndex-1; i >= 0; i--) {
						// Multiply for every loop we are currently
						// Inside of
						addsub *= loop[i];
					}
				}
				
			}

			bytes[bitIndex] += addsub;
			// Print out current index, what we added and new value
			cout << "Index " << bitIndex << ", added " << addsub
				<< ", final value : " << bytes[bitIndex] << endl;

			// Reset addsub
			addsub = 0;

		} else if (c == '-') {
			addsub++;

			// Continue to add to addsub while continuing to
			// read in '-'
			while (((c = ifs.get()) != EOF) && c == '-') {
				addsub++;
			}
			
			// Check if we are currently in a loop
			if (loop[loopIndex] > 0) {
				// If so multiply addsub by the times we would loop
				addsub *= loop[loopIndex];
				if (loopstarter[loopIndex] != bitIndex && loops < 3) {
					for (int i = loopIndex-1; i >= 0; i--) {
						// Multiply for every loop we are currently
						// Inside of
						addsub *= loop[i];
					}
				}
					

			}

			bytes[bitIndex] -= addsub;
			// Print out current index, what we subtracted and new value
			cout << "Index " << bitIndex << ", subtracted " << addsub
				<< ", final value : " << bytes[bitIndex] << endl;

			// Reset addsub
			addsub = 0;

		} else if (c == '>') {
			bitIndex++;

			while (((c = ifs.get()) != EOF) && c == '>') {
				// add to bitIndex
				bitIndex++;
			}
			cout << "Moved to index " << bitIndex << endl;

		} else if (c == '<') {
			flag = false;
			bitIndex--;
			while (((c = ifs.get()) != EOF) && c == '<') {
				// add to bitIndex
				bitIndex--;
			}
			cout << "Moved to index " << bitIndex << endl;

		// These cases require retrieving an extra character
		} else {
			// Check to see if starting loop
			if (c == '[') {
				loops++;
				// Check to see if we are already in a loop
				if (loop[loopIndex] > 0) {
					if (loops > 2) {
						bytes[bitIndex] /= loop[loopIndex];
						cout << "Fixed loop bit number to correct loop count" << endl
							<< "Index " << bitIndex << " is now " << bytes[bitIndex] << endl;
					}
					//Add to loopIndex
					loopIndex++;
					//Set loop[loopIndex] to current index
					loop[loopIndex] = bytes[bitIndex];
					loopstarter[loopIndex]= bitIndex;
				} else {
					//Set loop[loopIndex] to current index
					loop[loopIndex] = bytes[bitIndex];
				}
				// Print out that we started loop [current index] times
				cout << "Started a while for " << bytes[bitIndex] << " loops."
					<< endl;

			// Check to see if ending while loop
			} else if (c == ']') {
				// check to see if we were in any other loops
				if (loopIndex > 0) {
					loop[loopIndex] = 0;
					// Reset loopstarter at current index
					loopstarter[loopIndex] = -1;
					//Subtract loopIndex
					loopIndex--;

				} else {
					loop[loopIndex] = 0;
					loops = 0;
					loopstarter[loopIndex] = -1;
				}
				
				//Print out that we ended a loop
				cout << "Exited while loop." << endl;

			// Check to see if printing to console
			} else if (c == '.') {
				// Print out what we are printing
				cout << "Printing to console : '" 
					<< (char)bytes[bitIndex] << "'" << endl;
					
			} else if (c == ',') {
				// State that inputs are represented as 100
				cout << "Asking for input from user" << endl
					<< "Input is handled as '10'" << endl;
					bytes[bitIndex] = 10;
			}

			// Retrieve another character from file
			c = ifs.get();
		}
	}

	return 0;

}
