static int x = 0;
static int direction = 1;

void setup() {
  size(640, 800);
  strokeWeight(2);
  stroke(0, 255, 0);
}

void draw() {
  background(0);
  line(x, 0, x, height);
  if (x == width) {
    direction = -1; 
  } else if (x == 0) {
    direction = 1; 
  }
  x = (x + direction);
}
