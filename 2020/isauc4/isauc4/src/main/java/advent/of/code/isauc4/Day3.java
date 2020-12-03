package advent.of.code.isauc4;

import java.io.IOException;
import java.util.List;

import advent.of.code.isauc4.utils.LecteurFichier;

public class Day3 {

    public static void main(String[] args) throws IOException {

        long nbArbreEvites = nbArbreEvites(1, 1);
        long nbArbreEvites2 = nbArbreEvites(1, 3);
        long nbArbreEvites3 = nbArbreEvites(1, 5);
        long nbArbreEvites4 = nbArbreEvites(1, 7);
        long nbArbreEvites5 = nbArbreEvites(2, 1);
        System.out.println(nbArbreEvites * nbArbreEvites2 * nbArbreEvites3 * nbArbreEvites4 * nbArbreEvites5);
    }

    private static long nbArbreEvites(int bas, int droit) throws IOException {
        List<String> inputs = LecteurFichier.getCollection("inputDay3.txt");

        int nbArbreEvite = 0;
        int rangee = 0;

        for (int i = 0; i < inputs.size(); i += bas) {
            char caractere = inputs.get(i).charAt(rangee % inputs.get(i).length());
            if (caractere == '#') {
                nbArbreEvite++;
            }
            rangee += droit;
        }
        return nbArbreEvite;
    }
}