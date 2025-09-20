#include <iostream>
#include <string>

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
        else if (command == "exit") return 0;
        else std::cout << command << ": command not found" << std::endl;
        break;
      case 'p':
        if (command == "print"){
          std::string message;
          std::getline(std::cin, message);
          while (true) std::cout << message << std::endl;
        }
        else std::cout << command << "command not found" << std::endl;
      default:
        std::cout << command << ": command not found" << std::endl;
        break;
    }
  }
  return 0;
}

