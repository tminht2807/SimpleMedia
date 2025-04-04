#include "File.hpp"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>

// Constructor
File::File(const std::string& _filePath) : File_path(_filePath) {
    // Use TagLib to read metadata
    TagLib::FileRef fileRef(_filePath.c_str());
    if (!fileRef.isNull() && fileRef.tag()) {
        TagLib::Tag* tag = fileRef.tag();
        metadata.Title = tag->title().to8Bit(true);
        metadata.Artist = tag->artist().to8Bit(true);
        metadata.Album = tag->album().to8Bit(true);
        metadata.Year = std::to_string(tag->year());
        metadata.Comment = tag->comment().to8Bit(true);
        metadata.Genre = tag->genre().to8Bit(true);

        // Read duration using audio properties
        if (fileRef.audioProperties()) {
            metadata.Duration = fileRef.audioProperties()->lengthInSeconds();
        } else {
            metadata.Duration = 0.0; // Default to 0 if duration is unavailable
        }
    } else {
        metadata.Title = "Unknown";
        metadata.Artist = "Unknown";
        metadata.Album = "Unknown";
        metadata.Year = "Unknown";
        metadata.Comment = "Unknown";
        metadata.Genre = "Unknown";
        metadata.Duration = 0.0; // Default to 0 if metadata is unavailable
    }
}

// Getter for File_path
std::string File::getFilePath() const {
    return File_path;
}

// Getter for Metadata
MetadataMP3 File::getMetadata() const {
    return metadata;
}

// Setter for File_path
void File::setFilePath(const std::string& filePath) {
    File_path = filePath;

    // Update metadata when File_path is changed
    TagLib::FileRef fileRef(filePath.c_str());
    if (!fileRef.isNull() && fileRef.tag()) {
        TagLib::Tag* tag = fileRef.tag();
        metadata.Title = tag->title().to8Bit(true);
        metadata.Artist = tag->artist().to8Bit(true);
        metadata.Album = tag->album().to8Bit(true);
        metadata.Year = std::to_string(tag->year());
        metadata.Comment = tag->comment().to8Bit(true);
        metadata.Genre = tag->genre().to8Bit(true);

        // Read duration using audio properties
        if (fileRef.audioProperties()) {
            metadata.Duration = fileRef.audioProperties()->lengthInSeconds();
        } else {
            metadata.Duration = 0.0; // Default to 0 if duration is unavailable
        }
    } else {
        metadata.Title = "Unknown";
        metadata.Artist = "Unknown";
        metadata.Album = "Unknown";
        metadata.Year = "Unknown";
        metadata.Comment = "Unknown";
        metadata.Genre = "Unknown";
        metadata.Duration = 0.0; // Default to 0 if metadata is unavailable
    }
}

// Setter for Metadata
void File::setMetadata(const MetadataMP3& metadata) {
    this->metadata = metadata;
}