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
    inline static Model* fake_taxi = nullptr; // Singleton instance

    std::vector<std::shared_ptr<PlayList>> List_PlayList; // Vector of playlists

    size_t current_File_Index; // Index of the current file in the playlist

    size_t current_PlayList_Index; // Index of the current playlist

    // Pointer to the SDL2 music object for media playback
    Mix_Music* currentMusic;

    // Flag to indicate if media is playing
    bool isPlaying;

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
    /**/bool playCurrentFile();

    // Method when Finished playing a media
    /**/static void StaticOnMediaFinished();

    // Method when Finished playing a media
    /**/void OnMediaFinished();

    // Method to Pause and Resume Media
    /**/void PauseResumeMedia();

    // Method to move to Next media in PlayList
    /**/void NextMedia();

    // Method to move to Previous media in PlayList
    /**/void PrevMedia();

    // Add PlayList name _PlayList_Name to the List_PlayList
    /**/void Add_New_PlayList(std::string& _PlayList_Name);

    // add a file to List_PlayList[_PlayList_index]
    /**/void Add_A_File_To_PlayList(size_t _PlayList_index);
    
    // delete a file in List_PlayList[_PlayList_index]
    /**/void Remove_From_PlayList(size_t _PlayList_index, size_t _File_index);

    // delete a PlayList in List_PlayList[_PlayList_index]
    /**/void Remove_A_PlayList(size_t _PlayList_index);

    /**/std::shared_ptr<PlayList> get_CurrentPlayList() const;

    // Return a PlayList of input index
    /**/std::shared_ptr<PlayList> get_PlayList(int _PlayList_Index) const;

    // Return List
    /**/std::vector<std::shared_ptr<PlayList>> get_List_PlayList() const;
};