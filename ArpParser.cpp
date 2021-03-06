// ArpParser.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool outputParsedArpToConsole();

int main()
{
	std::string fileName = "";
	std::cout << "Enter the filename you will save this as: ";
	std::cin >> fileName;

	FILE *arpOutputFile;
	char cmdOutput[128];

	arpOutputFile = _popen("arp -a", "r");

	std::ofstream parsedArpOutputFile;
	parsedArpOutputFile.open(fileName + ".txt");
	parsedArpOutputFile << "\t\t--ARP Table Results--\n\n";
	parsedArpOutputFile << "\tIP\t\t\tMAC\t\tType\n";
	parsedArpOutputFile << "______________________________________________________\n\n";

	std::vector<char *> arrayOfIPAddresses;


	const char * substr1 = "In";
	const char * substr2 = "  In";
	const char * substr3 = "\n";

	while (std::fgets(cmdOutput, sizeof(cmdOutput), arpOutputFile) != NULL)
	{
		// Cuts out lines of output where cmd says "Interface" and "Internet address" as well as any spaces
		if ((strncmp(cmdOutput, substr1, strlen(substr1)) == 0) || 
			(strncmp(cmdOutput, substr2, strlen(substr2)) == 0) ||
			(strncmp(cmdOutput, substr3, strlen(substr3)) == 0)) 
		{
			// Uncomment next line to see listed interfaces
			//parsedArpOutputFile << cmdOutput << "\n";
			continue;
		}
		else {
			parsedArpOutputFile << cmdOutput << "\n";
			arrayOfIPAddresses.push_back(cmdOutput);
		}
	}

	parsedArpOutputFile.close();
	_pclose(arpOutputFile);


	if (outputParsedArpToConsole() == true) {
		system("cls");
		std::ifstream readFile;
		readFile.open(fileName + ".txt");
		std::string i;
		while (std::getline(readFile, i)) {
			std::cout << i << std::endl;
		}

		readFile.close();
	}
	else {
		system("cls");
		std::cout << "You can find the file created listed as " << fileName << ".txt\n\n" << std::endl;
	}

	return 0;
}

bool outputParsedArpToConsole() {

	char showFile;
	std::cout << "Do you want to see the current contents of the file? (y/n)" << std::endl;
	std::cin >> showFile;

	showFile = std::tolower(showFile);

	if (showFile == 'y') {
		return true;
	}
	else if (showFile == 'n') {
		return false;
	}

	while (showFile != 'y' && showFile != 'n') {
		std::cout << "Do you want to see the current contents of the file? (Y/n)" << std::endl;
		std::cin >> showFile;

		if (showFile == 'y') {
			return true;
		}
		else if (showFile == 'n') {
			return false;
		}
	}
}