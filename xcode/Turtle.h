//
//  Turtle.h
//  LSystem
//
//  Created by Matthew Shanley on 10/13/13.
//  Copyright (c) 2013 Little Secrets Software. All rights reserved.
//

#ifndef __LSystem__Turtle__
#define __LSystem__Turtle__

#include <string>
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

// http://paulbourke.net/fractals/lsys/
// http://en.wikipedia.org/wiki/L-system
#define FORWARD_DRAWING_CHAR 'F'   // Move forward by line length drawing a line
#define FORWARD_WITHOUT_DRAWING_CHAR 'f'   // Move forward by line length without drawing a line
#define LEFT_TURN_CHAR '-'   // Turn left by turning angle
#define RIGHT_TURN_CHAR '+'   // Turn right by turning angle
//#define REVERSE_DIRECTION_CHAR '|'   // Reverse direction (ie: turn by 180 degrees)
#define PUSH_STATE_CHAR '['   // Push current drawing state onto stack
#define POP_STATE_CHAR ']'   // Pop current drawing state from the stack
//#define INCREMENT_LINE_WIDTH_CHAR '#'   // Increment the line width by line width increment
//#define DECREMENT_LINE_WIDTH_CHAR '!'   // Decrement the line width by line width increment
//#define DRAW_DOT_CHAR '@'   // Draw a dot with line width radius
//#define OPEN_POLYGON_CHAR '{'   // Open a polygon
//#define CLOSE_POLYGON_CHAR '}'   // Close a polygon and fill it with fill colour
#define SCALE_LINE_LENGTH_UP_CHAR '>'   // Multiply the line length by the line length scale factor
#define SCALE_LINE_LENGTH_DOWN_CHAR '<'   // Divide the line length by the line length scale factor
//#define SWAP_LEFT_AND_RIGHT_CHAR '&'   // Swap the meaning of + and -
//#define DECREMENT_TURNING_ANGLE_CHAR '('   // Decrement turning angle by turning angle increment
//#define INCREMENT_TURNING_ANGLE_CHAR ')'   // Increment turning angle by turning angle increment


class Turtle {
  
public:
  
  Turtle(Vec2f _startingLocation = Vec2f(100, 100), float _turnAngle = 90, float _lineLength = 5, float _lengthScaleFactor = 2);
  
  void draw(string input, Vec2f _location, Vec2f _velocity);
  
  
private:
  
  float turnAngle;
  float lineLength;
  float lengthScaleFactor;
  
  Vec2f location;
  Vec2f velocity;
  
  vector<Vec2f> locationHistory;
  vector<Vec2f> velocityHistory;

  void moveForwardDrawing();
  void moveForwardWithoutDrawing();

  void turnLeft();
  void turnRight();
  
  void scaleLineLengthUp();
  void scaleLineLengthDown();
  
  void pushValues();
  void popValues();
  
  float radians(float degrees);

};

#endif /* defined(__LSystem__Turtle__) */
