#include "Inreader.h"
#include <cctype>
#include <sstream>

Inreader::Inreader(std::istream *i) {
  in = i;
}

/**
 Checks whether arugment s is the next value in the input stream
 If it is, it removes it from the input stream
 */
//the same as peek, but if s is next, it 'swallows' s from the input stream. peek does not swallow, always replaced into input stream
bool Inreader::expect(std::string s) {
  swallowWhitespace();
  if (s.size() == 0) {
    return true;
  }
  std::string swallowed;
  char c;
  in->get(c);
  swallowed += c;
  while ((*in) && swallowed.size() < s.size() && swallowed == s.substr(0, swallowed.size())) {
    in->get(c);
    swallowed += c;
  }
  if (swallowed == s) {
    return true;
  }
  else {
    std::string::reverse_iterator it;
    for (it = swallowed.rbegin(); it != swallowed.rend(); ++it) {
      in->putback(*it);
    }
    return false;
  }
}

/**
 Checks whether arugment s is the next value in the input stream
 Does not modify input stream
 */
bool Inreader::peek(std::string s) {
  swallowWhitespace();
  bool retval = false;
  if (s.size() == 0) {
    return true;
  }
  std::string swallowed;
  char c;
  in->get(c);
  swallowed += c;
  while ((*in) && swallowed.size() < s.size() && swallowed == s.substr(0, swallowed.size())) {
    in->get(c);
    swallowed += c;
  }
  if (swallowed == s) {
    retval = true;
  }
  else {
    retval = false;
  }
  std::string::reverse_iterator it;
  for (it = swallowed.rbegin(); it != swallowed.rend(); ++it) {
    in->putback(*it);
  }
  return retval;
}

/** Remove whitespace from input stream */
void Inreader::swallowWhitespace() {
  char c;
  in->get(c);
  while ((*in) && std::isspace(c)) {
    in->get(c);
  }
  in->putback(c);
}

void Inreader::swallowLine() {
  std::string placeholder;
  std::getline(*in, placeholder);
  swallowWhitespace();
}

bool Inreader::readFloat(float &f) {
  swallowWhitespace();
  std::string accum;
  char c;
  in->get(c);
  while ((*in) && floatChar(c)) {
    accum += c;
    in->get(c);
  }
  in->putback(c);
  std::stringstream ss(accum);
  ss >> f;
  return true;
}

bool Inreader::readInt(int &i) {
  swallowWhitespace();
  std::string accum;
  char c;
  in->get(c);
  while ((*in) && intChar(c)) {
    accum += c;
    in->get(c);
  }
  in->putback(c);
  std::stringstream ss(accum);
  ss >> i;
  return true;
  
}

bool Inreader::readToken(std::string &s) {
  swallowWhitespace();
  std::string accum;
  char c;
  in->get(c);
  while ((*in) && tokenChar(c)) {
    accum += c;
    in->get(c);
  }
  in->putback(c);
  s = accum;
  return true;
}

bool Inreader::good() {
  //return (in);
	return in != nullptr;
}

bool Inreader::readLine(std::string &line) {
  getline(*in, line);
  return true;
}

bool Inreader::upcomingInt() {
  swallowWhitespace();
  char c;
  in->get(c);
  in->putback(c);
  return intChar(c);
}

bool Inreader::floatChar(char c) {
  return ( c == 'e'
          || (c >= '0' && c <= '9')
          || c == '.'
          || c == '+'
          || c == '-'
          );
}

bool Inreader::intChar(char c) {
  return ( (c >= '0' && c <= '9') || c == '-');
}

bool Inreader::tokenChar(char c) {
  return !std::isspace(c);
}

