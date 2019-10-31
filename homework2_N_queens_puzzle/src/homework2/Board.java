package homework2;

import java.util.concurrent.ThreadLocalRandom;

public class Board {
    private int[][] matrix;
    private int size;

    // Creates n x n board with randomly placed queens in each column
    public Board(int size) {
        this.size = size;
        matrix = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = CellFilling.EMPTY.getValue();
            }
        }
        shuffle();
    }

    public boolean isPositionOccupiedByQueen(int row, int col) {
        return matrix[row][col] == CellFilling.QUEEN.getValue();
    }

    // Randomly fills the board with one queen in each column.
    private void shuffle() {
        for (int col = 0; col < size; col++) {
            // nextInt is normally exclusive of the top value,
            // so no need to subtract 1 from size
            int randomRow = ThreadLocalRandom.current().nextInt(0, size);
            matrix[randomRow][col] = CellFilling.QUEEN.getValue();
        }
    }
}
