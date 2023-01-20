#include "AudioSubsystem.h"

AudioSubsystem::AudioSubsystem()
{
}

void AudioSubsystem::UpdateSubsystem()
{
	// Make sure you update the audio to be sure that it gets played correctly
	//system->update();
}

void AudioSubsystem::InitAudio()
{	
	/*
	// Initialize a pointer to Studio::System, to create the beggining of our audio. Afterwards get some confirmation that it is successful
	FMOD::Studio::System::create(&system);
	
	if (&system) {
		std::cout << "High-level (fmod studio) audio system created." << "\n";
	}

	// Once created, we make a pointer and bind it to the studio system, making a print to the console to make sure it was succesfful
	system->getLowLevelSystem(&lowLevelSystem);

	if (lowLevelSystem) {
		std::cout << "Low-level (fmod) audio system created." << "\n";
	}

	// We stipulate the speaker mode from stereo to surround and then we initialize our Studio System
	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);

	// Now we create a sound pointer and set it to NULL. Once created we use the createSound function to read in a .wav file and bind it to the pointer.

	lowLevelSystem->createSound("data/assets/audios/meow.wav", FMOD_LOOP_OFF, NULL, &mySound);

	if (&mySound) {	// If sound exists, print confirmation
		std::cout << "Sound loaded." << "\n";
	}

	// You can use the next line to change the sound frequency or if you want it to play faster or slower
	mySound->setDefaults(16400, 0);	
	*/
}

void AudioSubsystem::PlayAudio()
{
	//lowLevelSystem->playSound(mySound, NULL, false, &soundChannel);
}