// Walker randomly walks around the screen, with a tendency to walk
// to the right.
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
    float r = random(1);

    // 40% chance that Walker will move to the right.
    if (r < 0.4) {
      x++;
    } else if (r < 0.6) {
      x--;
    } else if (r < 0.8) {
      y++;
    } else {
      y--;
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
  // size(800, 600);
  fullScreen();
  w = new Walker();
}

void draw() {
  w.step();
  w.draw();
}