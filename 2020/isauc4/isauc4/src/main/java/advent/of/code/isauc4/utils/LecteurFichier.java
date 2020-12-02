package advent.of.code.isauc4.utils;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

public class LecteurFichier {

    public static List<String> getCollection(String nomFichier) throws IOException {

        String file = "src/main/resources/" + nomFichier;

        BufferedReader reader = new BufferedReader(new FileReader(file));
        List<String> lignes = reader.lines().collect(Collectors.toList());
        reader.close();

        return lignes;
    }
}