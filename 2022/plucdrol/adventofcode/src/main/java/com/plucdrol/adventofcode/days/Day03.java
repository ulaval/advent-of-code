package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Getter
public class Day03 extends Day {

    private static final String PRIORITIES = "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    private final Long answer1;
    private final Long answer2;

    public Day03(String input) {
        super(3);
        var lines = input.split("\n");

        var rucksacks = Arrays.stream(lines).map(Rucksack::new).toList();

        answer1 = (long) rucksacks.stream()
                .mapToInt(rucksack -> getPriority(rucksack.getRepeatedItem()))
                .sum();

        var rucksackSets = new ArrayList<RucksackSet>();
        for (int i = 0; i < rucksacks.size(); i += 3) {
            rucksackSets.add(new RucksackSet(rucksacks.get(i), rucksacks.get(i + 1), rucksacks.get(i + 2)));
        }

        answer2 = (long) rucksackSets.stream()
                .map(RucksackSet::getRepeatedItem)
                .mapToInt(this::getPriority).sum();
    }

    private int getPriority(char c) {

        for (int index = 0; index < PRIORITIES.length(); index++) {
            if (PRIORITIES.charAt(index) == c) {
                return index;
            }
        }
        throw new RuntimeException(String.format("Priority not found (char: %s)", c));
    }

    @Getter
    static class Compartment {

        private final List<Character> distinctItems;

        public Compartment(String items) {
            distinctItems = items.chars().distinct().mapToObj(c -> (char) c).toList();
        }

        public List<Character> getSameItems(Compartment other) {
            return getSameItems(other.distinctItems);
        }

        public List<Character> getSameItems(List<Character> other) {
            return distinctItems.stream().filter(other::contains).toList();
        }
    }

    @Getter
    static class Rucksack extends Compartment {
        private final Compartment compartment1;
        private final Compartment compartment2;

        private final char repeatedItem;

        public Rucksack(String source) {
            super(source);
            compartment1 = new Compartment(source.substring(0, source.length() / 2));
            compartment2 = new Compartment(source.substring(source.length() / 2));

            repeatedItem = compartment1.getDistinctItems().stream()
                    .filter(c -> compartment2.getDistinctItems().contains(c))
                    .findFirst()
                    .orElseThrow(() -> new RuntimeException(String.format("Source: '%s'", source)));
        }
    }

    @Getter
    static class RucksackSet {
        private final char repeatedItem;

        public RucksackSet(Rucksack one, Rucksack two, Rucksack three) {
            repeatedItem = one.getSameItems(two.getSameItems(three))
                    .stream().findFirst().orElseThrow();
        }
    }
}
