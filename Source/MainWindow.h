#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "UI/MainComponent.h"

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow(const juce::String& name);
    ~MainWindow() override;

    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
