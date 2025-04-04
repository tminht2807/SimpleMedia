#include "IController.hpp"
#include <filesystem> // C++17 filesystem library
#include <iostream> // For error messages

// Constructor
IController::IController()
    : currentIndex(0), currentMusic(nullptr), currentTime(0.0), isPlaying(false), isPaused(false) {
    instance = this; // Set the singleton instance
    try {
        // Retrieve the current directory and save it to a temporary variable
        std::string tempDirectory = std::filesystem::current_path().string();

        // Initialize the current directory and media files
        UpdateCurrentDirectory(tempDirectory);
    } catch (const std::exception& e) {
        std::cerr << "Error initializing controller: " << e.what() << std::endl;
    }
    // Initialize SDL2
    if (!InitializeSDL()) {
        std::cerr << "Failed to initialize SDL2." << std::endl;
        throw std::runtime_error("SDL2 initialization failed");
    }
}

// Destructor
IController::~IController() {
    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

// SDL2 Initialization Method
bool IController::InitializeSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_mixer with audio format settings
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true; // Initialization successful
}

// Static callback function to handle the end of media playback
void IController::StaticOnMediaFinished() {
    if (instance) {
        instance->OnMediaFinished();
    }
}

// Callback function to handle the end of media playback
void IController::OnMediaFinished() {
    std::cout << "Media playback finished." << std::endl;

    // Check if the current media is the last in the vector
    if (currentIndex + 1 >= mediaFiles.size()) {
        std::cout << "Reached the end of the playlist. Restarting from the beginning." << std::endl;
        currentIndex = 0; // Reset to the start of the vector
    } else {
        currentIndex++; // Move to the next media file
    }

    // Attempt to play the next media file
    if (!PlayMedia(currentIndex)) {
        std::cerr << "Failed to play the next media file." << std::endl;
    }
}

// Play Media Method
bool IController::PlayMedia(int index) {
    try {
        // Update currentIndex if a valid index is provided
        if (index >= 0 && index < static_cast<int>(mediaFiles.size())) {
            currentIndex = index;
        }

        // Check if mediaFiles is empty or currentIndex is out of range
        if (mediaFiles.empty() || currentIndex >= mediaFiles.size()) {
            std::cerr << "No media file to play." << std::endl;
            return false;
        }

        // Get the file path of the current media file
        std::string filePath = mediaFiles[currentIndex]->getFilePath();

        // Free the previous music object if any
        if (currentMusic) {
            Mix_FreeMusic(currentMusic);
        }

        // Load the media file into SDL_mixer
        currentMusic = Mix_LoadMUS(filePath.c_str());
        if (!currentMusic) {
            std::cerr << "Failed to load media file: " << Mix_GetError() << std::endl;
            return false;
        }

        // Set the callback for when the music finishes
        Mix_HookMusicFinished(StaticOnMediaFinished);

        // Start playing the media file
        if (Mix_PlayMusic(currentMusic, 0) == -1) {
            std::cerr << "Failed to play media: " << Mix_GetError() << std::endl;
            return false;
        }

        isPlaying = true;
        isPaused = false;
        currentTime = 0.0; // Reset playback time
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error during PlayMedia: " << e.what() << std::endl;
        return false;
    }
}

// Pause and Resume Media Method
bool IController::PauseResumeMedia() {
    if (!isPlaying) {
        std::cerr << "No media is currently playing." << std::endl;
        return false;
    }

    if (isPaused) {
        Mix_ResumeMusic();
        isPaused = false;
    } else {
        Mix_PauseMusic();
        isPaused = true;
    }

    return true;
}

// Update Current Directory
void IController::UpdateCurrentDirectory(const std::string& directoryPath) {
    try {
        // Assign the provided directory path to the currentDirectory attribute
        currentDirectory = directoryPath;

        // Clear the mediaFiles vector
        mediaFiles.clear();

        // Add media files from the specified directory and its subdirectories
        AddMediaFilesFromFolder(currentDirectory);
    } catch (const std::exception& e) {
        std::cerr << "Error updating current directory: " << e.what() << std::endl;
    }
}

// Add Media Files from Folder Method
bool IController::AddMediaFilesFromFolder(const std::string& folderPath) {
    try {
        // Iterate recursively over the directory and subdirectories
        for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                // Check if the file has a valid media extension
                std::string extension = entry.path().extension().string();
                if (extension == ".mp3" || extension == ".wav") {
                    // Create a File object using the constructor
                    std::shared_ptr<File> mediaFile = std::make_shared<File>(entry.path().string());

                    // Add the File object to the mediaFiles vector
                    mediaFiles.push_back(mediaFile);
                }
            }
        }
        return true; // Successfully added media files
    } catch (const std::exception& e) {
        std::cerr << "Error adding media files: " << e.what() << std::endl;
        return false; // Return false if an error occurs
    }
}

// Next Media Method
bool IController::NextMedia() {
    if (currentIndex + 1 < mediaFiles.size()) {
        currentIndex++;
        return PlayMedia(currentIndex);
    } else {
        std::cerr << "No next media file available." << std::endl;
        return false;
    }
}
// Previous Media Method
bool IController::PrevMedia() {
    if (currentIndex - 1 >= 0) {
        currentIndex--;
        return PlayMedia(currentIndex);
    } else {
        std::cerr << "No previous media file available." << std::endl;
        return false;
    }
}