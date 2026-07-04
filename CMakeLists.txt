cmake_minimum_required(VERSION 3.21)
project(FluidDAW VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# JUCE Framework Setup
# ============================================================================
add_subdirectory(ThirdParty/JUCE)

# ============================================================================
# Audio Engine Library (Core)
# ============================================================================
add_library(FluidAudioEngine
    Source/Audio/AudioEngine.cpp
    Source/Audio/AudioEngine.h
    Source/Audio/ProcessorGraph.cpp
    Source/Audio/ProcessorGraph.h
    Source/Audio/Transport.cpp
    Source/Audio/Transport.h
)

target_include_directories(FluidAudioEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_link_libraries(FluidAudioEngine PUBLIC
    juce::juce_audio_devices
    juce::juce_audio_processors
    juce::juce_core
)

# ============================================================================
# Main Application
# ============================================================================
juce_add_gui_app(FluidDAW
    PRODUCT_NAME "Fluid DAW"
)

target_sources(FluidDAW PRIVATE
    Source/Main.cpp
    Source/MainWindow.cpp
    Source/MainWindow.h
    Source/UI/MainComponent.cpp
    Source/UI/MainComponent.h
)

target_include_directories(FluidDAW PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_link_libraries(FluidDAW PRIVATE
    FluidAudioEngine
    juce::juce_gui_extra
    juce::juce_audio_devices
    juce::juce_audio_processors
    juce::juce_core
)

# ============================================================================
# Platform-Specific Settings
# ============================================================================
if(APPLE)
    set_target_properties(FluidDAW PROPERTIES
        MACOSX_BUNDLE YES
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.fluidaudio.daw"
        MACOSX_BUNDLE_BUNDLE_NAME "Fluid DAW"
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1.0"
    )
elseif(WIN32)
    set_target_properties(FluidDAW PROPERTIES
        VS_STARTUP_PROJECT FluidDAW
    )
endif()

# ============================================================================
# Copy Resources (if any)
# ============================================================================
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
    add_custom_command(TARGET FluidDAW POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:FluidDAW>/Resources"
    )
endif()
