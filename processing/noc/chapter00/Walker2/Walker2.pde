// Walker randomly walks around the screen.
class Walker {
  // x and y store the Walker's current location on the screen.
  float x, y;

  Walker() {
    x = width / 2;
    y = height / 2;
  }

  // Draw the Walker's current position on the screen.
  void draw() {
    stroke(0);
    point(x, y);
  }

  // Randomly choose what direction to step in. Two choices are made: 
  // which direction to step in both the x and y axes. Note that it
  // is possible to decide not to move along a given axis.
  void step() {
    float stepx = random(-1, 1);
    float stepy = random(-1, 1);
    x += stepx;
    y += stepy;
  }
}

Walker w;

void setup() {
  size(800, 600);
  background(255);
  w = new Walker();
}

void draw() {
  w.step();
  w.draw();
}