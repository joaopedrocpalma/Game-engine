#pragma once
#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include "Engine.h"

class AudioSubsystem
{
	// Sound variables
	// Complaining about unresolved external symbols, I think its a linking problem
	FMOD::Studio::System* system = NULL;
	FMOD::System* lowLevelSystem = NULL;
	FMOD::Sound* mySound = NULL;
	FMOD::Channel* soundChannel = NULL;

public:
	AudioSubsystem();

	virtual void InitAudio();
	virtual void UpdateSubsystem();
	virtual void PlayAudio();
};