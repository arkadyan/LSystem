#include "cinder/app/AppNative.h"
#include "cinder/Utilities.h"
#include "cinder/gl/gl.h"
#include "cinder/svg/Svg.h"
#include "cinder/cairo/Cairo.h"
#include "LSystem.h"
#include "Turtle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LSystemApp : public AppNative {
  
public:
	void setup();
	void keyDown( KeyEvent event );
	void update();
	void draw();
  
private:
  LSystem system;
  Turtle turtle;
  string result;
  
  void setupRightAngleKochCurve(Vec2f startingLocation);
  void setupAlgae(Vec2f startingLocation);
  void setupLengthChangingLeaf(Vec2f startingLocation);
  void setupBush(Vec2f startingLocation);
  
  void writePngFile();
  void writeSvgFile();
  void renderDrawing(cairo::Context& context);
  
  void quitApp();
  
};

void LSystemApp::setup() {
  Vec2f startingLocation = Vec2f( getWindowWidth() / 2, getWindowHeight() / 2 );
  
  //  setupRightAngleKochCurve(startingLocation);
  //  setupAlgae(startingLocation);
  //  setupLengthChangingLeaf(startingLocation);
  setupBush(startingLocation);
  // More examples can be found here: http://paulbourke.net/fractals/
}


void LSystemApp::setupRightAngleKochCurve(Vec2f startingLocation) {
  // http://forum.openframeworks.cc/index.php?topic=5867.0
  
  system = LSystem("F");
  system.addRule('F', "F+F-F-F+F");
  
  turtle = Turtle(startingLocation);
}

void LSystemApp::setupAlgae(Vec2f startingLocation) {
  // http://paulbourke.net/fractals/lsys_algae_b/
  
  system = LSystem();
  system.setStart("aF");
  
  system.addRule('a', "FFFFFy[++++n][----t]fb");
  system.addRule('b', "+FFFFFy[++++n][----t]fc");
  system.addRule('c', "FFFFFy[++++n][----t]fd");
  system.addRule('d', "-FFFFFy[++++n][----t]fe");
  system.addRule('e', "FFFFFy[++++n][----t]fg");
  system.addRule('g', "FFFFFy[+++fa]fh");
  system.addRule('h', "FFFFFy[++++n][----t]fi");
  system.addRule('i', "+FFFFFy[++++n][----t]fj");
  system.addRule('j', "FFFFFy[++++n][----t]fk");
  system.addRule('k', "-FFFFFy[++++n][----t]fl");
  system.addRule('l', "FFFFFy[++++n][----t]fm");
  system.addRule('m', "FFFFFy[---fa]fa");
  system.addRule('n', "ofFFF");
  system.addRule('o', "fFFFp");
  system.addRule('p', "fFFF[-s]q");
  system.addRule('q', "fFFF[-s]r");
  system.addRule('r', "fFFF[-s]");
  system.addRule('s', "fFfF");
  system.addRule('t', "ufFFF");
  system.addRule('u', "fFFFv");
  system.addRule('v', "fFFF[+s]w");
  system.addRule('w', "fFFF[+s]x");
  system.addRule('x', "fFFF[+s]");
  system.addRule('y', "Fy");
  
  turtle = Turtle(startingLocation, 12, 1);
}

void LSystemApp::setupLengthChangingLeaf(Vec2f startingLocation) {
  // http://paulbourke.net/fractals/lsys_leaf/
  
  system = LSystem();
  system.setStart("a");
  
  system.addRule('F', ">F<");
  system.addRule('a', "F[+x]Fb");
  system.addRule('b', "F[-y]Fa");
  system.addRule('x', "a");
  system.addRule('y', "b");
  
  turtle = Turtle(startingLocation, 45, 1, 1.36);
}

void LSystemApp::setupBush(Vec2f startingLocation) {
  // http://paulbourke.net/fractals/lsys_bush_b/
  
  system = LSystem();
  system.setStart("F");
  
  system.addRule('F', "FF+[+F-F-F]-[-F+F+F]");
  
  turtle = Turtle(startingLocation, 22.5, 10);
}


void LSystemApp::keyDown( KeyEvent event ) {
  if( event.getChar() == 'p' ) {
    writePngFile();
  } else if ( event.getChar() == 'q' ) {
    quitApp();
  }
}

void LSystemApp::update() {
  if (system.currentLevelCount() < 6) {
    result = system.getNextLevel();
  }
}

void LSystemApp::draw() {
	// clear out the window with white
	gl::clear( Color( 255, 255, 255 ) );
  
  turtle.draw(result, Vec2f( 0,  getWindowHeight() ), Vec2f( 1, 0 ));   // input string, starting location, starting velocity
}

void LSystemApp::writePngFile() {
  console() << "Writing image ~/LSystem.png" << endl;
  writeImage(getHomeDirectory() / "LSystem.png", copyWindowSurface());
}

void LSystemApp::writeSvgFile() {
  cairo::Context context(
    cairo::SurfaceSvg(
                      getAppPath() / fs::path("..") / "output.svg",
                      getWindowWidth(), // image.getWidth
                      getWindowHeight()   // image.getHeight
                      )
  );
  renderDrawing( context );
}

void LSystemApp::renderDrawing(cairo::Context& context) {
  context.setSource( ColorA( 0, 0, 0, 1 ) );
  context.paint();
  
  context.setSource( ColorA( 1, 1, 1, 1 ) );
  
}

void LSystemApp::quitApp() {
  console() << "Exiting" << endl;
  quit();
}

CINDER_APP_NATIVE( LSystemApp, RendererGl )
