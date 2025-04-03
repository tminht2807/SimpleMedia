#pragma once
#include "File.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <functional> // For std::function
#include <mutex>      // For thread-safe output

class ViewMediaPlay {
private:
    std::atomic<bool> isRunning; // Flag to control the timestamp update thread
    std::mutex outputMutex;      // Mutex to synchronize output

public:
    ViewMediaPlay() : isRunning(false) {}

    // Display the current timestamp of the media
    void DisplayCurrentTime(double currentTime, double totalDuration) {
        std::lock_guard<std::mutex> lock(outputMutex); // Ensure thread-safe output
        int currentMinutes = static_cast<int>(currentTime) / 60;
        int currentSeconds = static_cast<int>(currentTime) % 60;

        int totalMinutes = static_cast<int>(totalDuration) / 60;
        int totalSeconds = static_cast<int>(totalDuration) % 60;

        // Clear the current line and print the timestamp
        std::cout << "\rCurrent Time: " << (currentMinutes < 10 ? "0" : "") << currentMinutes << ":"
                  << (currentSeconds < 10 ? "0" : "") << currentSeconds
                  << " / " << (totalMinutes < 10 ? "0" : "") << totalMinutes << ":"
                  << (totalSeconds < 10 ? "0" : "") << totalSeconds << "   " << std::flush;

        // Print the input prompt on a new line
        std::cout << "\n> " << std::flush;
    }

    // Notify the user when playback is finished
    void NotifyPlaybackFinished() {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "\nPlayback finished!" << std::endl;
        std::cout << "> " << std::flush; // Ensure the input prompt is displayed after the message
    }

    // Start updating the timestamp in a separate thread
    void StartTimestampUpdates(std::function<double()> getCurrentTime, double totalDuration, std::function<bool()> isPlaying) {
        isRunning = true;
        std::thread([this, getCurrentTime, totalDuration, isPlaying]() {
            while (isRunning.load()) { // Use .load() for atomic variables
                if (!isPlaying()) {
                    isRunning = false; // Stop if playback has ended
                    NotifyPlaybackFinished();
                    break;
                }
                double currentTime = getCurrentTime();
                DisplayCurrentTime(currentTime, totalDuration);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }).detach();
    }

    // Stop updating the timestamp
    void StopTimestampUpdates() {
        isRunning = false;
        std::cout << std::endl; // Ensure the input prompt is on a new line
    }
};