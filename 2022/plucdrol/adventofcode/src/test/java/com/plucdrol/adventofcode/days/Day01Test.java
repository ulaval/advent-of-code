package com.plucdrol.adventofcode.days;

import lombok.extern.java.Log;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

@Log
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
        var day01 = new Day01(INPUT_TEST);

        log.info(day01.toString());
        assertThat(day01.getAnswer1()).isPositive();
        assertThat(day01.getAnswer2()).isPositive();
    }
}
