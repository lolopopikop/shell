#include <iostream>
#include <string>
#include <sys/select.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>

void net(std::string command){
  std::cout << command << ": command not found" << std::endl;
}

//            4.
void history(std::string command){
  std::ofstream file("kubsh_history", std::ios::app);
  file << command << std::endl;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string command, full_command;

  while(true){

    std::cout << "$ ";
    std::cin >> command;

    if (command != "print_history" && command != "clear_history")
      history(command);

    switch(command[0]){

      case 'e':
        //         5.
        if(command == "echo"){
          std::string message;
          std::getline(std::cin, message);
          std::cout << message << std::endl;
        }
        else net(command);
        break;

      case 'p':
        //         6.
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
        }
        
        else if (command == "print_history"){
          std::ifstream file("kubsh_history");
          if (!file)
            std::cout << "No history yet!" << std::endl;
          else{
            std::string command;
            while (std::getline(file, command))
              std::cout << command << std::endl;
          }
        }

        else net(command);
        break;

      case '\\':
        //          3.
        if (command == "\\q") {
          return 0;
        }
        else net(command);
        break;
      
      case 'c':
        if (command == "clear_history"){
          if (std::remove("kubsh_history") == 0)
            std::cout << "History cleared!" << std::endl;
          else
            std::cout << "No history file found!" << std::endl;
        }
        else net(command);
        break;

      default:
        net(command);
        break;
    }
  }
  return 0;
}
