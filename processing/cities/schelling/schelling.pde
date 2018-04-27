City city;

void setup() {
	size(35, 35);
	city = new City(1160, 0.5);
	city.draw();
	save("/tmp/city.png");
	city.dump();
}

int t = 0;

void draw() {
	if (!city.done()) {
		saveFrame("frames/#######.png");
		println(city.undeveloped);
		city.update();
		city.draw();
		t++;
	} else {
		println("Simulation complete at t = " + t);
		exit();
	}
}
