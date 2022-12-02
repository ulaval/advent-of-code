package com.plucdrol.adventofcode.days;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day02Test {

    private static final String INPUT_TEST = """
            C Y
            C Z
            B Z
            A Z
            A Z
            A Y
            A Z
            C Y
            C Z
            A Y
            A Y
            B X
            A Y
            C Z
            C Z
            B X
            C Z
            A Z
            B Y
            C Z
            A Y
            C X
            B Y
            A Z
            B Y
            C Z
            B Z
            """;

    @Test
    void doTheBartman() {
        var day02 = new Day02(INPUT_TEST);

        assertThat(day02.getReponse1()).isPositive();
    }

}
