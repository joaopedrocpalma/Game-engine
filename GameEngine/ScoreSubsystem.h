#pragma once
#include <fstream>
#include <iomanip>
#include "Engine.h"

/// <summary>
/// Score subsystem
/// Creates / Edits a scoreboard in a .html file
/// Updates the score over each update loop
/// </summary>

class ScoreSubsystem 
{
	// Private variables
	int score;
	std::string path;
	std::fstream myFile;

public:
	// Constructors / Destructors
	ScoreSubsystem();
	~ScoreSubsystem();

	// Functions
	virtual void InitScore(std::string path);
	virtual void UpdateSubsystem();
	virtual void SaveScore(std::string path, u32 deltaTime);
};
