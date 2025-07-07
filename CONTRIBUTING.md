# Contributing to C++ Cross-Platform Scaffolding

First of all, thank you for considering contributing to this project! This document provides guidelines and steps for contributing.

## Code of Conduct

By participating in this project, you are expected to uphold our Code of Conduct:

- Use welcoming and inclusive language
- Be respectful of differing viewpoints and experiences
- Accept constructive criticism
- Focus on what is best for the community
- Show empathy towards other community members

## Getting Started

### Fork and Clone the Repository

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/REPOSITORY-NAME.git
   cd REPOSITORY-NAME
   ```
3. Add the original repository as an upstream remote:
   ```bash
   git remote add upstream https://github.com/ORIGINAL-OWNER/ORIGINAL-REPOSITORY.git
   ```

### Set Up Development Environment

1. Make sure you have all required development tools installed (see README.md)
2. Run a local build to verify your setup:
   ```bash
   make local
   ```

## Making Contributions

### Pull Request Process

1. Create a new branch for your feature or bugfix:
   ```bash
   git checkout -b feature/your-feature-name
   ```
   or
   ```bash
   git checkout -b fix/your-bugfix-name
   ```

2. Make your changes, adhering to the coding standards described below.

3. Add tests for your changes if applicable.

4. Update documentation if necessary.

5. Commit your changes with clear, descriptive commit messages:
   ```bash
   git commit -m "Add feature: description of feature"
   ```

6. Push to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

7. Submit a Pull Request through GitHub.

8. Your Pull Request will be reviewed by maintainers, who may request changes.

9. Once approved, your Pull Request will be merged.

### Keeping Your Fork Updated

```bash
git fetch upstream
git merge upstream/main
git push origin main
```

## Coding Standards

### C++ Style Guide

- Use C++17 standard.
- Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with these exceptions:
  - Use 4 spaces for indentation, not tabs
  - Line length limit: 100 characters

### File Organization

- Place header files in `src/includes/`
- Place implementation files in `src/sources/`
- Name files with lowercase and underscores (e.g., `http_server.cpp`, not `HTTPServer.cpp`)

### Documentation

- Document all public functions, classes, and methods with descriptive comments
- Use Doxygen-style comments for API documentation

## Testing

- Write unit tests for new functionality
- Ensure all tests pass before submitting a Pull Request
- Test your changes on all supported platforms if possible (Linux, macOS, Windows)

## Bug Reports and Feature Requests

### Bug Reports

When reporting bugs, please include:

1. A clear and descriptive title
2. Steps to reproduce the bug
3. Expected behavior
4. Actual behavior
5. Environment details (OS, compiler version, etc.)

### Feature Requests

When suggesting features:

1. Describe the feature clearly
2. Explain why this feature would be useful
3. Provide examples of how this feature would be used

## Release Process

Only project maintainers should perform releases. The release process is:

1. Update version numbers in `src/includes/common.h`
2. Update CHANGELOG.md with notable changes
3. Create a new tag and GitHub release
4. GitHub Actions will automatically build and attach binaries

## Questions?

If you have any questions or need help, please open an issue with the label "question".

Thank you for contributing to the C++ Cross-Platform Scaffolding project!
