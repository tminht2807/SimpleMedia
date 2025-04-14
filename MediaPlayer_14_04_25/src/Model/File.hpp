#pragma once
#include <string>

struct MetadataMP3 {
    // structure of MetadataMP3 using Taglib
    std::string Title;
    std::string Artist;
    std::string Album;
    std::string Year;
    std::string Comment;
    std::string Genre;
    double Duration; // Duration in seconds
};

class File {
private:
    std::string File_path;
    MetadataMP3 metadata;

public:
    // Constructor
    File(const std::string& filePath);

    // Getters
    std::string getFilePath() const;
    MetadataMP3 getMetadata() const;
    
    double getDuration() const;

    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getYear() const;
    std::string getComment() const;
    std::string getGenre() const;
    
    // Setters
    void setFilePath(const std::string& _filePath);
    void setMetadata(const MetadataMP3& metadata);
};