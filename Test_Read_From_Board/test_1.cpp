#include <iostream>
#include <thread>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <bitset>
#include <string>
#include <vector>
#include <filesystem>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// g++ test_1.cpp -o output `sdl2-config --cflags --libs` -lSDL2_mixer

size_t index_play = 0;
std::vector<std::string> list;
Mix_Music* currentMusic;
bool isPlaying;
std::string folder_path = "/home/tuan/Music/pop"; // Change this to your folder path


void ChangeVolume(uint8_t _vol){ // vol is range 0-63
    int volume = static_cast<int>(_vol * (MIX_MAX_VOLUME / 64));
    Mix_VolumeMusic(volume);
}

void Pause_Resume(){
    if (isPlaying) { // Check if music is currently playing
        Mix_PauseMusic();
        isPlaying = false;   
    } else {
        Mix_ResumeMusic();
        isPlaying = true;
    }
}

void Next(){
    if (index_play + 1 < list.size()) index_play++;
    else index_play = 0;
    currentMusic = Mix_LoadMUS(list[index_play].c_str());
    Mix_PlayMusic(currentMusic, 1);
    isPlaying = true;
    Mix_HookMusicFinished(Next);
}

void uartListener() {
    bool isConnected = false;
    const char* port = "/dev/ttyACM0"; // Adjust for your system
    int serial_port;
    struct termios tty;
    
    while (true) {
        while (!isConnected) {
            std::cout << "Waiting for connection..." << std::endl;
            sleep(1);
            // Check if the serial port is open
            serial_port = open(port, O_RDWR);

            if (serial_port >= 0) {

                isConnected = true;
                tcgetattr(serial_port, &tty);
                cfsetspeed(&tty, B115200); // Set baud rate
                tcsetattr(serial_port, TCSANOW, &tty);

                std::cout << "Connected to serial port." << std::endl;
            }
        }
    
        uint8_t data; // 1-byte data bus
        int bytes_read = read(serial_port, &data, 1); // Read one byte
        
        if (bytes_read > 0) { // Ensure full byte is received
            uint8_t volume;
            uint8_t play_pause = 0;
            uint8_t nachste = 0;

            volume      = data & 0x3F;
            play_pause  = data & 0x80;
            nachste     = data & 0x40;
            
            // system("clear");
            std::cout << "Binary:" << std::endl;
            std::cout << "    Total receive:" << std::bitset<8>(data) << std::endl;
            std::cout << "    Volume:       " << std::bitset<8>(volume) << std::endl;
            std::cout << "    Play/pause:   " << std::bitset<8>(play_pause) << std::endl;  
            std::cout << "    Next:         " << std::bitset<8>(nachste) << std::endl;
            std::cout << "Volume: " << static_cast<int>(volume * (MIX_MAX_VOLUME / 64)) << std::endl;  

            ChangeVolume(volume); // Change volume

            if (play_pause != 0) Pause_Resume();
            if (nachste != 0) Next();

            tcflush(serial_port, TCIFLUSH);
        } 
        if (tcgetattr(serial_port, &tty) < 0){
            isConnected = false;
            close(serial_port);
        } 
    }
}


int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }
    // Initialize SDL_mixer with audio format settings
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
    }
    
    // Iterate over the directory and push filenames into the vector
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        list.push_back(entry.path().string()); // Store full file path
    }

    currentMusic = Mix_LoadMUS(list[0].c_str());
    Mix_PlayMusic(currentMusic, 1);
    Mix_HookMusicFinished(Next);
    isPlaying = true;

    // Create a separate thread for continuous UART reading
    std::thread uartThread(uartListener);
    uartThread.detach(); // Run in background

    // Keep the main program running
    char cmd;
    do {
        std::cin >> cmd;
        switch(cmd){
            case 'p':{
                Pause_Resume();
                break;
            }
            case 'n':{
                Next();
                break;
            }
            default:{
                break;
            }
        }
    } while (cmd != '0');

    return 0;
}
