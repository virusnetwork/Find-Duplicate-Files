//  Find-Duplicate-files a program to find duplicate files
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

//function for finding duplicate files and inserting them into duplicateArray
void fillFileArray(std::string folderLocation);

std::vector<std::string> duplicateArray;

namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {


    if(argc < 2)
    {
        std::cout << "No argument terminating program";
        return 1;
    }

    fillFileArray(argv[1]);

    //prints out all duplicate files and uses boosts remove function, should work on any system
    for (auto &element : duplicateArray)
    {
        std::cout << "\t" << element <<  std::endl;
        fs::remove(element);
    }

    return 0;
}


void fillFileArray(std::string folderLocation) {
    fs::path folderPath(folderLocation);
    fs::recursive_directory_iterator end_itr;
    std::vector<std::string> fileArray;

    // cycle through the directory
    for (fs::recursive_directory_iterator itr(folderPath); itr != end_itr; ++itr) {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();

            bool fileTest = false;
            for (auto element: fileArray) {
                if (fs::file_size(current_file) == fs::file_size(element)) {
                    fileTest = true;
                }
            }

            if (fileTest) {
                duplicateArray.push_back(current_file);
            } else {
                fileArray.push_back(current_file);
            }
        }
    }
    //empty vector to save memory as file array no longer needed
    std::vector<std::string>().swap(fileArray);
}

