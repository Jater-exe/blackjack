
#include <string>
class Card {
private:
  char family_;
  std::string name_;
  int value_;

public:
//Constructor
  Card(char family, std::string name, int value);
//Consultor
  char getFamily() const;

  std::string getName() const;

  int getValue() const;

};