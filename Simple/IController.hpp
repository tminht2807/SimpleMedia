#pragma once
#include "File.hpp"
#include "ViewMediaPlay.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

class IController {
private:
    std::vector<std::shared_ptr<File>> mediaFiles; // Vector of File references
    ViewMediaPlay view;                            // View to display media information
    Mix_Music* currentMusic;                       // SDL2 music object
    size_t currentIndex;                           // Index of the currently playing file
    double currentTime;                            // Current playback time in seconds
    std::atomic<bool> isPlaying;                   // Flag to indicate if media is playing
    std::mutex timeMutex;   
public:
    IController() : currentMusic(nullptr), currentIndex(-1) {
        // Define the path to the "sample" subfolder
        fs::path sampleFolder = fs::current_path() / "sample";

        // Check if the "sample" folder exists
        if (fs::exists(sampleFolder) && fs::is_directory(sampleFolder)) {
            // Iterate through the "sample" folder and collect .mp3 files
            for (const auto& entry : fs::directory_iterator(sampleFolder)) {
                if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
                    AddMediaFile(entry.path().string());
                }
            }
        } else {
            std::cerr << "Sample folder not found: " << sampleFolder << std::endl;
        }
    }

    ~IController() {
        if (currentMusic) {
            Mix_FreeMusic(currentMusic);
        }
        Mix_CloseAudio();
    }

    // Initialize SDL2 audio
    void InitAudio() {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        }
    }

    // Add media to vector mediaFiles
    void AddMediaFile(const std::string& filePath) {
        auto file = std::make_shared<File>(filePath);
        mediaFiles.push_back(file);
    }

    // Play a specific media file by index
    void PlayMedia(size_t index) {
        if (index < mediaFiles.size()) {
            if (currentMusic) {
                Mix_FreeMusic(currentMusic);
                view.StopTimestampUpdates(); // Stop previous timestamp updates
            }
            currentMusic = Mix_LoadMUS(mediaFiles[index]->Get_FilePath().c_str());
            if (!currentMusic) {
                std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
                return;
            }
            Mix_PlayMusic(currentMusic, 1);
            currentIndex = index;
            {
                std::lock_guard<std::mutex> lock(timeMutex);
                currentTime = 0; // Reset current time
            }
            isPlaying = true;
    
            // Start updating the timestamp
            view.StartTimestampUpdates(
                [this]() {
                    std::lock_guard<std::mutex> lock(timeMutex);
                    return currentTime;
                },
                mediaFiles[index]->Get_Metadata().Duration,
                [this]() { return isPlaying.load(); }
            );
    
            // Start a thread to increment the current time
            std::thread([this, index]() {
                while (isPlaying.load()) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    {
                        std::lock_guard<std::mutex> lock(timeMutex);
                        currentTime += 1.0; // Increment current time by 1 second
                        if (currentTime >= mediaFiles[index]->Get_Metadata().Duration) {
                            isPlaying = false;
                        }
                    }
                }
            }).detach();
        } else {
            std::cerr << "Invalid media index!" << std::endl;
        }
    }
    
    void StopMedia() {
        if (currentMusic) {
            Mix_HaltMusic();
            isPlaying = false;
            {
                std::lock_guard<std::mutex> lock(timeMutex);
                currentTime = 0;
            }
            view.StopTimestampUpdates(); // Stop timestamp updates
        }
    }

    // Pause or resume the currently playing media
    void PauseMedia() {
        if (currentMusic && currentIndex < mediaFiles.size()) {
            if (isPlaying.load()) {
                Mix_PauseMusic();
                isPlaying = false;
            } else {
                Mix_ResumeMusic();
                isPlaying = true;
            }
        }
    }

    // Skip to the next media file
    void Next() {
        if (mediaFiles.empty()) {
            std::cerr << "No media files available!" << std::endl;
            return;
        }
        size_t nextIndex = (currentIndex + 1) % mediaFiles.size();
        PlayMedia(nextIndex);
    }

    // Skip to the previous media file
    void Prev() {
        if (mediaFiles.empty()) {
            std::cerr << "No media files available!" << std::endl;
            return;
        }
        size_t prevIndex = (currentIndex == 0) ? mediaFiles.size() - 1 : currentIndex - 1;
        PlayMedia(prevIndex);
    }
};