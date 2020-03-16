#include "./pi.cpp"

#include <string.h>
#include <stdio.h>
#include <iostream>

int arg = 1;
bool got_subcommand = false;

bool break_line = true; // Should I add a line break?
unsigned char base_radix; // Radix
char base_digits[64] = {
	// Base Digit Set
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z', '$', '&'
};

int processIndex(int index, int size) {
	// Processes start and end indexes.
	if (index < 0)
		return "%i", index < -size ? 0 : size + index;
	return index > size ? size : index;
}

int main(int argc, char *argv[]) {
	// Iterate over the arguments and process them.
	for (; arg < argc; ++arg) {
		if (argv[arg][0] == '-') {
			// This is an option.
			switch (argv[arg][1]) {
				case 'n':
				break_line = false;
				break;
			}
		} else {
			// This is the subcommand.
			got_subcommand = true;

			if (!strcmp(argv[arg], "symbol")) {
				// The user has requested the Pi Symbol.
				std::cout << "π";
				arg = argc;
			} else if (!strcmp(argv[arg], "dump")) {
				// The user has requested the raw bytes of Pi.
				break_line = false;

				signed int index = 0;
				signed int end_index = pi::SIZE;

				if (argc - arg == 2) {
					// The user specified an end index but no start index.
					sscanf(argv[++arg], "%u", &end_index);
				} else if (argc - arg > 2) {
					// The user specified both start and end indexes.
					sscanf(argv[++arg], "%u", &index);
					sscanf(argv[++arg], "%u", &end_index);
				}

				// Squish the indexes into an acceptable range.
				index = processIndex(index, pi::SIZE);
				end_index = processIndex(end_index, pi::SIZE);

				// Output each internally stored byte of Pi.
				for (; index < end_index; ++index)
					std::cout << pi::pi[index];
			} else if (!strcmp(argv[arg], "pi")) {
				std::cerr << "I'll do it later--promise.\n";
				return 1;
			} else {
				std::cerr << "Unknown subcommand: " << argv[arg] << "\nConsult the manual for help.\n";
				return 2;
			}

			// Break the line at the end of the output.
			if (break_line)
				std::cout << '\n';
		}
	}

	if (!got_subcommand) {
		std::cerr << "No subcommand specified.\nConsult the manual for help.\n";
		return 2;
	}

	return 0;
}
