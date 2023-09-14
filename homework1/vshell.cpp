#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <fstream>
#include <sstream>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

// Функция для выполнения команды pwd
void printWorkingDirectory() {
    std::cout << fs::current_path() << std::endl;
}

// Функция для выполнения команды ls
void listDirectory(const std::string& path) {
    fs::directory_iterator end;

    for(fs::directory_iterator iter(path); iter != end; ++iter) {
        std::cout << iter->path().filename() << std::endl;
    }
}

// Функция для выполнения команды cd
void changeDirectory(const std::string& path) {
    fs::current_path(path);
}

// Функция для выполнения команды cat
void printFileContents(const std::string& path) {
    std::ifstream file(path);

    if(file.is_open()) {
        std::cout << file.rdbuf() << std::endl;
        file.close();
    } else {
        std::cerr << "Failed to open file: " << path << std::endl;
    }
}

bool loadImage(const std::string& imagePath) {
    // Извлекаем файл изображения (tar, zip) во временный каталог
    std::string tempDir = "/tmp/virtual_fs";
    fs::remove_all(tempDir);
    fs::create_directory(tempDir);

    // Извлекаем файл изображения с помощью соответствующего инструмента (tar, unzip и т. д.)
    // Заменяем пример команды фактической командой для извлечения файла изображения
    std::string extractCommand = "tar -xf " + imagePath + " -C " + tempDir;
    int result = std::system(extractCommand.c_str());

    if (result != 0) {
        std::cerr << "Не удалось извлечь файл изображения: " << imagePath << std::endl;
        return false;
    }

    // Устанавливаем текущий путь к извлеченному каталогу
    fs::current_path(tempDir);
    return true;
}

int main(int argc, char* argv[]) {
    std::string scriptFile;
    std::string imageFile;

    // Опции командной строки
    po::options_description desc("Options");
    desc.add_options()
        ("script", po::value<std::string>(&scriptFile), "Script file")
        ("image", po::value<std::string>(&imageFile), "Image file");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    // Если указан файл изображения, загружаем виртуальную файловую систему
    if (!imageFile.empty()) {
        if (loadImage(imageFile)) {
            std::cout << "Виртуальная файловая система загружена." << std::endl;
        } else {
            return 1;
        }
    }

    // Если указан файл со скриптом, загрузить команды из него
    if (!scriptFile.empty()) {
        std::ifstream script(scriptFile);
        if (script.is_open()) {
            std::string command;
            while (std::getline(script, command)) {
                if (command == "pwd") {
                    printWorkingDirectory();
                } else if (command == "ls") {
                    listDirectory(fs::current_path().string());
                } else if (command.substr(0, 3) == "cd ") {
                    std::string path = command.substr(3);
                    changeDirectory(path);
                } else if (command.substr(0, 4) == "cat ") {
                    std::string path = command.substr(4);
                    printFileContents(path);
                } else if (command == "exit") {
                    break;
                } else {
                    std::cerr << "Unknown command" << std::endl;
                }
            }
            script.close();
        } else {
            std::cerr << "Failed to open script file: " << scriptFile << std::endl;
            return 1;
        }
    } else {
        // Интерактивный режим, ожидание команд от пользователя
        std::string command;

        while (true) {
            std::cout << "> ";
            std::getline(std::cin, command);

            if (command == "pwd") {
                printWorkingDirectory();
            } else if (command == "ls") {
                listDirectory(fs::current_path().string());
            } else if (command.substr(0, 3) == "cd ") {
                std::string path = command.substr(3);
                changeDirectory(path);
            } else if (command.substr(0, 4) == "cat ") {
                std::string path = command.substr(4);
                printFileContents(path);
            } else if (command == "exit") {
                break;
            } else {
                std::cerr << "Unknown command" << std::endl;
            }
        }
    }

    return 0;
}
