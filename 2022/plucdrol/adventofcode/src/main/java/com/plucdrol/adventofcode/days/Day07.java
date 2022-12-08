package com.plucdrol.adventofcode.days;

import lombok.Getter;

import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;

@Getter
public class Day07 extends Day {
    private final Long answer1;
    private final Long answer2;
    private final Set<Directory> directories = new HashSet<>();
    private Directory baseDirectory;

    public Day07(String input) {
        super(7);

        parseToDirectories(input);

        answer1 = directories.stream()
                .filter(directory -> directory.getSize() <= 100000)
                .mapToLong(Directory::getSize)
                .sum();

        var freeSpace = 70000000 - baseDirectory.getSize();
        answer2 = directories.stream()
                .filter(directory -> directory.getSize() + freeSpace >= 30000000)
                .min(Comparator.comparingLong(Directory::getSize))
                .orElseThrow().getSize();
    }

    private void parseToDirectories(String input) {
        Directory currentDirectory = null;

        for (var line : input.split("\n")) {
            var splitLine = line.split(" ");
            if (splitLine[0].equals("$")) {
                if (splitLine[1].equals("cd")) {
                    if (splitLine[2].equals("..")) {
                        currentDirectory = currentDirectory.getParent();
                    } else {
                        Directory changedDirectory;
                        if (currentDirectory != null) {
                            changedDirectory = currentDirectory.getSubDirectory(splitLine[2]);
                            currentDirectory.addFile(changedDirectory);
                        } else {
                            changedDirectory = new Directory(splitLine[2], null);
                            baseDirectory = changedDirectory;
                        }
                        directories.add(changedDirectory);
                        currentDirectory = changedDirectory;
                    }
                }
            } else if (splitLine[0].equals("dir")) {
                currentDirectory.addFile(new Directory(splitLine[1], currentDirectory));

            } else if (Character.isDigit(splitLine[0].charAt(0))) {
                var file = new ConcreteFile(splitLine[1], Long.parseLong(splitLine[0]));
                currentDirectory.addFile(file);

            } else {
                throw new RuntimeException(String.format("unexpected value (line: %s)", line));
            }
        }
    }

    @Getter
    static abstract class File {
        private final String name;

        public File(String name) {
            this.name = name;
        }

        public abstract long getSize();

        @Override
        public String toString() {
            return String.format("name: %s; size: %s", getName(), getSize());
        }
    }

    @Getter
    static class ConcreteFile extends File {
        private final long size;

        public ConcreteFile(String name, Long size) {
            super(name);
            this.size = size;
        }
    }

    @Getter
    static class Directory extends File {
        private final Directory parent;
        private final Set<File> files;

        public Directory(String name, Directory parent) {
            super(name);
            this.parent = parent;
            this.files = new HashSet<>();
        }

        public void addFile(File file) {
            if (files.stream().noneMatch(file1 -> file1.getName().equals(file.getName()))) {
                files.add(file);
            }
        }

        public Directory getSubDirectory(String name) {
            return files.stream().filter(file -> file instanceof Directory)
                    .filter(dir -> dir.getName().equals(name))
                    .map(dir -> (Directory) dir)
                    .findFirst()
                    .orElseGet(() -> new Directory(name, this));
        }

        public long getSize() {
            return files.stream().mapToLong(File::getSize).sum();
        }

        @Override
        public String toString() {
            return String.format("%s; file count: %s", super.toString(), files.size());
        }
    }
}
