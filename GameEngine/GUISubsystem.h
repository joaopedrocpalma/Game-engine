#pragma once
#include "irrlicht.h"
#include "driverChoice.h"
#include "IAttributeExchangingObject.h"
#include "ScoreSubsystem.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/// <summary>
/// Responsible for displaying any GUI
/// </summary>

class GUISubsystem
{
    // Private variables
    IGUIFont* font;
    IrrlichtDevice* device;
    video::IVideoDriver* driver;
    IGUIEnvironment* env;
    IGUISkin* skin;
    IGUIStaticText* tBoxText;

public:
    // Constructors
    GUISubsystem();

    // Destructors
    virtual void InitGUI(IrrlichtDevice* device);
    virtual void UpdateSubsystem();
    virtual void SetFont(std::string* path);
    virtual void AddStaticText(wchar_t myText[]);
    virtual void AddStaticText();
    virtual void AddImage(std::string* text);
};

