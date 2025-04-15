#pragma once
#include "../Model/PlayList.hpp"
#include "../View/ViewMediaPlay.hpp"

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class ControllerMediaPlay  {
protected:
    static ControllerMediaPlay* fake_taxi;

    std::shared_ptr<PlayList> playlist;  // **Shared model reference**

    ViewMediaPlay view;

    // Pointer to the SDL2 music object for media playback
    Mix_Music* currentMusic;

    size_t current_File_Index; // Index of the current file in the playlist

    size_t current_PlayList_Index; // Index of the current playlist

    // Flag to indicate if media is playing
    bool isPlaying;
public:
    ControllerMediaPlay(std::shared_ptr<PlayList> _playlist) : playlist(_playlist), current_PlayList_Index(0){
        fake_taxi = this;
        // Initialize SDL2
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        }
        // Initialize SDL_mixer with audio format settings
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
            SDL_Quit();
        }
        isPlaying = false;
        currentMusic = nullptr;
    
        current_File_Index = 0;
        current_PlayList_Index = 0;
    }
    // ControllerMediaPlay();
    ~ControllerMediaPlay() = default;

    std::shared_ptr<ViewMediaPlay> Get_View();
    std::shared_ptr<PlayList> Get_PlayList();
    void Show();

    std::string Get_Current_PlayList_Name() const;
    std::string Get_Current_File_Title() const;
    size_t Get_Current_PlayList_Index() const;
    size_t Get_Current_File_Index() const;
    double Get_Current_File_Duration() const;
    void Set_Current_PlayList_Index(const size_t _PlayList_Index);
    
    void Set_PlayList(std::shared_ptr<PlayList> _playlist);
    void Set_View(ViewMediaPlay _view);
    
    void ControlPlayMedia();

    // Method when Finished playing a media
    static void StaticOnMediaFinished();

    // Method when Finished playing a media
    void OnMediaFinished();

    void ControlPauseResumeMedia();
    void ControlNextMedia();
    void ControlPreviousMedia();
};