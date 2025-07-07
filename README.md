# C++ Cross-Platform Project Template

## Overview

This repository provides a ready-to-use template for creating new cross-platform C++ applications. It's designed to serve as a starting point for developers who need to build software that runs seamlessly on Linux, macOS, and Windows without having to set up complex build systems from scratch.

## Why Use This Template?

Creating truly cross-platform C++ applications with proper build pipelines can be challenging. This template solves common problems:

- **Unified build system** that works consistently across platforms
- **True cross-compilation** with native binaries for each target platform
- **Ready-made CI/CD pipeline** with GitHub Actions for automated releases
- **Docker integration** for reproducible builds
- **Common infrastructure** like logging and signal handling already implemented

## Key Features

- Pre-configured build system for Linux, macOS, and Windows targets
- Docker-based development environment for consistent builds
- Native compilation support when running on target platforms
- Integrated logging system ready for extension
- Signal handling for graceful application termination
- Google Test framework integration for unit testing
- GitHub Actions workflow for creating platform-specific releases
- Clean project structure with sensible defaults
- Support for popular GUI frameworks (Qt, GTK, wxWidgets)

## Project Structure

```
.
├── build/              # Locally compiled binaries
├── dist/               # Multi-platform distribution binaries
├── src/                # Source code
│   ├── includes/       # Header files (.h)
│   ├── sources/        # Implementation files (.cpp)
│   └── Makefile        # Specific Makefile for source compilation
├── tests/              # Unit tests
│   ├── build/          # Test build directory
│   └── Makefile        # Test-specific Makefile
├── .github/workflows/  # GitHub Actions configuration files
├── .editorconfig       # Editor configuration for code style
├── CHANGELOG.md        # Project change history
├── CONTRIBUTING.md     # Contribution guidelines
├── Dockerfile.builder  # Dockerfile for cross-compilation environment
├── LICENSE             # MIT License
├── Makefile            # Main Makefile with high-level commands
└── README.md           # This file
```

## Getting Started

This project is designed as a template/scaffolding for new cross-platform C++ applications. Here's how to use it as a starting point for your own project:

### Using This Template

1. **Clone or download this repository**
   ```bash
   git clone https://github.com/mpernia/cross-platform-compiled.git my-cpp-project
   cd my-cpp-project
   ```

2. **Remove the existing Git history and start fresh**
   ```bash
   rm -rf .git
   git init
   git add .
   git commit -m "Initial commit from cross-platform template"
   ```

3. **Update project information**
   - Modify `PROJECT_NAME` in the main Makefile
   - Update this README.md with your project details
   - Start adding your own code to `src/sources/` and headers to `src/includes/`

4. **Test the build system**
   ```bash
   make all
   ```

5. **Customize the CI/CD workflow**
   - Modify `.github/workflows/release.yml` if needed

### Example: Creating a Simple Application

```cpp
// In src/sources/main.cpp
#include "logger.h"

int main(int argc, char** argv) {
    // Logger is already set up from the template
    Logger::setLogLevel(LogLevel::DEBUG);
    Logger::log(LogLevel::INFO, "My application started");
    
    // Your application code here
    
    Logger::log(LogLevel::INFO, "Application shutting down");
    return 0;
}
```

## GUI Framework Support

This template includes examples of GUI applications using three popular cross-platform frameworks. Each framework has its own example in the `examples/gui/` directory.

### Available GUI Frameworks

1. **Qt** - A comprehensive C++ framework with rich UI components
   - Modern look and feel across all platforms
   - Extensive widget library and tools
   - Strong industry adoption

2. **GTK** - The GIMP Toolkit, popular on Linux systems
   - Native look on Linux/GNOME systems
   - Good cross-platform support
   - Lightweight and efficient

3. **wxWidgets** - A native-looking GUI framework
   - Uses native controls on each platform
   - Simpler API than Qt
   - Wide platform support

### Building GUI Examples

The GUI examples use Docker by default to ensure all dependencies are available. This makes the build process consistent across all environments.

#### Using Docker (Default)

To build an example with a specific GUI framework using Docker:

```bash
# Build Qt example (default)
cd examples/gui
make

# Or specify the framework
cd examples/gui
make GUI_FRAMEWORK=qt
make GUI_FRAMEWORK=gtk
make GUI_FRAMEWORK=wx

# Direct commands also work
cd examples/gui
make qt    # Build Qt example
make gtk   # Build GTK example
make wx    # Build wxWidgets example
```

#### Local Compilation

If you have the necessary dependencies installed locally, you can build without Docker:

```bash
# Build examples locally
cd examples/gui
make local-qt
make local-gtk
make local-wx

# Build all examples locally
make local-all
```

### Creating Your Own GUI Application

The examples provided are minimal "Hello World" applications that demonstrate how to integrate the template's logging system with each GUI framework. Use them as a starting point for your own application:

1. Choose your preferred framework
2. Copy the corresponding example
3. Extend it with your application logic

### Dependencies

To compile the GUI examples, you'll need to install the development libraries for your chosen framework:

- **Qt**: Qt5 or Qt6 development packages
  ```bash
  # Ubuntu/Debian
  apt-get install qtbase5-dev qt5-qmake
  
  # macOS with Homebrew
  brew install qt5
  
  # Windows with MSYS2
  pacman -S mingw-w64-x86_64-qt5
  ```

- **GTK**: GTK4 development packages
  ```bash
  # Ubuntu/Debian
  apt-get install libgtk-4-dev
  
  # macOS with Homebrew
  brew install gtk4
  
  # Windows with MSYS2
  pacman -S mingw-w64-x86_64-gtk4
  ```

- **wxWidgets**: wxWidgets development packages
  ```bash
  # Ubuntu/Debian
  apt-get install libwxgtk3.0-gtk3-dev
  
  # macOS with Homebrew
  brew install wxwidgets
  
  # Windows with MSYS2
  pacman -S mingw-w64-x86_64-wxwidgets
  ```

## Requirements

### Local Compilation

- Linux/macOS:
  - g++ or clang++ with C++17 support
  - make
  - zlib (libz)

- Windows:
  - MinGW-w64 with C++17 support
  - MSYS2/Cygwin with make
  - zlib for Windows

### Docker Compilation

- Docker

## Compilation

### Local Compilation for Your Platform

```bash
# Compile for your local platform
make local

# Run the generated binary
./bin/my_app
```

### Complete Workflow

```bash
# Complete workflow: clean, run tests and compile for all platforms using Docker
make all
```

When running `make all`, the system will:
1. Clean previous build files
2. Run all tests in Docker
3. If tests pass, compile binaries for all platforms (Linux, Windows, macOS)

**Special behavior on macOS**: When running on a macOS system, `make all` will automatically replace the Docker-generated macOS binary with a native one compiled directly on your macOS system. This ensures you get a truly native and executable binary for macOS without changing the standard naming convention.

### Platform-Specific Compilation

```bash
# Compile for a specific platform
make linux
make macos
make macos_arm64
make windows
```

### Clean Commands

```bash
# Clean build files but preserve distribution binaries
make clean

# Remove all generated files (build and distribution)
make clean-all
```

### Generated Binaries

All compilation commands generate binaries in the `dist/` directory. When running the complete workflow (`make all`), the following binaries are created:

| File | Type | Description |
|------|------|-------------|
| `my_app_linux` | Linux ELF | Native Linux binary |
| `my_app_windows.exe` | Windows PE | Native Windows binary (cross-compiled with MinGW) |
| `my_app_macos` | macOS Mach-O or Linux ELF | Native macOS binary when built on macOS, or Linux binary with macOS #ifdef adaptations when built on other platforms |

**Important Note**: When compiled on non-macOS systems, the `my_app_macos` binary is not a true native macOS executable but rather a Linux binary with macOS preprocessor definitions. However, when you run `make all` directly on a macOS system, the build system automatically replaces this with a true native macOS binary (Mach-O format).

## GitHub Releases

This project is configured with GitHub Actions to automatically build native binaries for all supported platforms when a new version tag is pushed.

### How Releases Work

1. When a tag with format `v*` is pushed (e.g., `v1.0.0`), GitHub Actions automatically:
   - Builds a native Linux binary on Ubuntu runners
   - Builds a native macOS binary on macOS runners
   - Builds a native Windows binary on Windows runners with MSYS2
   - Creates a GitHub Release with all three binaries attached

2. This ensures that **all binaries are truly native** for their respective platforms, unlike when building locally with Docker where the macOS binary is not a true Mach-O executable unless built on a macOS system.

### How to Create a Release

```bash
# Tag the current commit with a version number
git tag v1.0.0

# Push the tag to GitHub
git push origin v1.0.0
```

### How to Download Release Binaries

Users can download pre-built native binaries from the [Releases page](https://github.com/mpernia/cross-platform-compiled/releases) on GitHub.

### Docker Commands

```bash
# Build the Docker image for cross-compilation
make docker-build

# Compile for all platforms using Docker
make docker-compile

# Run unit tests in Docker
make docker-test

# Or compile for a specific platform using Docker
make docker-linux
make docker-windows
```

## Creating Releases

1. Update the version in `src/includes/common.h` (`VERSION_*` constants).
2. Create a new tag in GitHub.
3. Create a new release based on that tag.
4. GitHub Actions will automatically compile binaries for all platforms.
5. The binaries will be automatically attached to the release.

## Customizing the Project

1. Modify `PROJECT_NAME` in the main Makefile to change the binary names.
2. Add your .cpp files in `src/sources/` and your headers in `src/includes/`.
3. If you need additional libraries, update the corresponding Makefiles.
4. Customize the `.github/workflows/release.yml` file if you need to modify the release process.

## Signal Handling

The code includes signal handling for clean termination on all platforms:

- On Linux/macOS: Handles SIGINT, SIGTERM, and ignores SIGPIPE
- On Windows: Handles SIGINT and SIGTERM

## Unit Testing

The project includes a testing framework based on Google Test. You can run tests either locally or within Docker:

### Local Testing

```bash
# Install Google Test dependencies
make install-gtest

# Run all tests
make test
```

### Docker Testing

```bash
# Run tests inside the Docker container
make docker-test
```

This ensures consistent test execution across different development environments.

### Adding New Tests

To create new tests:

1. Add your test files to the `tests/` directory with naming convention `*_test.cpp`
2. Follow the Google Test pattern for assertions and test cases
3. Run `make test` locally or `make docker-test` for containerized testing

## EditorConfig

The project includes an `.editorconfig` file to maintain consistent coding styles across various editors and IDEs. Supported editors will automatically use these settings.

Key settings include:
- 4 spaces for indentation in C++ files
- UTF-8 encoding
- LF line endings
- 100 character line length limit for C++ files

## Changelog

This project maintains a changelog following the [Keep a Changelog](https://keepachangelog.com/) format and adheres to [Semantic Versioning](https://semver.org/).

When contributing, please update the CHANGELOG.md file with your changes under the appropriate section.

## Contributing

Please see [CONTRIBUTING.md](CONTRIBUTING.md) for detailed guidelines on how to contribute to this project.

## License

Code released under the MIT license. See LICENSE file for more details.
