#include <iostream>
#include <sstream>
#include <unistd.h>

class Grid {
public:
  int height, width;
  bool** grid_data;
private:
  bool** shadow_grid_data;

public:
  Grid (int width_, int height_) {
    width = width_;
    height = height_;
    grid_data = new bool*[height_];
    for (int i = 0; i < height_; i++)
      grid_data[i] = new bool[width_];

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
          os << (this->grid_data[i][j] == true ? '#' : '.');
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
  std::cout << "Hello world" << std::endl;

  Grid my_grid = Grid(20, 19);

	// www.conwaylife.com/patterns/pulsar_106.lif
	/*
		Macro to process above
		^imy_grid.grid_data[9/ r]a[9$a] = true;j^
	*/
	my_grid.grid_data[5][3] = true;
	my_grid.grid_data[6][3] = true;
	my_grid.grid_data[7][3] = true;
	my_grid.grid_data[11][3] = true;
	my_grid.grid_data[12][3] = true;
	my_grid.grid_data[13][3] = true;
	my_grid.grid_data[3][5] = true;
	my_grid.grid_data[8][5] = true;
	my_grid.grid_data[10][5] = true;
	my_grid.grid_data[15][5] = true;
	my_grid.grid_data[3][6] = true;
	my_grid.grid_data[8][6] = true;
	my_grid.grid_data[10][6] = true;
	my_grid.grid_data[15][6] = true;
	my_grid.grid_data[3][7] = true;
	my_grid.grid_data[8][7] = true;
	my_grid.grid_data[10][7] = true;
	my_grid.grid_data[15][7] = true;
	my_grid.grid_data[5][8] = true;
	my_grid.grid_data[6][8] = true;
	my_grid.grid_data[7][8] = true;
	my_grid.grid_data[11][8] = true;
	my_grid.grid_data[12][8] = true;
	my_grid.grid_data[13][8] = true;
	my_grid.grid_data[5][10] = true;
	my_grid.grid_data[6][10] = true;
	my_grid.grid_data[7][10] = true;
	my_grid.grid_data[11][10] = true;
	my_grid.grid_data[12][10] = true;
	my_grid.grid_data[13][10] = true;
	my_grid.grid_data[3][11] = true;
	my_grid.grid_data[8][11] = true;
	my_grid.grid_data[10][11] = true;
	my_grid.grid_data[15][11] = true;
	my_grid.grid_data[3][12] = true;
	my_grid.grid_data[8][12] = true;
	my_grid.grid_data[10][12] = true;
	my_grid.grid_data[15][12] = true;
	my_grid.grid_data[3][13] = true;
	my_grid.grid_data[8][13] = true;
	my_grid.grid_data[10][13] = true;
	my_grid.grid_data[15][13] = true;
	my_grid.grid_data[5][15] = true;
	my_grid.grid_data[6][15] = true;
	my_grid.grid_data[7][15] = true;
	my_grid.grid_data[11][15] = true;
	my_grid.grid_data[12][15] = true;
	my_grid.grid_data[13][15] = true;

  for (int i = 0; i < 100; i++) {
    std::cout << "\033[2J\033[1;1H";
    std::cout << my_grid << std::endl;
    my_grid.tick();
    usleep(1000 * 500);
  }
}
