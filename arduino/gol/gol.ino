#define WIDTH 128
#define HEIGHT 64

uint8_t oled_buf[WIDTH * HEIGHT / 8];

// Button setup.
const int	buttonStart = 2;
const int	buttonRight = 3;
const int	buttonLeft = 4;
const int	buttonDown = 5;
const int	buttonUp = 6;

const int	led = 13;


void
setup() {
  Serial.begin(115200);
  Serial.println("OLED Example");


  pinMode(buttonStart, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonUp, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
  Serial.println("setup  complete.");

  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}

bool ledState = false;

void
loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(buttonUp)) {
    ledState = !ledState;
  }

  if (ledState) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
