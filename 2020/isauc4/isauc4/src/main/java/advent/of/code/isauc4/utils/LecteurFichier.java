package advent.of.code.isauc4.utils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class LecteurFichier {

    private static String path = "src/main/resources/";

    public static List<String> getCollection(String nomFichier) throws IOException {
        String file = path + nomFichier;

        try (Stream<String> stream = Files.lines(Paths.get(file))) {
            return stream.collect(Collectors.toList());
        }
    }

    public static List<Integer> getCollectionInteger(String nomFichier) throws IOException {
        return getCollection(nomFichier).stream().map(Integer::valueOf).collect(Collectors.toList());
    }
}