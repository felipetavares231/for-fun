#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using namespace std;

char getRandomChar() {
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#!.%¨&*{}[]+-/";
    std::random_device r; // Provides a non-deterministic seed source if available
    std::mt19937 rng(r()); // Standard mersenne twister engine seeded with random_device
    std::uniform_int_distribution<> dist(0, CHARACTERS.size() - 1); // Uniform distribution of indices

    return CHARACTERS[dist(rng)];
}

const int width = 130;
const int height = 50;
const int FPS = 60;

void clearScreen(char buffer[height][width]){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      buffer[i][j] = ' ';
    }
  }
  cout << "\033[2J\033[1;1H";
}

class Particle{
  public:
    int x;
    int y;
    char symbol;
    Particle(int xPos, int yPos){
      x = xPos;
      y = yPos;
      symbol = '.';
    };
};

void createRainParticles(int particleQuantity, vector<Particle>&particles){
  for (int i = 0; i < particleQuantity; i+=4){
    int randX = rand() % width+1;
    for(int j = 0; j < 13; j++){
      Particle newParticle(randX, j);
      particles.push_back(newParticle);
    }
  }

  for (int i = 0; i < particleQuantity; i+=4){
    int randX = rand() % width+1;
    int randY = rand() % height/2;
    for(int j = 0; j < 13; j++){
      int randSpawn = rand() % 101;
      if(randSpawn > 60){
        Particle newParticle(randX, randY);
        particles.push_back(newParticle);
      }
    }
  }
}

void draw(char buffer[height][width], vector<Particle> particles){

  for (int i = 0; i < particles.size(); i++){
    buffer[particles[i].y][particles[i].x] = particles[i].symbol;
  }
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      cout << buffer[i][j];
      if((width-1) - j == 0){
        cout << '\n';
      }
    }
  }
}

void update(vector<Particle> &particles){
    for (int i = 0; i < particles.size(); i++){
      particles[i].symbol = getRandomChar();
      particles[i].y += 1;
      if(particles[i].y >= height){
        particles.erase(particles.begin() + i);
      }
    }

    if(rand() % 101 < 9){
      createRainParticles(120, particles);
    }

}

int main (){
  srand(static_cast<unsigned int>(std::time(nullptr)));

  char buffer[height][width];
  vector<Particle> particles;

  while(true){
    draw(buffer, particles);
    update(particles);
    this_thread::sleep_for(chrono::milliseconds(FPS/1000));
    clearScreen(buffer);
  }
  return 0;
}
