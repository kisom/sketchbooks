float sdx = 2.5;
float sdy = 2.5;
float meanx = 10;
float meany = 10;

// Walker randomly walks around the screen, with a Gaussian distribution
// for the steps.
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
  void step() {
    float dx = randomGaussian() * sdx + meanx;
    float dy = randomGaussian() * sdy + meany;

    x += (dx * random(-1, 1));
    y += (dy * random(-1, 1));

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