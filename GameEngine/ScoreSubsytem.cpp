#pragma once
#include "ScoreSubsystem.h"


// Constuctors
ScoreSubsystem::ScoreSubsystem() 
{
	this->score = 0;
	this->path = "";
}

// Destructor
ScoreSubsystem::~ScoreSubsystem()
{

}


// Functions
void ScoreSubsystem::InitScore(std::string path)	// Creates the scores file, if it doesn't exist, in the path in order to save the scores
{
	myFile.open(path);
	if (!myFile) {	// If file doesn't exist, create a new one
		std::cout << "File doesn't exist. Creating new file...\n";
		myFile.open(path, std::ios::out | std::ios::app);
		myFile << "\n";
		myFile.close();
		std::cout << "File created successfully\n";
	}
	myFile.close();	// Close the file so we can open it in append mode
}

void ScoreSubsystem::UpdateSubsystem()
{
	// The bigger the score the worst, we want to get the lowest score since it represents time elapsed
	score += 1;
}

// Saves the current run score when called (I tried to make order all the scores, but couldn't get to convert the string to int)
void ScoreSubsystem::SaveScore(std::string path, u32 deltaTime)
{	
	std::vector<std::pair<std::string, std::string>> wordValue;

	std::string word;
	std::string value;

	std::ifstream file(path);

	for (std::string line; getline(file, line);)	// For each line
	{
		for (int i = 0; i < line.size(); i++)	// for each character in current line
		{
			if(std::isdigit(line[i]))	// If text is a number push into value variable
			{
				value.push_back(line[i]);
			}
			else	// If text is text push it into a string variable
			{
				word.push_back(line[i]);
			}
		}

		wordValue.emplace_back(word, value);	// Placing all the score as key : values
		
		// NEED TO CONVERT FROM INT TO STRING
		//std::cout << std::stoi(value);

		/*for (int i = 0; i < wordValue.size(); i++) {	// Ordering scores
			for (int j = 0; j < wordValue.size(); i++)
			{
				if (wordValue[j].second > wordValue[i].second) 
				{
					wordValue[i] = wordValue[j];
				}
			}
			std::cout << wordValue[i].first << wordValue[i].second << "\n";
		}*/

		word = "";
		value = "";		
	}

	// Function is called when engine closes to save the current score
	myFile.open(path, std::ios_base::app);	// Open the file in append mode
	myFile << "Score: " << score << "<br>\n";
	myFile.close();
	std::cout << "Score saved successfully\n";
	std::cout << "Time: " << deltaTime;
}

