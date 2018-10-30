#include <iostream>
#include <sstream>
#include <unistd.h>
#include <curses.h>


class Grid {
public:
  int height, width;
  bool** grid_data;
private:
  bool** shadow_grid_data;

public:
  Grid (int height_, int width_) {
    width = width_;
    height = height_;
    grid_data = new bool*[height_];
    for (int i = 0; i < height_; i++) {
      grid_data[i] = new bool[width_];
      for (int j = 0; j < this-> width; j++) {
          this->grid_data[i][j] = false;
      }
    }

    shadow_grid_data = new bool*[height_];
    for (int i = 0; i < height_; i++)
      shadow_grid_data[i] = new bool[width_];
  }
    std::string str() {
      std::ostringstream os;
      os << "Width:\t" << this->width << std::endl
        << "Height:\t" << this->height;
      os << std::endl;

      for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this-> width; j++) {
          os << (this->grid_data[i][j] == true ? '@' : ' ');
        }
        os << std::endl;
      }

      return os.str();
    }

    void tick() {
      int neighbour_h, neighbour_w;
      int counts;
      int current;
      for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this-> width; j++) {
          counts = 0;
          for (int h_offset = -1; h_offset <= 1; h_offset++) {
            for (int w_offset = -1; w_offset <= 1; w_offset++) {
                if (w_offset == 0 && h_offset == 0) continue;

                neighbour_h = (((i + h_offset) % this->height) + this->height) % this->height;
                neighbour_w = (((j + w_offset) % this->width) + this->width) % this->width;

                current = this->grid_data[neighbour_h][neighbour_w];
                counts += current;
            }
          }
          bool live = grid_data[i][j];
          if (live && counts < 2) {
            this->shadow_grid_data[i][j] = false;
          } else if (live && (counts == 2 || counts == 3)) {
            this->shadow_grid_data[i][j] = true;
          } else if (live && counts > 3) {
            this->shadow_grid_data[i][j] = false;
          } else if (!live && counts == 3) {
            this->shadow_grid_data[i][j] = true;
          } else {
            this->shadow_grid_data[i][j] = live;
          }
        }
      }
      bool** temp = this->grid_data;
      this->grid_data = this->shadow_grid_data;
      this->shadow_grid_data = temp;
    }

};

std::ostream& operator<< (std::ostream& stream, Grid& obj) {
    return std::cout << obj.str();
}

int main() {
  Grid my_grid = Grid(42, 200);

	// www.conwaylife.com/patterns/pulsar_106.lif
	/*
		Macro to process above
		^imy_grid.grid_data[30/ r]a[30$a] = true;j^
	*/
  my_grid.grid_data[12][36] = true;
  my_grid.grid_data[13][34] = true;
  my_grid.grid_data[13][36] = true;
  my_grid.grid_data[14][24] = true;
  my_grid.grid_data[14][25] = true;
  my_grid.grid_data[14][32] = true;
  my_grid.grid_data[14][33] = true;
  my_grid.grid_data[14][46] = true;
  my_grid.grid_data[14][47] = true;
  my_grid.grid_data[15][23] = true;
  my_grid.grid_data[15][27] = true;
  my_grid.grid_data[15][32] = true;
  my_grid.grid_data[15][33] = true;
  my_grid.grid_data[15][46] = true;
  my_grid.grid_data[15][47] = true;
  my_grid.grid_data[16][12] = true;
  my_grid.grid_data[16][13] = true;
  my_grid.grid_data[16][22] = true;
  my_grid.grid_data[16][28] = true;
  my_grid.grid_data[16][32] = true;
  my_grid.grid_data[16][33] = true;
  my_grid.grid_data[17][12] = true;
  my_grid.grid_data[17][13] = true;
  my_grid.grid_data[17][22] = true;
  my_grid.grid_data[17][26] = true;
  my_grid.grid_data[17][28] = true;
  my_grid.grid_data[17][29] = true;
  my_grid.grid_data[17][34] = true;
  my_grid.grid_data[17][36] = true;
  my_grid.grid_data[18][22] = true;
  my_grid.grid_data[18][28] = true;
  my_grid.grid_data[18][36] = true;
  my_grid.grid_data[19][23] = true;
  my_grid.grid_data[19][27] = true;
  my_grid.grid_data[20][24] = true;
  my_grid.grid_data[20][25] = true;

  initscr();

  for (int i = 0; i < 10000; i++) {
    std::string res = my_grid.str();
    erase();
    // std::cout << "\033[2J\033[1;1H"
    printw(res.c_str());
    refresh();
    my_grid.tick();
    usleep(1000 * 10);
  }
}
