// Walker using a Lévy flight with a Monte Carlo probability function for steps. The
// scale for stepping can be changed by dragging the mouse; a positive Δx will increase
// the scaler, and a negative Δx will decrease it (but not less than 1.0). A wrapping
// function is used to ensure the Walker remains on screen.
float scale = 15;

// probabilityOf returns a qualifier for r.
float probabilityOf(float r) {
  return r; // P = R1
}

float monteCarlo() {
  while (true) {
    float r1 = random(1);
    float p = probabilityOf(r1);
    float r2 = random(1);

    if (r2 < p) {
      return r1;
    }
  }
}

// Walker randomly walks around the screen, with a Lévy walk.
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
    float dx = monteCarlo() * scale;
    float dy = monteCarlo() * scale;
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

void mouseDragged() {
  if (mouseX > pmouseX) {
    scale++;
  } else {
    scale--;
  }
  
  if (scale < 0) {
    scale = 1;
  }

  println("New scaler: ", scale);
}