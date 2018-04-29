void setup() {
	fullScreen();
}

void draw() {
	if (mousePressed) {
		line(pmouseX, pmouseY, mouseX, mouseY);
	}
}
