const int LCD0 = 63;
const int LCD1 = 6;
const int LCD2 = 91;
const int LCD3 = 79;
const int LCD4 = 102;
const int LCD5 = 109;
const int LCD6 = 125;
const int LCD7 = 7;
const int LCD8 = 127;
const int LCD9 = 103;
const int LCDA = 119;
const int LCDB = 124;
const int LCDC = 57;
const int LCDD = 94;
const int LCDE = 121;
const int LCDF = 113;

class SegmentLCD {
  public:
    SegmentLCD(int a, int b, int c, int d, int e, int f, int g) {
      pins[0] = g;
      pins[1] = f;
      pins[2] = e;
      pins[3] = d;
      pins[4] = c;
      pins[5] = b;
      pins[6] = a;
    }
    void display(uint8_t number);

  private:
    int pins[7];
    int a, b, c, d, e, f, g, dp;
    void write(uint8_t value);
};

void
SegmentLCD::write(uint8_t value)
{
    value = ~value;
    for (int i = 0; i < 7; i++) {
    int v = (1 << (6 - i));
    if ((value & v) == 0) {
      digitalWrite(pins[i], LOW);
    } else {
      digitalWrite(pins[i], HIGH);
    }
  }
}

void
SegmentLCD::display(uint8_t number)
{
  number = number & 0x0F;
  switch (number) {
    case 0:
      this->write(LCD0);
      break;
    case 1:
      this->write(LCD1);
      break;
    case 2:
      this->write(LCD2);
      break;
    case 3:
      this->write(LCD3);
      break;
    case 4:
      this->write(LCD4);
      break;
    case 5:
      this->write(LCD5);
      break;
    case 6:
      this->write(LCD6);
      break;
    case 7:
      this->write(LCD7);
      break;
    case 8:
      this->write(LCD8);
      break;
    case 9:
      this->write(LCD9);
      break;
    case 10:
      this->write(LCDA);
      break;
    case 11:
      this->write(LCDB);
      break;
    case 12:
      this->write(LCDC);
      break;
    case 13:
      this->write(LCDD);
      break;
    case 14:
      this->write(LCDE);
      break;
    case 15:
      this->write(LCDF);
      break;
    default:
      return;
  }
}

SegmentLCD  lcd7(2, 3, 4, 5, 6, 7, 8);

void setup() {
  Serial.begin(115200);
  Serial.println("hello, world");
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
  lcd7.display(8);
  delay(1000);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    lcd7.display(i);
    delay(1000);
  }
}
