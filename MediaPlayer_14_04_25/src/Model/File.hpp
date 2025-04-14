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
    std::string Get_FilePath() const;
    double Get_Duration() const;
    std::string Get_Title() const;
    std::string Get_Artist() const;
    std::string Get_Album() const;
    std::string Get_Year() const;
    std::string Get_Comment() const;
    std::string Get_Genre() const;
    
    // Setters
    void Set_FilePath(const std::string& _filePath);
    void Set_Duration(const double _Duration);
    void Set_Title(const std::string& _Title);
    void Set_Artist(const std::string& _Artist);
    void Set_Album(const std::string& _Album);
    void Set_Year(const std::string& _Year);
    void Set_Comment(const std::string& _Comment);
    void Set_Genre(const std::string& _Genre);
};