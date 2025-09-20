#include <iostream>
#include <string>
#include <sys/select.h>
#include <unistd.h>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string command;

  while(true){

    std::cout << "$ ";
    std::cin >> command;

    switch(command[0]){
      case 'e':

        if(command == "echo"){
          std::string message;
          std::getline(std::cin, message);
          std::cout << message << std::endl;
        }
        else std::cout << command << ": command not found" << std::endl;
        break;

      case 'p':
        if (command == "print"){
          std::string message;
          std::getline(std::cin, message);

          
          while (true) {
            std::cout << message << std::endl;
            struct timeval tv = {0, 0};
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0){
              char c;
              if (read(STDIN_FILENO, &c, 1) == 0) break;
            }
            usleep(100000);
          }
        
            /*
          while (true){
            std::cout << message << std::endl;
            char c;
            if (read(STDIN_FILENO, &c, 1) == 0) break;
            usleep(100000);
          }
            */
        }
        else std::cout << command << "command not found" << std::endl;
        break;

      case '\\':
        if (command == "\\q") return 0;
        else std::cout << command << ": command not found" << std::endl;
        break;

      default:
        std::cout << command << ": command not found" << std::endl;
        break;
    }
  }
  return 0;
}

