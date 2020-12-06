package isauc4;

import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.Assert;
import org.junit.Test;

import advent.of.code.isauc4.Day5;

public class TestDay5 {

    private Day5 d = new Day5();

    @Test
    public void testSeat1() {
        Pair<Double, Double> paire = d.guessSeats('L', new ImmutablePair<Double, Double>(0d, 7d));
        Assert.assertTrue(0 == paire.getLeft());
        Assert.assertTrue(3 == paire.getRight());
    }

    @Test
    public void testCalculate() {
        Double calculate = d.calculate("BFFFBBFRRR");
        Assert.assertTrue(calculate == 567d);;
    }

    @Test
    public void testCalculate2() {
        Double calculate = d.calculate("FFFBBBFRRR");
        Assert.assertTrue(calculate == 119d);;
    }

    @Test
    public void testCalculate3() {
        Double calculate = d.calculate("BBFFBBFRLL");
        Assert.assertTrue(calculate == 820d);;
    }

}
