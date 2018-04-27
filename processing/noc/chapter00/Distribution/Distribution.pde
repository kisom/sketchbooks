// Visual display of the distribution of the random() function.

int[] randomCounts;

void setup() {
  size(640, 480);
  randomCounts = new int[20];
}

void draw() {
  background(255);

  int index = int(random(randomCounts.length));
  randomCounts[index]++;

  stroke(0);
  fill(175);

  int w = width / randomCounts.length;

  for (int x = 0; x < randomCounts.length; x++) {
    if (x == index) {
      fill(100);
    } else {
      fill(175);
    }
    rect(x * w, height - randomCounts[x], w - 1, randomCounts[x]);
  }
}