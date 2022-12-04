package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

@Getter
public class Day04 extends Day {

    private final long answer1;
    private final long answer2;

    private final List<List<Elf>> elfGroups;

    public Day04(String input) {
        super(4);

        elfGroups = Arrays.stream(input.split("\n"))
                .map(Elf::createGroup)
                .toList();

        answer1 = elfGroups.stream()
                .filter(elves -> elves.get(0).hasAllSections(elves.get(1))
                        || elves.get(1).hasAllSections(elves.get(0)))
                .count();
        answer2 = elfGroups.stream()
                .filter(elves -> elves.get(0).hasAnySection(elves.get(1))
                        || elves.get(1).hasAnySection(elves.get(0)))
                .count();
        ;
    }

    @Getter
    static class Elf {

        private final Set<Integer> assignedSections;

        public Elf(String input) {
            var range = input.split("-");
            assignedSections = IntStream
                    .rangeClosed(Integer.parseInt(range[0]), Integer.parseInt(range[1]))
                    .boxed().collect(Collectors.toSet());
        }

        static List<Elf> createGroup(String input) {
            return Arrays.stream(input.split(",")).map(Elf::new).toList();
        }

        public boolean hasAllSections(Elf other) {
            return assignedSections.containsAll(other.assignedSections);
        }

        public boolean hasAnySection(Elf other) {
            return assignedSections.stream().anyMatch(other.assignedSections::contains);
        }

        @Override
        public String toString() {
            return String.format("Sections: %s",
                    assignedSections.stream()
                            .map(Object::toString)
                            .collect(Collectors.joining(", ")));
        }
    }
}
