#ifndef Inreader_h
#define Inreader_h

#include <fstream>
#include <string>
#include <iostream>

class Inreader {
public:
  Inreader(std::istream *i);
  
  bool expect(std::string s);
  
  bool peek(std::string s);
  
  void swallowWhitespace();
  
  void swallowLine();
  
  bool readFloat(float &f);
  
  bool readInt(int &i);
  
  bool readToken(std::string &s);
  
  bool good();
  
  bool readLine(std::string &line);
  
  bool upcomingInt();
  
protected:
  bool floatChar(char c);
  
  bool intChar(char c);
  
  bool tokenChar(char c);
  
  std::istream *in;
};

#endif
