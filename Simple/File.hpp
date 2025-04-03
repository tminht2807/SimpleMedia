#pragma once
#include <string>
#include <chrono>
#include <taglib/fileref.h>
#include <taglib/tag.h>

struct MetadataMP3 {
    double Duration;
    TagLib::String year;
    TagLib::String album;
    TagLib::String artist;
    TagLib::String genre;
};

class File {
protected:
    std::string File_path; // Path to the media file
    MetadataMP3 Metadata;  // Metadata of the media file
    bool isPaused;         // Playback paused state
    bool isFinished;       // Playback finished state

public:
    // Constructor
    File(const std::string& _filePath) 
        : File_path(_filePath), isPaused(false), isFinished(false) {
        // Use TagLib to extract metadata
        TagLib::FileRef fileRef(_filePath.c_str());
        if (!fileRef.isNull() && fileRef.tag()) {
            Metadata.artist = fileRef.tag()->artist();
            Metadata.album = fileRef.tag()->album();
            Metadata.genre = fileRef.tag()->genre();
            Metadata.year = TagLib::String::number(fileRef.tag()->year()); // Convert year to TagLib::String
        }
        if (!fileRef.isNull() && fileRef.audioProperties()) {
            Metadata.Duration = fileRef.audioProperties()->length();
        }
    }

    // Get the file path
    const std::string& Get_FilePath() const { return File_path; }

    // Get the playback paused state
    bool Get_isPaused() const { return isPaused; }

    // Set the playback paused state
    void Set_isPaused(bool paused) { isPaused = paused; }

    // Get the playback finished state
    bool Get_isFinished() const { return isFinished; }

    // Set the playback finished state
    void Set_isFinished(bool finished) { isFinished = finished; }

    // Get the metadata of the media file
    MetadataMP3 Get_Metadata() const { return Metadata; }

    // Set the metadata of the media file
    void Set_Metadata(const MetadataMP3& metadata) { Metadata = metadata; }
};