//
//  LSystem.h
//  LSystem
//
//  Created by Matthew Shanley on 10/13/13.
//  Copyright (c) 2013 Little Secrets Software. All rights reserved.
//

#ifndef __LSystem__LSystem__
#define __LSystem__LSystem__

#include <iostream>
#include <map>

using std::string;
using std::map;


class LSystem {
  
public:
  
  LSystem(string _startString = "F");
  
  void setStart(string _startString = "F");
  
  void addRule(char key, string value);
  void removeRule(char key);
  
  string getNextLevel();
  
  int currentLevelCount();
  
  
private:
  
  int level;
  string curString;
  
  map<char, string> rules;
  
};

#endif /* defined(__LSystem__LSystem__) */
