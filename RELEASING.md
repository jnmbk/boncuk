# Boncuk Release Process

This document outlines the standard procedure for releasing a new version of Boncuk. We use a GitHub Actions CI/CD pipeline to automate the generation of cross-platform installers (Windows, macOS, Linux).

## 1. Prepare the Release
Before creating a release, ensure that:
- All desired features and bug fixes are merged into the target branch (e.g., `qt6` or `main`).
- Local tests pass successfully.

## 2. Update Version Numbers
Before tagging, update the version numbers in the source code configuration:

1. Open **`boncuk.pro`** and update the `VERSION` variable:
   ```pro
   VERSION = "2.1.0"
   ```
2. Open **`windows/boncuk.iss`** and update the `AppVersion`:
   ```ini
   AppVersion=2.1.0
   ```

## 3. Commit the Version Bump
Commit these version changes to your repository:
```bash
git add boncuk.pro windows/boncuk.iss
git commit -m "Bump version to v2.1.0"
git push origin qt6  # Replace with your active branch if different
```

## 4. Create and Push a Git Tag
Our GitHub Actions workflow is configured to automatically run and package the application whenever a Git tag starting with `v` is pushed to the repository.

Create an annotated tag for the new version:
```bash
git tag -a v2.1.0 -m "Release version 2.1.0"
```

Push the tag to GitHub:
```bash
git push origin v2.1.0
```
*(Alternatively, use `git push origin --tags` to push all pending tags).*

## 5. Retrieve the Installers from GitHub Actions
Once the tag is pushed to GitHub, the CI pipeline will automatically start building the installers.

1. Navigate to the **Actions** tab on your GitHub repository page.
2. Click on the most recent workflow run (it should match your tag name).
3. Wait for the `build-and-test` jobs for Windows, macOS, and Linux to finish.
4. Scroll down to the **Artifacts** section at the bottom of the workflow run page.
5. Download the generated artifact zip files:
   - `Boncuk-Windows-Installer`
   - `Boncuk-macOS-DMG`
   - `Boncuk-Linux-AppImage`

## 6. Publish the GitHub Release
To make the installers easily accessible to your users:

1. Go to the **Releases** section on your GitHub repository sidebar.
2. Click **Draft a new release**.
3. In the "Choose a tag" dropdown, select the tag you just pushed (e.g., `v2.1.0`).
4. Write a title and provide Release Notes (changelog, new features, bug fixes).
5. Extract the `.zip` artifacts you downloaded in Step 5.
6. Drag and drop the actual installer files (`Boncuk_Setup.exe`, `boncuk.dmg`, and the `.AppImage`) into the **Attach binaries** area at the bottom of the release form.
7. Click **Publish release**.

Users can now download the native installers directly from your GitHub Releases page!

