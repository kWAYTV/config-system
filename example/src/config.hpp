#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include "logger.hpp"

using json = nlohmann::json;

class Config {
public:
    // Singleton instance getter
    static Config& Get() {
        static Config instance;
        return instance;
    }

    // Register a setting with a default value
    template<typename T>
    void RegisterSetting(const std::string& section, const std::string& key, T defaultValue) {
        settings[section][key] = defaultValue;
    }

    // Get a setting value
    template<typename T>
    T GetSetting(const std::string& section, const std::string& key) const {
        return settings.at(section).at(key).get<T>();
    }

    // Set a setting value
    template<typename T>
    void SetSetting(const std::string& section, const std::string& key, const T& value) {
        settings[section][key] = value;
    }

    // Load settings from a file
    bool LoadFromFile(const std::string& filename) {
        std::filesystem::path configPath = GetConfigDirectory() / filename;
        std::ifstream file(configPath);
        if (!file.is_open()) {
            LOG_ERROR("Could not open config file: " + configPath.string());
            return false;
        }

        try {
            json loadedSettings = json::parse(file);
            MergeSettings(loadedSettings);
            LOG_INFO("Loaded config from file: " + configPath.string());
            return true;
        }
        catch (json::parse_error& e) {
            LOG_ERROR("JSON parse error in config file: " + std::string(e.what()));
            return false;
        }
    }

    // Save settings to a file
    bool SaveToFile(const std::string& filename) const {
        std::filesystem::path configPath = GetConfigDirectory() / filename;
        std::ofstream file(configPath);
        if (!file.is_open()) {
            LOG_ERROR("Could not open file for saving: " + configPath.string());
            return false;
        }

        file << settings.dump(4);
        LOG_INFO("Config saved successfully to file: " + configPath.string());
        return true;
    }

    // List all config files in the config directory
    std::vector<std::string> ListConfigs() const {
        std::vector<std::string> configs;
        for (const auto& entry : std::filesystem::directory_iterator(GetConfigDirectory())) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                configs.push_back(entry.path().filename().string());
            }
        }
        return configs;
    }

    // Delete a config file
    bool DeleteConfigFile(const std::string& filename) {
        std::filesystem::path configPath = GetConfigDirectory() / filename;
        if (std::filesystem::remove(configPath)) {
            LOG_INFO("Config file deleted successfully: " + configPath.string());
            return true;
        }
        else {
            LOG_ERROR("Failed to delete config file: " + configPath.string());
            return false;
        }
    }

    // Print all current settings (for debugging)
    void PrintSettings() const {
        LOG_INFO(settings.dump(4));
    }

private:
    Config() {
        EnsureConfigDirectoryExists();
        RegisterDefaultSettings();
    }

    std::filesystem::path GetConfigDirectory() const {
        return std::filesystem::current_path() / "configs";
    }

    void EnsureConfigDirectoryExists() {
        std::filesystem::path configDir = GetConfigDirectory();
        if (!std::filesystem::exists(configDir)) {
            try {
                std::filesystem::create_directory(configDir);
                LOG_INFO("Created config directory: " + configDir.string());
            } catch (const std::filesystem::filesystem_error& e) {
                LOG_ERROR("Failed to create config directory: " + std::string(e.what()));
            }
        }
    }

    void RegisterDefaultSettings() {
        // Example default settings
        RegisterSetting("Graphics", "Resolution", std::string("1920x1080"));
        RegisterSetting("Graphics", "FullScreen", true);
        RegisterSetting("Graphics", "VSync", false);
        RegisterSetting("Graphics", "AntiAliasing", 4);

        RegisterSetting("Audio", "MasterVolume", 0.8f);
        RegisterSetting("Audio", "MusicVolume", 0.5f);
        RegisterSetting("Audio", "SFXVolume", 0.7f);

        RegisterSetting("Gameplay", "Difficulty", std::string("Normal"));
        RegisterSetting("Gameplay", "AutoSave", true);
        RegisterSetting("Gameplay", "ShowTutorials", true);

        // Add more default settings as needed
    }

    void MergeSettings(const json& loadedSettings) {
        for (auto& [section, sectionSettings] : loadedSettings.items()) {
            for (auto& [key, value] : sectionSettings.items()) {
                if (settings.contains(section) && settings[section].contains(key)) {
                    settings[section][key] = value;
                }
            }
        }
    }

    json settings;
};

// Global config instance
inline Config& config = Config::Get();
