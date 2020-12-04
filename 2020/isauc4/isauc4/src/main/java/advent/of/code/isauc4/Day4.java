package advent.of.code.isauc4;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

import org.apache.commons.lang3.RegExUtils;
import org.apache.commons.lang3.StringUtils;

import advent.of.code.isauc4.utils.LecteurFichier;

public class Day4 {
    public static void main(String[] args) throws IOException {
        System.out.println("part #1 : " + part1());
        System.out.println("part #2 : " + part2());
    }

    public static long part1() throws IOException {
        List<String> passports = construireInputs();
        long nb = passports.stream()
                .filter(s -> s.contains("byr:") && s.contains("iyr:")
                        && s.contains("eyr:")
                        && s.contains("hgt:")
                        && s.contains("hcl:")
                        && s.contains("ecl:")
                        && s.contains("pid:"))
                .count();

        return nb;
    }

    public static long part2() throws IOException {

        int nbValid = 0;

        List<String> passports = construireInputs();
        passports = passports.stream()
                .filter(s -> s.contains("byr:") && s.contains("iyr:")
                        && s.contains("eyr:")
                        && s.contains("hgt:")
                        && s.contains("hcl:")
                        && s.contains("ecl:")
                        && s.contains("pid:"))
                .collect(Collectors.toList());

        for (String input : passports) {
            String tab[] = RegExUtils.removeFirst(input, " ").split(" ");

            boolean isByr = false;
            boolean isIyr = false;
            boolean isEyr = false;
            boolean isHgt = false;
            boolean isHcl = false;
            boolean isEcl = false;
            boolean isPid = false;
            for (int i = 0; i < tab.length; i++) {

                isByr = isByr(tab, isByr, i);
                isIyr = isIyr(tab, isIyr, i);
                isEyr = isEyr(tab, isEyr, i);
                isHgt = isHgt(tab, isHgt, i);
                isHcl = isHcl(tab, isHcl, i);
                isEcl = isEcl(tab, isEcl, i);
                isPid = isPid(tab, isPid, i);
            }
            if (isByr && isEcl && isEyr && isHcl && isHgt && isIyr && isPid) {
                nbValid++;
            }
        }
        return nbValid;

    }

    private static boolean isPid(String[] tab, boolean isPid, int i) {
        if (tab[i].contains("pid")) {
            String valeur = tab[i].split(":")[1];
            Pattern p1 = Pattern.compile("^\\d{9}$");
            if (p1.matcher(valeur).find()) {
                isPid = true;
            }

        }
        return isPid;
    }

    private static boolean isEcl(String[] tab, boolean isEcl, int i) {
        if (tab[i].contains("ecl")) {
            String valeur = tab[i].split(":")[1];
            Pattern p1 = Pattern.compile("^amb|blu|brn|gry|grn|hzl|oth$");
            if (p1.matcher(valeur).find()) {
                isEcl = true;
            }
        }
        return isEcl;
    }

    private static boolean isHcl(String[] tab, boolean isHcl, int i) {
        if (tab[i].contains("hcl")) {
            String valeur = tab[i].split(":")[1];
            Pattern p1 = Pattern.compile("^#[a-f0-9]{6}$");
            if (p1.matcher(valeur).find()) {
                isHcl = true;
            }

        }
        return isHcl;
    }

    private static boolean isHgt(String[] tab, boolean isHgt, int i) {
        if (tab[i].contains("hgt")) {
            String valeur = tab[i].split(":")[1];
            if (valeur.endsWith("cm")) {
                valeur = StringUtils.removeEnd(valeur, "cm");
                if (Integer.valueOf(valeur) >= 150 && Integer.valueOf(valeur) <= 193) {
                    isHgt = true;
                }
            }
            if (valeur.endsWith("in")) {
                valeur = StringUtils.removeEnd(valeur, "in");
                if (Integer.valueOf(valeur) >= 59 && Integer.valueOf(valeur) <= 76) {
                    isHgt = true;
                }
            }
        }
        return isHgt;
    }

    private static boolean isEyr(String[] tab, boolean isEyr, int i) {
        if (tab[i].contains("eyr")) {
            String valeur = tab[i].split(":")[1];
            if (Integer.valueOf(valeur) >= 2020 && Integer.valueOf(valeur) <= 2030) {
                isEyr = true;
            }
        }
        return isEyr;
    }

    private static boolean isIyr(String[] tab, boolean isIyr, int i) {
        if (tab[i].contains("iyr")) {
            String valeur = tab[i].split(":")[1];
            if (Integer.valueOf(valeur) >= 2010 && Integer.valueOf(valeur) <= 2020) {
                isIyr = true;
            }
        }
        return isIyr;
    }

    private static boolean isByr(String[] tab, boolean isByr, int i) {
        if (tab[i].contains("byr:")) {
            String valeur = tab[i].split(":")[1];
            if (Integer.valueOf(valeur) >= 1920 && Integer.valueOf(valeur) <= 2002) {
                isByr = true;
            }
        }
        return isByr;
    }

    private static List<String> construireInputs() throws IOException {
        List<String> inputs = LecteurFichier.getCollection("inputDay4.txt");
        List<String> inputsPassports = new ArrayList<String>();
        StringBuilder builder = new StringBuilder();
        for (String input : inputs) {

            if (!input.equals("")) {
                builder.append(" " + input);
            } else {
                inputsPassports.add(builder.toString());
                builder = new StringBuilder();
            }
        }
        return inputsPassports;
    }

}