#include <iostream> 
#include <fstream>
#include "AVLTree.h"
#include "LinkedList.h"

void ParseCSV(const std::string filename, AVLTree<std::string, std::string> &tree);
void DisplayMeanings(const std::string word, AVLTree<std::string, std::string> &tree);
std::string &Captalize(std::string &str);
std::string &ToLowerCase(std::string &str);

int main() {
  std::cout << "\t\t*** Dictionary ***" << '\n' << std::endl;

  AVLTree<std::string, std::string> tree;
  std::cout << "** Loading data. Please wait...." << std::endl;
  ParseCSV("dictionary.csv", tree);
  std::cout << "\n\n";

  for (;;) {
    std::string word;
    std::cout << "Enter a word (CONTROL + C to exit): ";
    std::cin >> word;

    DisplayMeanings(ToLowerCase(word), tree);
    std::cout << "\n\n";
  }
}

void ParseCSV(const std::string filename, AVLTree<std::string, std::string> &tree) {
  std::string line;
  std::string word, meaning;
  std::ifstream file(filename);
  getline(file, line);

  size_t entries = 0;

  while (getline(file, line)) {
    size_t idx = line.find_first_of(',');
    word = line.substr(0, idx);
    meaning = line.substr(idx + 1);

    if (meaning.find('"') != meaning.npos) {
      size_t idx = meaning.find('"');
      meaning = meaning.substr(idx + 1);
      idx = meaning.find('"');
      meaning = meaning.substr(0, idx);
    }
    tree.Insert(word, Captalize(meaning));
    line.clear();
    std::cout << ++entries << " words loaded!" << '\r';
  }
  std::cout << std::endl;
}

void DisplayMeanings(const std::string word, AVLTree<std::string, std::string> &tree) {
  AVLTree<std::string, std::string>::TreeNode *node = tree.Search(word);
  if (node == nullptr) {
    std::cout << "Error: " << "\"" << word << "\"" << " is not present in the record." << std::endl;
    return;
  }

  std::cout << "Meanings: " << std::endl;
  auto array = node->meaning.ToArray();
  size_t len = node->meaning.GetLength();

  for (size_t i = 0; i < len; i++) {
    std::cout << '\t' << "* " << array[i] << std::endl;
  }
}

std::string &Captalize(std::string &str) {
  str[0] = toupper(str[0]);
  return str;
}

std::string &ToLowerCase(std::string &str) {
  for (size_t i = 0, len = str.size(); i < len; i++) {
    str[i] = tolower(str[i]);
  }

  return str;
}
