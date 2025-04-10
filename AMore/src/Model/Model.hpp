#pragma once
#include "PlayList.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <atomic>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class Model {
protected:
    std::vector<std::shared_ptr<PlayList>> List_PlayList; // Vector of playlists

    size_t current_File_Index; // Index of the current file in the playlist

    size_t current_PlayList_Index; // Index of the current playlist

    // Pointer to the SDL2 music object for media playback
    Mix_Music* currentMusic;

    // Flag to indicate if media is playing
    std::atomic<bool> isPlaying;

public:
    // Constructor
    /**/Model();

    // Destructor
    virtual ~Model() = default;

    // Getter Setter for current_File_Index, current_PlayList_Index
    /**/size_t getCurrentFileIndex() const;
    /**/void setCurrentFileIndex(size_t index);
    /**/size_t getCurrentPlayListIndex() const;
    /**/void setCurrentPlayListIndex(size_t index);

    // Method to get the list of playlists
    std::vector<std::shared_ptr<PlayList>> getPlaylists() const;

    // Method to play the current file: List_PlayList[_current_PlayList_Index]->getFile(_current_File_Index)
    /**/void playCurrentFile(size_t _current_PlayList_Index, size_t _current_File_Index);

    // Add PlayList name _PlayList_Name to the List_PlayList
    /**/void Add_New_PlayList(std::string& _PlayList_Name);

    // add a file to List_PlayList[_PlayList_index]
    /**/void Add_A_File_To_PlayList(size_t _PlayList_index);
    
    // delete a file in List_PlayList[_PlayList_index]
    /**/void Remove_From_PlayList(size_t _PlayList_index, size_t _File_index);

    // delete a PlayList in List_PlayList[_PlayList_index]
    /**/void Remove_A_PlayList(size_t _PlayList_index);

    std::shared_ptr<PlayList> getCurrentPlayList() const;
};