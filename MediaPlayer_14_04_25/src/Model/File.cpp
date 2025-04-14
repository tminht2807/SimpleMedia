#include "File.hpp"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>

// Constructor
File::File(const std::string& _filePath) : File_path(_filePath) {
    // Use Taglib to read metadata
    TagLib::FileRef fileRef(_filePath.c_str());
    if (!fileRef.isNull() && fileRef.tag()) {
        TagLib::Tag* tag = fileRef.tag();
        TagLib::AudioProperties* properties = fileRef.audioProperties();

        if (tag) {
            metadata.Title = tag->title().toCString(true);
            metadata.Artist = tag->artist().toCString(true);
            metadata.Album = tag->album().toCString(true);
            metadata.Year = tag->year();
            metadata.Comment = tag->comment().toCString(true);
            metadata.Genre = tag->genre().toCString(true);
        }
        // Get the duration of the audio file
        if (properties) {
            metadata.Duration = properties->lengthInSeconds();
        }
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

// Setter for Metadata
void File::setMetadata(const MetadataMP3& metadata) {
    this->metadata = metadata;
}

// Getter for Duration
double File::getDuration() const {
    return metadata.Duration;
}

// Getter for Title
std::string File::getTitle() const {
    return metadata.Title;
}

// Getter for Artist
std::string File::getArtist() const {
    return metadata.Artist;
}

// Getter for Album
std::string File::getAlbum() const {
    return metadata.Album;
}

// Getter for Year
std::string File::getYear() const {
    return metadata.Year;
}

// Getter for Comment
std::string File::getComment() const {
    return metadata.Comment;
}

// Getter for Genre
std::string File::getGenre() const {
    return metadata.Genre;
}
