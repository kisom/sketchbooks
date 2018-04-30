void setup() {
	fullScreen(P2D);
	noFill();
	colorMode(HSB, 360, 99, 99);
	strokeWeight(2);
	stroke(210);
	background(0, 0, 99);
}

void draw() {
	if (mousePressed) {
		line(pmouseX, pmouseY, mouseX, mouseY);
		if (random(1) < 0.5) {
			PVector dir = new PVector(mouseX - pmouseX, mouseY - pmouseY);
			float a = dir.heading();
			drawSpiral(mouseX, mouseY, a);
		}

		if (random(1) < 0.5) {
			drawFlower(mouseX, mouseY);
		}
	}
}

void keyPressed() {
	background(0, 0, 99);
}

void drawFlower(float xc, float yc) {
	println("drawing flower");
	pushMatrix();
	pushStyle();
	noStroke();
	
	translate(xc, yc);
	fill(random(60,79), random(50, 60), 85, 190);

	beginShape();
	int numLobes = int(random(4, 10));
	for (int i = 0; i < numLobes; i++) {
		float a = map(i, 0, numLobes, 0, TWO_PI);
		float a1 = map(i+1, 0, numLobes, 0, TWO_PI);
		float r = random(10, 50) * displayDensity;

		float x = r * cos(a);
		float x1 = r * cos(a1);
		float y = r * sin(a);
		float y1 = r * sin(a1);

		vertex(0, 0);
		vertex(0, 0);
		bezierVertex(x, y, x1, y1, 0, 0);
	}
	endShape();
	popStyle();
	popMatrix();
}

void drawSpiral(float xc, float yc, float a) {
  println("drawing spiral");
  pushMatrix();
  pushStyle();
  translate(xc, yc);  
  rotate(PI + a);
  noFill();
  beginShape();
  float maxt = random(5, 10);
  float maxr = random(20, 70) * displayDensity;
  float sign = (random(1) < 0.5) ? -1 : +1;  
  float x0 = maxr * cos(sign);
  float y0 = maxr * sin(sign);
  for (float t = 1; t < maxt; t += 0.5) {
    float r = maxr/t;
    float x = r  * cos(sign * t) - x0;
    float y = r  * sin(sign * t) - y0;
    vertex(x, y);
  }
  endShape();
  noStroke();
  fill(random(310, 360), 80, 80);
  float x1 = (maxr/maxt) * cos(sign * maxt) - x0;
  float y1 = (maxr/maxt) * sin(sign * maxt) - y0;
  float r = random(5, 10) * displayDensity;
  ellipse(x1, y1, r, r);
  popStyle();
  popMatrix();
}
