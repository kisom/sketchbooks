// Walker randomly walks around the screen, with a tendency to walk
// to the mouse pointer.
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

  // randomStep takes a random step (or not) along in both the x and y axes.
  void randomStep() {
    float dx = random(-1, 1);
    float dy = random(-1, 1);

    x += dx;
    y += dy;
  }

  // followMouse moves towards the mouse.
  void followMouse() {
    if (mouseX < x) {
      x--;
    }
    // Notice that we don't change x if mouseX == x.
    else if (mouseX >= x) {
      x++;
    }

    if (mouseY < y) {
      y--;
    }
    // Notice that we don't change y if mouseY == y.
    else if (mouseY >= y) {
      y++;
    }
  }

  // Randomly choose what direction to step in. Two choices are made:
  // which direction to step in both the x and y axes. Note that it
  // is possible to decide not to move along a given axis.
  void step() {
    float pr = random(1);

    if (pr <= 0.5) {
      followMouse();
    } else {
      randomStep();
    }

    this.wrapXY();
  }

  void wrapXY() {
    // Ensure the Walker stays on screen.
    if (x > width) {
      x = 0;
    }

    if (x < 0) {
      x = width;
    }

    if (y > height) {
      y = 0;
    }

    if (y < 0) {
      y = height;
    }
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