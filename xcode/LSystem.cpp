//
//  LSystem.cpp
//  LSystem
//
//  Created by Matthew Shanley on 10/13/13.
//  Copyright (c) 2013 Little Secrets Software. All rights reserved.
//

#include "LSystem.h"

using std::cout;
using std::endl;


LSystem::LSystem(string _startString) {
  level = 0;
  curString = _startString;
}

void LSystem::setStart(string _startString) {
  if (level == 0) {
    curString = _startString;
  }
}

void LSystem::addRule(char key, string value) {
  rules[key] = value;
}

void LSystem::removeRule(char key) {
  rules.erase(key);
}

string LSystem::getNextLevel() {
  string result;
  
  // Apply all rules
  for (int i = 0; i < curString.length(); i++) {
    if(rules.find(curString[i]) != rules.end()) {
      result += rules[curString[i]];
    } else {
      result += curString[i];
    }
  }
  
  curString = result;
  level++;
  
  return curString;
}

int LSystem::currentLevelCount() {
  return level;
}
