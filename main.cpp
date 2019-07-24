#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

void fillFileArray(std::string folderLocation);

std::vector<std::string> fileArray;
std::vector<std::string> duplicateArray;

namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {


    if(argc < 2)
    {
        std::cout << "No argument terminating program";
        return 1;
    }

    fillFileArray(argv[1]);

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
}

