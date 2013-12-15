//
//  Turtle.cpp
//  LSystem
//
//  Created by Matthew Shanley on 10/13/13.
//  Copyright (c) 2013 Little Secrets Software. All rights reserved.
//

#include "Turtle.h"

//using namespace cinder::Color;


Turtle::Turtle(Vec2f _startingLocation, float _turnAngle, float _lineLength, float _lengthScaleFactor) {
  turnAngle = _turnAngle;
  lineLength = _lineLength;
  lengthScaleFactor = _lengthScaleFactor;
  location = _startingLocation;
  velocity = Vec2f( 1, 0 );
}

void Turtle::draw(string input, Vec2f _location, Vec2f _velocity) {
  location = _location;
  velocity = _velocity;
  
  // Check every character and act accordingly
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == FORWARD_DRAWING_CHAR) {
      moveForwardDrawing();
    } else if (input[i] == FORWARD_WITHOUT_DRAWING_CHAR) {
      moveForwardWithoutDrawing();
    } else if (input[i] == LEFT_TURN_CHAR) {
      turnLeft();
    } else if (input[i] == RIGHT_TURN_CHAR) {
      turnRight();
    } else if (input[i] == PUSH_STATE_CHAR) {
      pushValues();
    } else if (input[i] == POP_STATE_CHAR) {
      popValues();
    } else if (input[i] == SCALE_LINE_LENGTH_UP_CHAR) {
      scaleLineLengthUp();
    } else if (input[i] == SCALE_LINE_LENGTH_DOWN_CHAR) {
      scaleLineLengthDown();
    } else {
      console() << "WARNING: I don't know what do do with the character: " << input[i] << endl;
    }
  }
}


#pragma mark private

void Turtle::moveForwardDrawing() {
  Vec2f newLocation = location + velocity * lineLength;
  
  gl::enableAlphaBlending();
	glLineWidth( 2.0f );
  gl::color(0, 0, 0, 0.47f);
  gl::drawLine(location, newLocation);

  location = newLocation;
}

void Turtle::moveForwardWithoutDrawing() {
  location += velocity * lineLength;
}

void Turtle::turnLeft() {
  velocity.rotate(radians(turnAngle));
}

void Turtle::turnRight() {
  velocity.rotate(-1 * radians(turnAngle));
}

void Turtle::scaleLineLengthUp() {
  lineLength *= lengthScaleFactor;
}

void Turtle::scaleLineLengthDown() {
  lineLength /= lengthScaleFactor;
}

void Turtle::pushValues() {
  locationHistory.push_back(location);
  velocityHistory.push_back(velocity);
}

void Turtle::popValues() {
  location = locationHistory[locationHistory.size() - 1];
  velocity = velocityHistory[velocityHistory.size() - 1];
  
  locationHistory.pop_back();
  velocityHistory.pop_back();
}

float Turtle::radians(float degrees) {
  return degrees * M_PI / 180.0;
}
