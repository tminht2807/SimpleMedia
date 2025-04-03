#include "File.hpp"

File::File(const std::string& _filePath) 
    : File_path(_filePath), CurrentTime(0.0), isPaused(false) {}

void File::Display_Timestamp() {
    std::thread([this]() {
        while (true) {
            if (!isPaused) {
                auto now = std::chrono::steady_clock::now();
                CurrentTime = std::chrono::duration<double>(now - StartTime).count();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Update every 100ms
        }
    }).detach();
}

void File::Play() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_Music* music = Mix_LoadMUS(File_path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }

    StartTime = std::chrono::steady_clock::now();
    isPaused = false;
    Mix_PlayMusic(music, 1);
    Display_Timestamp();
}

double File::Get_Current() {
    return CurrentTime;
}

void File::Pause() {
    if (isPaused) {
        // Resume playback
        StartTime += std::chrono::steady_clock::now() - StartTime; // Adjust StartTime
        Mix_ResumeMusic();
    } else {
        // Pause playback
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

MetadataMP3 File::Get_Metadata() {
    return Metadata;
}

void File::Stop() {
    Mix_HaltMusic();
    Mix_CloseAudio();
    CurrentTime = 0.0;
    isPaused = false;
}