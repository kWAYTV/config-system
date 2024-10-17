# C++ Configuration System

![Preview](https://i.imgur.com/kx4As1P.png)

## Description

This project demonstrates a configuration management system implemented in C++. It provides a flexible and robust way to handle application settings, including loading from and saving to JSON files, with support for default values and easy access to configuration options.

## Table of Contents

- [C++ Configuration System](#c-configuration-system)
  - [Description](#description)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Project Structure](#project-structure)
  - [Contributing](#contributing)
  - [License](#license)

## Features

- Singleton-based configuration manager
- JSON file-based configuration storage
- Default settings with easy registration
- Type-safe setting access and modification
- Configuration file management (list, save, delete)
- Colored console logging for better readability
- Cross-platform file system operations using C++17 features

## Requirements

- C++20 compatible compiler (e.g., MSVC v143)
- Visual Studio 2022 or later
- nlohmann/json library (included in the project)

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/kWAYTV/config-system.git
   ```
2. Open the `example.sln` file in Visual Studio.
3. Build the project for your desired configuration (Release) and platform (x64).

## Usage

The `main.cpp` file demonstrates the usage of the configuration manager:

- Loading and saving configuration files
- Accessing and modifying settings
- Listing and deleting configuration files
- Using the logging system

To run the example:

1. Build the project in Visual Studio.
2. Run the compiled executable from the `out/Release` directory.

## Project Structure

- `src/`
  - `main.cpp`: Example usage of the configuration manager
  - `config.hpp`: Configuration manager implementation
  - `logger.hpp`: Logging utilities
- `ext/`
  - `json.hpp`: nlohmann/json library
- `example.vcxproj`: Visual Studio project file
- `example.vcxproj.filters`: Visual Studio project filters
- `example.vcxproj.user`: Visual Studio user-specific settings

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open-source and available under the MIT License.
