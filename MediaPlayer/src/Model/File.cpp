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

    // Getters
std::string File::Get_FilePath() const{
    return File_path;
}
double File::Get_Duration() const{
    return metadata.Duration;
}
std::string File::Get_Title() const{
    return metadata.Title;
}
std::string File::Get_Artist() const{
    return metadata.Artist;
}
std::string File::Get_Album() const{
    return metadata.Album;
}
std::string File::Get_Year() const{
    return metadata.Year;
}
std::string File::Get_Comment() const{
    return metadata.Comment;
}
std::string File::Get_Genre() const{
    return metadata.Genre;
}

// Setters
void File::Set_Duration(const double _Duration){
    metadata.Duration = _Duration;
}
void File::Set_Title(const std::string& _Title){
    metadata.Title = _Title;
}
void File::Set_Artist(const std::string& _Artist){
    metadata.Artist = _Artist;
}
void File::Set_Album(const std::string& _Album){
    metadata.Album = _Album;
}
void File::Set_Year(const std::string& _Year){
    metadata.Year = _Year;
}
void File::Set_Comment(const std::string& _Comment){
    metadata.Comment = _Comment;
}
void File::Set_Genre(const std::string& _Genre){
    metadata.Genre = _Genre;
}
