#include <juce_gui_extra/juce_gui_extra.h>
#include "MainWindow.h"

class FluidDAWApplication : public juce::JUCEApplication
{
public:
    FluidDAWApplication() {}

    const juce::String getApplicationName() override { return "Fluid DAW"; }
    const juce::String getApplicationVersion() override { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String& commandLine) override
    {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted(const juce::String& commandLine) override
    {
        // Handle another instance launched
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(FluidDAWApplication)
