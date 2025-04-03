#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <mutex>

struct MetadataMP3{
    double Duration;
    TagLib::String year;
    TagLib::String album;
    TagLib::String artist;
    TagLib::String genre;
};

class File {
protected:
    std::string File_path;
    MetadataMP3 Metadata;
    std::chrono::steady_clock::time_point StartTime; // Start time of playback
    double CurrentTime; // Current playback time in seconds
    bool isPaused;
public:
    File(const std::string& _filePath);

    /** 
    * @brief Show the media file timestamp running, use thread to run parallel.
    * When the media is Pause(), 
    * make sure the other timestamps like CurrentTime or Get_Current() still manage to get real timestamp
    */
    void Display_Timestamp();

    /**
    * @brief Init the SDL connection, start playing the media file with the path File_path.
    */
    void Play();

    /**
    * @brief Get current time of the media file, when Pause() media, Get_Current will stop at the time of the pause.
    */
    double Get_Current();

    /**
    * @brief Pause/Resume the media file, 
    * consider the variables CurrentTime and Get_Current() method 
    * to ensure they still have the right value of time stamp of media playing even when the media is paused.
    */
    void Pause();

    /**
    * @brief Edit the media file's metadata.
    */
    void Edit_Metadata();
    
    /**
    * @brief  Get the media file's metadata.
    * @return a structure of metadata of file .mp3
    */
    MetadataMP3 Get_Metadata();

    /**
    * @brief Set the media metadata to attributes of the object.
    */
    void Set_Metadata();

    /**
    * @brief Stop the media file playback.
    */
    void Stop();
};