#include <iostream>
#include "config.hpp"
#include "logger.hpp"

int main() {
    // Load existing config or use defaults
    if (!config.LoadFromFile("user_settings.json")) {
        LOG_WARNING("Using default settings");
    }

    // Access and modify settings
    bool fullscreen = config.GetSetting<bool>("Graphics", "FullScreen");
    LOG_INFO("Fullscreen mode: " + std::string(fullscreen ? "On" : "Off"));

    config.SetSetting("Graphics", "Resolution", "2560x1440");
    config.SetSetting("Audio", "MasterVolume", 0.9f);

    // Print all settings
    LOG_INFO("Current Settings:");
    config.PrintSettings();

    // Save modified settings
    config.SaveToFile("user_settings.json");
    config.SaveToFile("user_settings_backup.json");

    // List all config files
    auto configFiles = config.ListConfigs();
    LOG_INFO("Available config files:");
    for (const auto& file : configFiles) {
        LOG_INFO("- " + file);
    }

    // Delete a config file
    if (config.DeleteConfigFile("user_settings.json")) {
        LOG_INFO("Config file 'user_settings.json' deleted successfully");
    } else {
        LOG_ERROR("Failed to delete config file 'user_settings.json'");
    }

    // List all config files again
    configFiles = config.ListConfigs();
    LOG_INFO("Available config files after deletion:");
    for (const auto& file : configFiles) {
        LOG_INFO("- " + file);
    }

    // Pause before exit
    get_user_input("Press Enter to continue...");
    return 0;
}
