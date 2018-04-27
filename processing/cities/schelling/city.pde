int STEP = 10;

class City {
  int[][] grid;
  int rows, cols;
  int M;
  float phi;
  int undeveloped;

  City(int m, float iphi) {
    if (m > (height * width)) {
      println("Too many agents.");
      exit();
    }
    rows = height;
    cols = width;
    grid = new int[cols+1][rows+1];
    phi = iphi;
    M = m;
    undeveloped = m;
    while (m > 0) {
      int i = int(random(0.0, float(cols)));
      int j = int(random(0.0, float(rows)));
      if (grid[i][j] != 0) {
        continue;
      }
      int type = int(random(0, 2))+1;
      m--;
      grid[i][j] = type;
    }
  }
  
  void dump() {
     PrintWriter output = createWriter("/tmp/city.txt");
     for (int i = 0; i < cols; i++) {
       for (int j = 0; j < rows; j++) {
         output.print(grid[i][j]);
       }
       output.print("\n");
     } 
     output.flush();
     output.close();
     print("wrote file\n");
  }

  void draw() {
    background(0);
    
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        int p = grid[i][j];
        if (p == 0) {
          continue;
        } else if (p == 1) {
          stroke(0, 255, 0);
        } else if (p == 2) {
          stroke(255, 0, 0);
        }
        point(i, j);
      }
    }
  }

  boolean move(int i, int j) {
    int similar = 1;
    int dissimilar = 0;
    int type = grid[i][j];
    int cell = 0;

    if (i > 0) {
      if (j > 0) {
        cell = grid[i-1][j-1];
        if (cell != 0) {
          if (cell == type) {
            similar++;
          } else {
            dissimilar++;
          }
        }
      }

      if (j < rows) {
        cell = grid[i-1][j+1];
        if (cell != 0) {
          if (cell == type) {
            similar++;
          } else {
            dissimilar++;
          }
        }
      }

      cell = grid[i-1][j];
      if (cell != 0) {
        if (cell == type) {
          similar++;
        } else {
          dissimilar++;
        }
      }
    }

    if (j > 0) {
      cell = grid[i][j-1];
      if (cell != 0) {
        if (cell == type) {
          similar++;
        } else {
          dissimilar++;
        }
      }
    }

    if (j < rows) {
      cell = grid[i][j+1];
      if (cell != 0) {
        if (cell == type) {
          similar++;
        } else {
          dissimilar++;
        }
      }
    }

    cell = grid[i][j];
    if (cell != 0) {
      if (cell == type) {
        similar++;
      } else {
        dissimilar++;
      }
    }

    if (i < cols) {
      if (j > 0) {
        cell = grid[i+1][j-1];
        if (cell != 0) {
          if (cell == type) {
            similar++;
          } else {
            dissimilar++;
          }
        }
      }

      if (j < rows) {
        cell = grid[i+1][j+1];
        if (cell != 0) {
          if (cell == type) {
            similar++;
          } else {
            dissimilar++;
          }
        }
      }

      cell = grid[i+1][j];
      if (cell != 0) {
        if (cell == type) {
          similar++;
        } else {
          dissimilar++;
        }
      }
    }
    /*
    if ((float(similar) / float(similar + dissimilar)) < phi) {
      return true;
    }
    */
    if ((float(dissimilar) / float(similar + dissimilar)) < phi) {
      return true;
    }
    return false;
  }

  void update() {
    PVector[] moves = new PVector[M];
    undeveloped = 0;

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        if (grid[i][j] == 0) {
          continue;
        } else if (move(i, j)) {
          moves[undeveloped++] = new PVector(i, j, grid[i][j]);
        }
      }
    }

    shuffle(moves);
    for (int i = 0; i < undeveloped; i++) {
      PVector move = moves[i];
      if (move == null) {
        continue;
      }
      while (true) {
        int stepx = int(random(3))-1;
        int stepy = int(random(3))-1;
        int ii, jj;
        stepx += (stepx * randstep());
        stepy += (stepy * randstep());
        ii = int(constrain(move.x + stepx, 0, cols));
        jj = int(constrain(move.y + stepy, 0, rows));
        if (grid[ii][jj] == 0) {
          grid[ii][jj] = int(move.z);
          grid[int(move.x)][int(move.y)] = 0;
          break;
        }
      }
    }
  }

  boolean done() {
    return undeveloped == 0;
  }
}

void shuffle(PVector[] moves) {
  for (int i = 1; i < moves.length; i++) {
    PVector temp;
    int j = int(random(1, i));
    temp = moves[j];
    moves[j] = moves[i];
    moves[i] = temp;
  }
}

int randstep() {
  while (true) {
    float p = random(STEP);
    float step = random(STEP);

    if (step < p) {
      int direction = 1;
      if (random(1) < 0.5) {
        direction = -1;
      }
      return int(step * direction);
    }
  }
}
