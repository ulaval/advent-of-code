package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.*;
import java.util.stream.Collectors;

@Getter
public class Day05 extends Day {

    private final String answer1;
    private final String answer2;

    public Day05(String input) {
        super(5);

        var sections = input.split("\n\n");
        answer1 = getAnswer1(sections);
        answer2 = getAnswer2(sections);
    }

    private String getAnswer1(String[] sections) {
        var supplies = new Supplies(sections[0]);
        var moves = Arrays.stream(sections[1].split("\n")).map(Move::new).toList();
        moves.forEach(supplies::moveOneByOne);
        return supplies.getTopCrates();
    }

    private String getAnswer2(String[] sections) {
        var supplies = new Supplies(sections[0]);
        var moves = Arrays.stream(sections[1].split("\n")).map(Move::new).toList();
        moves.forEach(supplies::moveBatch);
        return supplies.getTopCrates();
    }

    @Getter
    static class Supplies {
        private final Map<Integer, Stack> stacks;

        public Supplies(String input) {
            var lines = input.split("\n");
            stacks = new HashMap<>();
            var stackNumbersRow = lines[lines.length - 1].toCharArray();
            for (int rowIndex = 0; rowIndex < stackNumbersRow.length; rowIndex++) {
                if (stackNumbersRow[rowIndex] != ' ')
                    stacks.put(Character.getNumericValue(stackNumbersRow[rowIndex]), stackUp(rowIndex, lines));
            }
        }

        private Stack stackUp(int stackNumber, String[] lines) {
            var crates = new ArrayList<Character>();
            for (int column = 0; column < lines.length - 1; column++) {
                var crate = lines[column].charAt(stackNumber);
                if (crate != ' ') {
                    crates.add(crate);
                }
            }
            return new Stack(crates);
        }


        public void moveOneByOne(Move move) {
            stacks.get(move.getToStack())
                    .add(stacks.get(move.getFromStack())
                            .remove(move.getNumberOfCrates()));
        }

        public void moveBatch(Move move) {
            var stack1 = stacks.get(move.getFromStack());
            var stack2 = stacks.get(move.getToStack());
            var crates = stack1.removeBatch(move.getNumberOfCrates());
            stack2.addBatch(crates);
        }

        public String getTopCrates() {
            List<Character> topCrates = new ArrayList<>();
            for (var truc : stacks.entrySet()) {
                topCrates.add(truc.getKey() - 1, truc.getValue().getTopCrate());
            }
            return topCrates.stream().map(String::valueOf).collect(Collectors.joining());
        }
    }

    @Getter
    static class Stack {
        private final List<Character> crates;

        public Stack(List<Character> crates) {
            this.crates = crates;
        }

        public void add(List<Character> characters) {
            characters.forEach(character -> crates.add(0, character));
        }

        public void addBatch(List<Character> characters) {
            crates.addAll(0, characters);
        }

        public List<Character> remove(int number) {
            var characters = new ArrayList<Character>();
            for (int i = 0; i < number; i++) {
                characters.add(crates.get(i));
            }
            crates.subList(0, number).clear();
            return characters;
        }

        public List<Character> removeBatch(int number) {
            var characters = new ArrayList<Character>();
            for (int i = 0; i < number; i++) {
                characters.add(crates.get(i));
            }
            crates.subList(0, number).clear();
            return characters;
        }

        public Character getTopCrate() {
            return crates.get(0);
        }

        @Override
        public String toString() {
            return String.format("%s:", crates.stream().map(String::valueOf).collect(Collectors.joining()));
        }
    }

    @Getter
    static class Move {

        private final int numberOfCrates;
        private final int fromStack;
        private final int toStack;

        public Move(String input) {
            var words = input.split(" ");
            numberOfCrates = Integer.parseInt(words[1]);
            fromStack = Integer.parseInt(words[3]);
            toStack = Integer.parseInt(words[5]);
        }

        @Override
        public String toString() {
            return String.format("%s : %s -> %s", numberOfCrates, fromStack, toStack);
        }
    }
}
