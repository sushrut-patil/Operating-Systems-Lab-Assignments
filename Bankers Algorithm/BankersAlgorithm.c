#include <stdio.h>

int main() {
    int P = 5; // Number of processes
    int R = 3; // Number of resources

    int allocationMatrix[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}}; // Allocation Matrix
    int maxMatrix[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};   // MAX Matrix
    int availableResources[3] = {3, 3, 2}; // Available Resources

    int isFinished[P], safeSequence[P], index = 0;
    for (int k = 0; k < P; k++) {
        isFinished[k] = 0;
    }

    int needMatrix[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
    }

    for (int k = 0; k < P; k++) {
        for (int i = 0; i < P; i++) {
            if (isFinished[i] == 0) {
                int flag = 0;
                for (int j = 0; j < R; j++) {
                    if (needMatrix[i][j] > availableResources[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    safeSequence[index++] = i;
                    for (int y = 0; y < R; y++)
                        availableResources[y] += allocationMatrix[i][y];
                    isFinished[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for (int i = 0; i < P; i++) {
        if (isFinished[i] == 0) {
            flag = 0;
            printf("The system is not safe.\n");
            break;
        }
    }

    if (flag == 1) {
        printf("SAFE Sequence: ");
        for (int i = 0; i < P - 1; i++){
            printf("P%d -> ", safeSequence[i]);
        }
        printf("P%d\n", safeSequence[P - 1]);
    }

    return 0;
}