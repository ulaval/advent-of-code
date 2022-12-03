package com.plucdrol.adventofcode.days;

import lombok.Data;

import java.util.Arrays;

@Data
public class Day01 {

    private final int reponse1;
    private final int reponse2;

    public Day01(String input) {
        var groupesValeurs = input.split("\n\n");
        var sommes = Arrays.stream(groupesValeurs).map(this::calculerSomme).sorted().toList();

        var top3 = sommes.subList(sommes.size() - 3, sommes.size());

        reponse1 = top3.get(top3.size() - 1);
        reponse2 = top3.stream().mapToInt(Integer::intValue).sum();
    }

    private int calculerSomme(String groupe) {
        String[] valeurs = groupe.split("\n");
        return Arrays.stream(valeurs).mapToInt(Integer::parseInt).sum();
    }

    @Override
    public String toString() {
        return String.format("Reponse 1: '%s'; Reponse 2: '%s'", reponse1, reponse2);
    }
}
