package advent.of.code.isauc4;

import java.io.IOException;
import java.util.List;

import org.apache.commons.lang3.StringUtils;

import advent.of.code.isauc4.utils.LecteurFichier;

public class Day2 {

    public static void main(String[] args) throws IOException {
        System.out.println(part1());
        System.out.println(part2());
    }

    private static int part1() throws IOException {

        int nbPasswordValide = 0;

        List<String> inputs = LecteurFichier.getCollection("inputDay2.txt");

        for (String input : inputs) {
            String[] tab = input.split(":");

            String[] patternToValidate = tab[0].split(" ");
            String lettreAValider = patternToValidate[1];

            String nombres[] = patternToValidate[0].split("-");
            Integer nbMinimum = Integer.valueOf(nombres[0]);
            Integer nbMaximum = Integer.valueOf(nombres[1]);

            String chaineAValider = StringUtils.stripToEmpty(tab[1]);

            if (chaineAValider.contains(lettreAValider)) {
                int count = StringUtils.countMatches(chaineAValider, lettreAValider);
                if (count >= nbMinimum && count <= nbMaximum) {
                    nbPasswordValide++;
                }
            }
        }
        return nbPasswordValide;
    }

    private static int part2() throws IOException {
        int nbCorrectPassword = 0;

        List<String> inputs = LecteurFichier.getCollection("inputDay2.txt");

        for (String input : inputs) {
            String[] tab = input.split(":");

            String[] patternToValidate = tab[0].split(" ");
            String lettreAValider = patternToValidate[1];

            String nombres[] = patternToValidate[0].split("-");
            Integer occurence1 = Integer.valueOf(nombres[0]) - 1;
            Integer occurence2 = Integer.valueOf(nombres[1]) - 1;

            char[] chaineAValider = StringUtils.stripToEmpty(tab[1]).toCharArray();

            if ((chaineAValider[occurence1] == lettreAValider.charAt(0) && chaineAValider[occurence2] != lettreAValider.charAt(0))
                    || (chaineAValider[occurence1] != lettreAValider.charAt(0) && chaineAValider[occurence2] == lettreAValider.charAt(0))) {

                nbCorrectPassword++;
            }
        }

        return nbCorrectPassword;
    }
}