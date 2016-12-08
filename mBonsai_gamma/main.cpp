#include "mBonsaiGm.h"
#include <math.h> /* ceil */

// arguments
// 1 nodeNum
// 2 alphabet
// 3 dataset
// 4 loadFactor
// 5 blockSize
// 6 searchFile
void printSpace(mBonsaiGm, uint32_t);

int main(int argc, char *argv[]) {
  uint32_t nodeNum = atoi(argv[1]);
  uint32_t sigma = atoi(argv[2]);
  char *file = argv[3];
  double loadFactor = atof(argv[4]);
  uint32_t blockSize = atoi(argv[5]);
  uint32_t numBlocks =
      ceil((double)(((double)nodeNum / loadFactor) / (double)blockSize));

  mBonsaiGm mbGm(nodeNum, sigma, loadFactor, file, blockSize, numBlocks);
  mbGm.build();
  std::cout << "NodeNumber : " << mbGm.nodeNumberCount << std::endl;
  // mbGm.searchBench(argv[6]);
  printSpace(mbGm, numBlocks);
  return 0;
}

void printSpace(mBonsaiGm mbGm, uint32_t numBlocks) {
  double quotientSpace =
      sdsl::size_in_bytes(mbGm.quotient) / (double)mbGm.nodeNumberCount * 8.0;
  double sumBlockSpace = 0;
  for (uint32_t i = 0; i < numBlocks; i++) {
    sumBlockSpace += (sdsl::size_in_bytes(mbGm.D.darray[i]->dBlock) * 8.0);
  }
  sumBlockSpace /= (double)mbGm.nodeNumberCount;
  double pointerSpace =
      (double)numBlocks * 64.0 / (double)(mbGm.nodeNumberCount * 8.0);
  std::cout << "space in bits (in detail): " << std::endl;
  std::cout << "quotient: " << quotientSpace << std::endl;
  std::cout << "DArray Blocked Gamma: " << sumBlockSpace << std::endl;
  std::cout << "Block Pointers: " << pointerSpace << std::endl;
  // average space per M
  std::cout << "Total Space: " << quotientSpace + sumBlockSpace + pointerSpace
            << std::endl;
}
