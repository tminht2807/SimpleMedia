#pragma once
#include "File.hpp"
// #include "IView.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <filesystem>
#include <atomic>
#include <mutex>

/**
 * @class IController
 * @brief Base controller class for managing media files and metadata.
 */
class IController {
private:
    // static IController* instance; // Singleton instance of IController
    inline static IController* instance = nullptr; // Singleton instance of IController

    // Collection of media files to manage
    std::vector<std::shared_ptr<File>> mediaFiles;

    // Index of the currently selected media file
    size_t currentIndex;

    // Pointer to the SDL2 music object for media playback
    Mix_Music* currentMusic;

    // Tracks current playback time in seconds
    double currentTime;

    // Flag to indicate if media is playing
    std::atomic<bool> isPlaying;

    // Flag to indicate if media is paused
    std::atomic<bool> isPaused;

    // The directory from which the program is executed
    std::string currentDirectory;

    // View instance for interacting with the UI
    // IView view;

public:
    // ###################################################################### Constructor and Destructor
    /**
     * @brief Default constructor that sets the current directory 
     *        and populates media files.
     */
    IController();

    /**
     * @brief Destructor to clean up resources.
     */
    virtual ~IController();

    // ###################################################################### SDL2 Initialization Methods
    /**
     * @brief Initializes SDL and SDL_mixer for media playback.
     * @return True if initialization is successful, false otherwise.
     */
    bool InitializeSDL();

    // ###################################################################### Playback Control Methods
    /**
     * @brief Starts playing the current media file.
     * @return True if playback starts successfully, false otherwise.
     */
    bool PlayMedia(int index);

    /**
     * @brief Stops the currently playing media file.
     */
    void OnMediaFinished();

    /**
     * @brief Static callback function to handle the end of media playback.
     */
    static void StaticOnMediaFinished();

    /**
     * @brief Pauses or resumes the currently playing media file.
     * @return True if the operation is successful, false otherwise.
     */
    bool PauseResumeMedia();

    /**
     * @brief Moves to the next media file in the collection and starts playback.
     * @return True if the next media file is played successfully, false otherwise.
     */
    bool NextMedia();

    /**
     * @brief Moves to the previous media file in the collection and starts playback.
     * @return True if the previous media file is played successfully, false otherwise.
     */
    bool PrevMedia();

    // ###################################################################### File and Directory Management Methods
    /**
     * @brief Updates the current directory from where the program is executed.
     *        Assigns the path to the currentDirectory attribute.
     * @param directoryPath Path to the directory to set as the current directory.
     */
    void UpdateCurrentDirectory(const std::string& directoryPath);

    /**
     * @brief Adds media files from a folder and its subfolders to the collection.
     * @param folderPath Path to the folder containing media files.
     * @return True if files were successfully added, false otherwise.
     */
    bool AddMediaFilesFromFolder(const std::string& folderPath);

    /**
     * @brief Updates the current playback time of the media file.
     *        Assigns the playback time to the currentTime attribute.
     */
    void UpdateCurrentTime();
};