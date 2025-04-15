#pragma once
#include "PlayList.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <atomic>

class List {
protected:
    std::vector<std::shared_ptr<PlayList>> List_PlayLists; // Vector of playlists
    // std::vector<std::string> List_Names;
public:
    // Constructor
    List();

    // Destructor
    virtual ~List() = default;

    // Method to get the list of playlists
    std::vector<std::shared_ptr<PlayList>> Get_List() const;

    std::vector<std::string> Get_List_Names() const;

    // void Set_List_Names(std::string _New_Name, size_t _PlayList_index);

    // Return a PlayList of input index
    std::shared_ptr<PlayList> Get_A_PlayList(int _PlayList_Index) const;

    // Add PlayList name _PlayList_Name to the List_PlayLists
    bool Add_PlayList(std::string& _PlayList_Name);

    // delete a PlayList in List_PlayLists[_PlayList_index]
    void Remove_PlayList(size_t _PlayList_index);
};