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

size_t index_play = 0;
std::vector<std::string> list;
Mix_Music* currentMusic;
bool isPlaying;
std::string folder_path = "/home/tuan/Music/pop"; // Change this to your folder path


void uartListener(int serial_port) {
    while (true) {
        uint8_t data; // 1-byte data bus
        uint8_t volume;
        uint8_t play;
        int bytes_read = read(serial_port, &data, 1); // Read one byte


        if (bytes_read > 0) { // Ensure full byte is received
            volume = data & 0x7F;
            play = data & 0x80;

            std::cout << "Binary:\n";
            std::cout << "    Total receive: " << std::bitset<8>(data) << std::endl;
            std::cout << "    Volume:        " << std::bitset<8>(volume) << std::endl;
            std::cout << "    Play:          " << std::bitset<8>(play) << std::endl;  

            tcflush(serial_port, TCIFLUSH);
        } 

        usleep(20000); // Wait 20ms before reading again
    }
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
    Mix_HookMusicFinished(Next);
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

    // const char* port = "/dev/ttyUSB0"; // Adjust for your system
    // int serial_port = open(port, O_RDWR);

    // if (serial_port < 0) {
    //     std::cerr << "Error opening UART\n";
    //     return 1;
    // }

    // struct termios tty;
    // if (tcgetattr(serial_port, &tty) < 0) {
    //     std::cerr << "Error getting UART attributes\n";
    //     close(serial_port);
    //     return 1;
    // }

    // cfsetspeed(&tty, B115200); // Set baud rate
    // if (tcsetattr(serial_port, TCSANOW, &tty) < 0) {
    //     std::cerr << "Error setting UART attributes\n";
    //     close(serial_port);
    //     return 1;
    // }

    // // Create a separate thread for continuous UART reading
    // std::thread uartThread(uartListener, serial_port);
    // uartThread.detach(); // Run in background

    // Keep the main program running
    char cmd;
    do {
        std::cout << " >> Enter command: ";
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

    // close(serial_port);
    return 0;
}
