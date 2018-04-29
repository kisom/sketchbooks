void setup() {
  fullScreen();
  frameRate(1);
  background(180);
}

void draw() {
    drawFlower(random(width), random(height));
    if (mousePressed) {
	    background(180);
    }
}

void drawFlower(float posx, float posy) {
  pushMatrix();
  translate(posx, posy);
  fill(random(255), random(255), random(255), 200);
  beginShape();

  int n = int(random(4, 10));
  for (int i = 0; i < n; i++) {
    float a = map(i, 0, n, 0, TWO_PI);
    float a1 = map(i+1, 0, n, 0, TWO_PI);
    float r = random(100, 500);
    float x = r * cos(a);
    float y = r * sin(a);
    float x1 = r * cos(a1);
    float y1 = r * sin(a1);
    vertex(0, 0);
    bezierVertex(x, y, x1, y1, 0, 0);
  }

  endShape();
  popMatrix();
}
