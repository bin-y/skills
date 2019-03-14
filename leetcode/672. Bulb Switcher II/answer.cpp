class Solution {
public:
  int flipLights(int n, int m) {
    if (!n) {
      return 0;
    }
    if (!m) {
      return 1;
    }
    set<uintptr_t> possiblities;
    if (n > 6) {
      n = 6;
    }
    
    uintptr_t lights = 0b111111 >> (6 - n);
    
    possiblities.insert(lights & 0b010101);
    possiblities.insert(lights & 0b101010);
    possiblities.insert(0);
    possiblities.insert(lights & 0b110110);
    if (m > 1) {
      possiblities.insert(lights & 0b011100);
      possiblities.insert(lights & 0b100011);
      possiblities.insert(lights & 0b001001);
      if (m > 2) {
        possiblities.insert(lights);
      }
    }
    
    return possiblities.size();
  }
};