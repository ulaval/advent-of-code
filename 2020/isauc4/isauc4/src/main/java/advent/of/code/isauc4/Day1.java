package advent.of.code.isauc4;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

import advent.of.code.isauc4.utils.LecteurFichier;

public class Day1 {

    public static void main(String[] args) throws Exception {
        System.out.println("Part #1 " + part1());
        System.out.println("Part #2 " + part2());
    }

    private static Integer part1() throws IOException {

        List<String> temp = LecteurFichier.getCollection("inputDay1.txt");
        List<Integer> notes = temp.stream().map(t -> Integer.valueOf(t)).collect(Collectors.toList());

        for (int i = 0; i < notes.size(); i++) {
            for (int ii = i + 1; ii < notes.size(); ii++) {
                if (notes.get(i).intValue() + notes.get(ii).intValue() == 2020) {
                    return notes.get(i).intValue() * notes.get(ii).intValue();
                }
            }
        }
        return -1;
    }

    private static Integer part2() throws IOException {

        List<String> temp = LecteurFichier.getCollection("inputDay1.txt");
        List<Integer> notes = temp.stream().map(t -> Integer.valueOf(t)).collect(Collectors.toList());

        for (int i = 0; i < notes.size(); i++) {
            for (int ii = i + 1; ii < notes.size(); ii++) {
                for (int iii = i + 2; iii < notes.size(); iii++) {
                    if (notes.get(i).intValue() + notes.get(ii).intValue() + notes.get(iii).intValue() == 2020) {
                        return notes.get(i).intValue() * notes.get(ii).intValue() * notes.get(iii).intValue();
                    }
                }
            }
        }
        return -1;
    }
}