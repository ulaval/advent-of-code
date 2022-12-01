package com.patate.poil;

import java.util.Arrays;

import org.junit.jupiter.api.Test;

public class Day01Test {

    private static final String INPUT_TEST = """
            5436
            2522
            4455
            4808
            3644
            2344
            1671
                        
            45637
            
            5634
            2755
            3537
            5047
            1878
            4820
            5959
            5412
            6458
            1544
            3606
            4374
            2743
            3946

            3013
            1604
            1574
            3617
            5992
            7090
            3693
            7543
            3619
            5161
            1137
            """;

    @Test
    void doTheBartman() {
        var groupesValeurs = INPUT_TEST.split("\n\n");

        var sommes = Arrays.stream(groupesValeurs).map(this::calculerSomme).sorted().toList();

        var top3 = sommes.subList(sommes.size() - 3, sommes.size());

        var reponse1 = top3.get(top3.size() - 1);
        var reponse2 = top3.stream().mapToInt(Integer::intValue).sum();
    }

    private int calculerSomme(String groupe) {
        String[] valeurs = groupe.split("\n");
        return Arrays.stream(valeurs).mapToInt(Integer::parseInt).sum();
    }
}
