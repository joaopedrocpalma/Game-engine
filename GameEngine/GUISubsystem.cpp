#pragma once
#include "GUISubsystem.h"

GUISubsystem::GUISubsystem()
{
}

// Initializing some needed variables
void GUISubsystem::InitGUI(IrrlichtDevice* device)
{
	this->device = device;
	this->driver = device->getVideoDriver();
	this->env = device->getGUIEnvironment();
	this->skin = env->getSkin();
}

void GUISubsystem::UpdateSubsystem()
{
	this->env->drawAll();
}

// Gets the font from specified path and applies it to the gui font, as well as set it as default font in the skin
void GUISubsystem::SetFont(std::string* path)
{
	this->font = env->getFont(&path);

	if (font)
		this->skin->setFont(font);

	this->skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
}

// Default function for showing text on preset location
void GUISubsystem::AddStaticText(wchar_t myText[])
{	
	// How  addStaticText works: text, position / size, border, wordwrap
	// coords[x - horizontal position on screen, y - vertical position, x2 - width of textbox, y2 - height of textbox]
	tBoxText = env->addStaticText(L"", rect<s32>(600, 10, 800, 50), false);
	tBoxText->setText(myText);
	
}

// This function allows you to select where you want the text to appear on screen
void GUISubsystem::AddStaticText()
{
	tBoxText = env->addStaticText(L"Hardcode text here: ", rect<s32>(600, 10, 1000, 200), false);
	//this->env->addStaticText(*text, rect<s32>(150,20,350,40), true);
}

void GUISubsystem::AddImage(std::string* path)
{
}