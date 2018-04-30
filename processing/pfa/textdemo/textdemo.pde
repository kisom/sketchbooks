int fontSize = int(32 * displayDensity);

void setup() {
	fullScreen();
	fill(20);
	PFont font = createFont("SansSerif", fontSize);
	textFont(font);
}

void draw() {
	background(180);
	text("Beacon status", 100, 100);
	text(frameCount, 100, 100+(1.2*fontSize));
}