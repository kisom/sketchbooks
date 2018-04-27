City city;

void setup() {
  size(150, 150);
  city = new City(width, height, 2500);
  city.set_phi(5);
  city.draw();
  save("initial.png");
}

int t = 0;
int done = 0;

void draw() {
  if (!city.done()) {
    t++;
    city.step();
    city.draw();
    saveFrame("frames/####.png");
    print(city.undeveloped + "\n");
  } else if (done == 0) {
    print("Complete at t = " + t + "\n");
    done = 1;
    save("clusters.png");
  }
}

