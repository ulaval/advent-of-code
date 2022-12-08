package com.plucdrol.adventofcode.days;

import lombok.Getter;
import lombok.Setter;

import java.util.ArrayList;
import java.util.List;

@Getter
public class Day08 extends Day {
    private final Long answer1;
    private final Long answer2;
    private final List<List<Tree>> treeGrid;

    public Day08(String input) {
        super(8);
        treeGrid = parseToTreeGrid(input);

        answer1 = treeGrid.stream()
                .mapToLong(trees -> trees.stream().filter(Tree::isVisible).count())
                .sum();

        answer2 = treeGrid.stream()
                .flatMapToLong(treeRow -> treeRow.stream().mapToLong(Tree::getScenicScore))
                .max().orElseThrow();
    }

    private List<List<Tree>> parseToTreeGrid(String input) {
        List<List<Tree>> grid = new ArrayList<>();
        var lines = input.split("\n");
        for (int rowIndex = 0; rowIndex < lines.length; rowIndex++) {

            var row = new ArrayList<Tree>();
            for (var character : lines[rowIndex].toCharArray()) {
                row.add(new Tree(Character.getNumericValue(character)));
            }

            for (int columnIndex = 0; columnIndex < row.size(); columnIndex++) {
                var currentTree = row.get(columnIndex);
                if (columnIndex > 0) {
                    currentTree.setLeft(row.get(columnIndex - 1));
                }
                if (columnIndex < row.size() - 1) {
                    currentTree.setRight(row.get(columnIndex + 1));
                }

                if (rowIndex > 0) {
                    currentTree.setTop(grid.get(rowIndex - 1).get(columnIndex));
                }
            }

            grid.add(row);
        }

        for (int rowIndex = 0; rowIndex < lines.length - 1; rowIndex++) {
            for (int columnIndex = 0; columnIndex < grid.get(rowIndex).size() - 1; columnIndex++) {
                var currentTree = grid.get(rowIndex).get(columnIndex);
                currentTree.setBottom(grid.get(rowIndex + 1).get(columnIndex));
            }
        }
        return grid;
    }

    @Setter
    static class Tree {
        private final long height;
        private Tree left;
        private Tree right;
        private Tree top;
        private Tree bottom;

        public Tree(long height) {
            this.height = height;
        }

        public boolean isVisible() {
            return isVisibleFromLeft(height)
                    || isVisibleFromRight(height)
                    || isVisibleFromTop(height)
                    || isVisibleFromBottom(height);
        }

        private boolean isVisibleFromLeft(long height) {
            return left == null || (left.height < height && left.isVisibleFromLeft(height));
        }

        private boolean isVisibleFromRight(long height) {
            return right == null || right.height < height && right.isVisibleFromRight(height);
        }

        private boolean isVisibleFromTop(long height) {
            return top == null || (top.height < height && top.isVisibleFromTop(height));
        }

        private boolean isVisibleFromBottom(long height) {
            return bottom == null || (bottom.height < height && bottom.isVisibleFromBottom(height));
        }

        public long getScenicScore() {
            return getViewingDistanceLeft(height)
                    * getViewingDistanceRight(height)
                    * getViewingDistanceTop(height)
                    * getViewingDistanceBottom(height);
        }

        private long getViewingDistanceLeft(long height) {
            if (left == null) {
                return 0;
            }
            return left.height < height ? 1 + left.getViewingDistanceLeft(height) : 1;
        }

        private long getViewingDistanceRight(long height) {
            if (right == null) {
                return 0;
            }
            return right.height < height ? 1 + right.getViewingDistanceRight(height) : 1;
        }

        private long getViewingDistanceTop(long height) {
            if (top == null) {
                return 0;
            }
            return top.height < height ? 1 + top.getViewingDistanceTop(height) : 1;
        }

        private long getViewingDistanceBottom(long height) {
            if (bottom == null) {
                return 0;
            }
            return bottom.height < height ? 1 + bottom.getViewingDistanceBottom(height) : 1;
        }

        @Override
        public String toString() {
            return String.format("%sheight: %s", isVisible() ? "(V) " : "", height);
        }
    }
}
