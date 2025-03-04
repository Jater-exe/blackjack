#include <string>
class Card {
private:
  char family_;
  std::string name;
  int value;

public:
//Constructor
  Card(char family, std::string name, int value);
//Consultor
  char getFamily() const;
};