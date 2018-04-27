int COLS = 130;
int ROWS = 130;
int M = 2500;
int STEP = 5;

class City {
  int[][] cells;
  int[][] developed;
  int rows;
  int cols;
  int phi;
  int m, undeveloped;

  City(int ncols, int nrows, int agents) {
    rows = nrows;
    cols = ncols;
    cells = new int[cols+1][rows+1];
    developed = new int[cols+1][rows+1];
    m = agents;
    undeveloped = agents;
    while (agents > 0) {
      int i = int(random(0.0, float(cols-1)));
      int j = int(random(0.0, float(rows-1)));
      if (populated(i, j)) {
        continue;
      }
      agents--;
      cells[i][j] = 1;
    }
  }

  boolean populated(int i, int j) {
    if (cells[i][j] == 1) {
      return true;
    }
    return false;
  }

  void set_phi(int nphi) {
    phi = nphi;
  }

  boolean done() {
    return undeveloped == 0;
  }

  void draw() {
    background(0);
    stroke(255);
    loadPixels();
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        if (populated(i, j)) {
          point(i, j);
        }
      }
    }
  }

  int moore(int i, int j) {
    int neighbours = 0;

    if (i > 0) {
      if (j > 0) {
        if (populated(i-1, j-1)) {
          neighbours++;
        }
      }
      if (j < rows) {
        if (populated(i-1, j+1)) {
          neighbours++;
        }
      }

      if (populated(i-1, j)) {
        neighbours++;
      }
    }

    if (j > 0) {
      if (populated(i, j-1)) {
        neighbours++;
      }
    }
    if (j < rows) {
      if (populated(i, j+1)) {
        neighbours++;
      }
    }

    if (populated(i, j)) {
      neighbours++;
    }

    if (i < cols) {
      if (j > 0) {
        if (populated(i+1, j-1)) {
          neighbours++;
        }
      }
      if (j < rows) {
        if (populated(i+1, j+1)) {
          neighbours++;
        }
      }

      if (populated(i+1, j)) {
        neighbours++;
      }
    }

    return neighbours;
  }


  void step() {
    ArrayList<Move> moves = new ArrayList<Move>();

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        int neighbours = moore(i, j);
        if (developed[i][j] == 1) {
          continue;
        } else if (neighbours >= phi) {
          developed[i][j] = 1; 
        } else if (populated(i, j)) {
          moves.add(new Move(i, j));
        }
      }
    }

    undeveloped = 0;
    for (Move move : moves) {
      while (true) {
        int stepx = int(random(3))-1;
        int stepy = int(random(3))-1;
        int ii, jj;
        stepx += (stepx * randstep());
        stepy += (stepy * randstep());
        ii = constrain(move.i + stepx, 0, cols);
        jj = constrain(move.j + stepy, 0, rows);

        if (populated(ii, jj)) {
          continue;
        }
        cells[ii][jj] = 1;
        cells[move.i][move.j] = 0;
        undeveloped++;
        break;
      }
    }
  }
}


int randstep() {
  while (true) {
    float p = random(STEP);
    float step = random(STEP);

    step *= step;
    if (step < p) {
      int direction = 1;
      if (random(1) < 0.5) {
        direction = -1;
      }
      return int(step * direction);
    }
  }
}

