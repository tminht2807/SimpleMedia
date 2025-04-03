#include "File.hpp"

File::File(const std::string& _filePath) 
    : File_path(_filePath), CurrentTime(0.0), isPaused(false) {}

void File::Display_Timestamp() {
    std::thread([this]() {
        const int barWidth = 30; // Width of the progress bar
        while (Mix_PlayingMusic()) { // Check if the music is still playing
            if (!isPaused) {
                auto now = std::chrono::steady_clock::now();
                CurrentTime = std::chrono::duration<double>(now - StartTime).count();
            }

            // Stop updating if the current time exceeds the duration
            if (CurrentTime >= Metadata.Duration) {
                CurrentTime = Metadata.Duration; // Cap the current time to the duration
            }

            // Calculate progress
            double progress = (Metadata.Duration > 0) ? (CurrentTime / Metadata.Duration) : 0.0;
            if (progress > 1.0) progress = 1.0; // Cap progress at 100%

            // Format time as MM:SS
            int currentMinutes = static_cast<int>(CurrentTime) / 60;
            int currentSeconds = static_cast<int>(CurrentTime) % 60;
            int durationMinutes = static_cast<int>(Metadata.Duration) / 60;
            int durationSeconds = static_cast<int>(Metadata.Duration) % 60;

            // Build the progress bar
            int filledBars = static_cast<int>(progress * barWidth);
            std::string progressBar = "[" + std::string(filledBars, '=') + std::string(barWidth - filledBars, ' ') + "]";

            // Use a mutex to synchronize output
            static std::mutex outputMutex;
            std::lock_guard<std::mutex> lock(outputMutex);

            // Move the cursor up one line, clear the line, and print the timestamp and progress bar
            std::cout << "\033[1A\033[2K" // Move cursor up one line and clear the line
                        << "Current Time: " << (currentMinutes < 10 ? "0" : "") << currentMinutes << ":"
                        << (currentSeconds < 10 ? "0" : "") << currentSeconds << " / "
                        << (durationMinutes < 10 ? "0" : "") << durationMinutes << ":"
                        << (durationSeconds < 10 ? "0" : "") << durationSeconds
                        << " " << progressBar << std::endl;

            // Move the cursor back down to the input line
            std::cout << "\033[1E> " << std::flush;

            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Update every 100ms
        }

        // Print a message when playback finishes
        std::cout << "\nPlayback finished!" << std::endl;
    }).detach();
}

void File::Play() {
    Set_Metadata();
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_Music* music = Mix_LoadMUS(File_path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }

    // Start playback
    StartTime = std::chrono::steady_clock::now();
    isPaused = false;
    Mix_PlayMusic(music, 1); // Play the music once
    Display_Timestamp();
}

double File::Get_Current() {
    return CurrentTime;
}

void File::Pause() {
    if (isPaused) {
        // Resume playback
        auto now = std::chrono::steady_clock::now();
        StartTime += now - PauseTime; // Adjust StartTime by the pause duration
        Mix_ResumeMusic();
    } else {
        // Pause playback
        PauseTime = std::chrono::steady_clock::now(); // Record the time when paused
        Mix_PauseMusic();
    }
    isPaused = !isPaused;
}

void File::Edit_Metadata() {
    // Example: Editing metadata (implementation depends on TagLib usage)
    TagLib::FileRef file(File_path.c_str());
    if (!file.isNull() && file.tag()) {
        file.tag()->setArtist("New Artist");
        file.tag()->setAlbum("New Album");
        file.save();
    }
}

void File::Set_Metadata() {
    TagLib::FileRef file(File_path.c_str());
    if (!file.isNull() && file.tag()) {
        // Assign metadata attributes
        Metadata.artist = file.tag()->artist();
        Metadata.album = file.tag()->album();
        Metadata.genre = file.tag()->genre();

        // Convert year (unsigned int) to TagLib::String
        Metadata.year = TagLib::String::number(file.tag()->year());

        // Get the duration of the file (if supported by TagLib)
        if (file.audioProperties()) {
            Metadata.Duration = file.audioProperties()->length(); // Duration in seconds
        } else {
            Metadata.Duration = 0.0; // Default to 0 if duration is unavailable
        }
    } else {
        std::cerr << "Failed to read metadata from file: " << File_path << std::endl;
        Metadata = {}; // Reset metadata to default values
    }
}

MetadataMP3 File::Get_Metadata() {
    return Metadata;
}

void File::Stop() {
    Mix_HaltMusic();
    Mix_CloseAudio();
    CurrentTime = 0.0;
    isPaused = false;
}

bool File::Get_isFinished() const{
    return isFinished;
}