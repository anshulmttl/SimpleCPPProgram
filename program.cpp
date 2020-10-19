#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Compile : g++ program.cpp -o filename

const string eBadLineLength = "Error, maxLineLength must be a positive integer";
const string eNoCensorWord = "Error, missing censor word";
const string eCantOpenInputFile = "Error, could not open input file";

bool FileExists(std::string fileName)
{
	if(FILE *file = fopen(fileName.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

void ReplaceCensorWord(std::string &inputText, std::string censorWord)
{
	size_t pos = inputText.find(censorWord);
	size_t len = censorWord.length();
	if(pos == std::string::npos)
	{
		return;
	}
	inputText.replace(pos, len, "");
	
	ReplaceCensorWord(inputText, censorWord);
}

int main(int argc, char* argv[])
{
	std::string maxLineLength, censorWord = "", inputFile = "";
	bool fileInputted = false;
	std::string::size_type sz;
	std::string inputText, line;
	int maxLength = 20;
	for(int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if(arg == "-n")
		{
			maxLineLength = argv[i+1];
			try{
				maxLength = stoi(maxLineLength);
			}
			catch(...)
			{
				cout << eBadLineLength << endl;
				return 0;
			}
			++i;
		}
		else if(arg == "-c")
		{
			censorWord = argv[i+1];
			if(censorWord == "-n" || censorWord == "" || censorWord == "-c")
			{
				cout << eNoCensorWord << endl;
				return 0;
			}
			++i;
		}
		else
		{
			// Taking .\MyProgram also as command line argument
			fileInputted = true;
			inputFile = argv[i];
		}
	}
	
	// Getting input
	if(!fileInputted)
	{
		//cout << "File not inputted" << endl;
		// Read input from cin
		while(getline(cin, line))
		{
			if(line.empty())
			{
				break;
			}
			inputText += line;
			inputText += "\n";
		}
	}
	else
	{
		//cout << "File is inputted" << endl;
		// Read input from file
		if(FileExists(inputFile))
		{
			std::ifstream file(inputFile);
			while(getline(file, line))
			{
				inputText += line;
				inputText += "\n";
			}
		}
		else
		{
			cout << eCantOpenInputFile << endl;
		}
	}

	// Replacing censorword n number of times
	if(!(censorWord == ""))
	{
		ReplaceCensorWord(inputText, censorWord);
	}
	
	int j = 0;
	// Iterate char by char and print
	for(std::string::size_type i = 0; i < inputText.size(); ++i)
	{
		if(inputText[i] == '\n')
		{
			j = 1;
			cout << inputText[i];
			continue;
		}
		
		if((j % maxLength) == 0)
		{
			cout << endl;
			cout << inputText[i];
			//j = 0;
		}
		else
		{
			cout << inputText[i];
		}
		
		++j;
	}
	
}
