package com.plucdrol.adventofcode.days;

import lombok.Data;
import lombok.Getter;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Data
public class Day03 {

    private static final String PRIORITIES = "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    private final int reponse1;
    private final int reponse2;

    public Day03(String inputTest) {
        var lines = inputTest.split("\n");

        var rucksacks = Arrays.stream(lines).map(Rucksack::new).toList();

        reponse1 = rucksacks.stream()
                .mapToInt(rucksack -> getPriority(rucksack.getRepeatedItem()))
                .sum();

        var rucksackSets = new ArrayList<RucksackSet>();
        for (int i = 0; i < rucksacks.size(); i += 3) {
            rucksackSets.add(new RucksackSet(rucksacks.get(i), rucksacks.get(i + 1), rucksacks.get(i + 2)));
        }

        reponse2 = rucksackSets.stream()
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

    @Override
    public String toString() {
        return String.format("Reponse 1: '%s'; Reponse 2: '%s'", reponse1, reponse2);
    }

    @Getter
    static class Compartment {

        private final List<Character> itemsDistincts;

        public Compartment(String items) {
            itemsDistincts = items.chars().distinct().mapToObj(c -> (char) c).toList();
        }

        public List<Character> getSameItems(Compartment other) {
            return getSameItems(other.itemsDistincts);
        }

        public List<Character> getSameItems(List<Character> other) {
            return itemsDistincts.stream().filter(other::contains).toList();
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

            repeatedItem = compartment1.getItemsDistincts().stream()
                    .filter(c -> compartment2.getItemsDistincts().contains(c))
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
