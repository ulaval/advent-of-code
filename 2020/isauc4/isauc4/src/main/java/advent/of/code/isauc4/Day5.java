package advent.of.code.isauc4;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;

import advent.of.code.isauc4.utils.LecteurFichier;

public class Day5 {

    public static void main(String[] args) throws IOException {
        Day5 d = new Day5();
        System.out.println(d.part1());
        System.out.println(d.part2());

    }

    public Double calculate(String code) {
        char[] lettres = code.toCharArray();
        //occurence 0
        Pair<Double, Double> rangee = guessRows(lettres[0], new ImmutablePair<>(Double.valueOf(0), Double.valueOf(127)));

        //occurence 1
        rangee = guessRows(lettres[1], rangee);

        //occurence 2
        rangee = guessRows(lettres[2], rangee);

        //occurence 3
        rangee = guessRows(lettres[3], rangee);

        //occurence 4
        rangee = guessRows(lettres[4], rangee);

        //occurence 5
        rangee = guessRows(lettres[5], rangee);

        //occurence 6
        double rangeeFinale = 'F' == lettres[6] ? rangee.getLeft() : rangee.getRight();

        Double id = rangeeFinale * 8;

        //occurence 7
        Pair<Double, Double> seat = guessSeats(lettres[7], new ImmutablePair<Double, Double>(Double.valueOf(0), Double.valueOf(7)));

        //occurence 8
        seat = guessSeats(lettres[8], seat);

        //occurence 9
        double seatFinal = 'L' == lettres[9] ? seat.getLeft() : seat.getRight();

        double chiffreFinal = id + seatFinal;
        return chiffreFinal;

    }

    public double part2() throws IOException {
        List<String> inputs = LecteurFichier.getCollection("inputDay5.txt");
        List<Double> tousLesChiffres = new ArrayList<Double>();

        for (String input : inputs) {
            tousLesChiffres.add(calculate(input));
        }

        Collections.sort(tousLesChiffres);

        for (int i = 0; i < tousLesChiffres.size() - 1; i++) {

            Double double1 = tousLesChiffres.get(i);
            Double double2 = tousLesChiffres.get(i + 1);

            if (!(double1 + 1 == double2)) {
                return tousLesChiffres.get(i) + 1;
            }
        }
        return -1;
    }

    public Double part1() throws IOException {
        List<String> inputs = LecteurFichier.getCollection("inputDay5.txt");
        List<Double> tousLesChiffres = new ArrayList<Double>();

        for (String input : inputs) {
            tousLesChiffres.add(calculate(input));
        }

        return Collections.max(tousLesChiffres);
    }

    public Pair<Double, Double> guessSeats(char lettre, Pair<Double, Double> paire) {

        double gauche = paire.getLeft();
        double droite = paire.getRight();

        double nouveauResultat = Math.floor((gauche + droite) / 2);

        Pair<Double, Double> nouvellePaire = null;
        if (lettre == 'L') {
            nouvellePaire = new ImmutablePair<>(gauche, nouveauResultat);
        } else {
            nouvellePaire = new ImmutablePair<>(nouveauResultat + 1, droite);

        }
        return nouvellePaire;
    }

    public Pair<Double, Double> guessRows(char lettre, Pair<Double, Double> paire) {

        double gauche = paire.getLeft();
        double droite = paire.getRight();

        double nouveauResultat = Math.floor((gauche + droite) / 2);

        Pair<Double, Double> nouvellePaire = null;
        if (lettre == 'F') {
            nouvellePaire = new ImmutablePair<>(gauche, nouveauResultat);
        } else {
            nouvellePaire = new ImmutablePair<>(nouveauResultat + 1, droite);

        }
        return nouvellePaire;
    }
}