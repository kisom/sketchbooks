// Walker randomly walks around the screen.
class Walker {
  // x and y store the Walker's current location on the screen.
  int x, y;

  Walker() {
    x = width / 2;
    y = height / 2;
  }

  // Draw the Walker's current position on the screen.
  void draw() {
    stroke(0);
    point(x, y);
  }

  // Randomly choose what direction to step in:
  //   1: right
  //   2: left
  //   3: up
  //   4: down
  // Note that the Walker always takes a step.
  void step() {
    int choice = int(random(4));
    switch (choice) {
    case 0:
      x++;
      break;
    case 1:
      x--;
      break;
    case 2:
      y++;
      break;
    case 3:
      y--;
      break;
    default:
      exit(); // really shouldn't happen
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