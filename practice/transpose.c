int** transpose(int** matrix,
                int matrixSize,
                int* matrixColSize,
                int* returnSize,
                int** returnColumnSizes) {
    int** result = (int**)malloc(sizeof(int*) * (*matrixColSize));
    *returnSize = *matrixColSize;
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*matrixColSize));

    for (int i = 0; i < *matrixColSize; i++) {
        result[i] = (int*)malloc(sizeof(int) * matrixSize);
        (*returnColumnSizes)[i] = matrixSize;
    }

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < *matrixColSize; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}