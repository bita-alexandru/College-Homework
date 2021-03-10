package com.company;

import java.util.HashMap;

public class Main {

    public static void main(String[] args) {
        compulsory();
        boolean matrix[][] = optional(args);
        //bonus(matrix);
    }

    public static void compulsory() {
        String languages[] = {"C", "C++", "C#", "Python", "Go", "Rust", "JavaScript", "PHP", "Swift", "Java"};

        int n = (int) (Math.random() * 1_000_000);

        int result = (n * 3 + 0b10101 + 0xFF) * 6;

        while (result > 10) {
            int newResult = 0;

            while (result > 0) {
                newResult += (result % 10);
                result /= 10;
            }

            result = newResult;
        }

        System.out.println("Willy-nilly, this semester I will learn " + languages[result]);
    }

    public static boolean[][] optional(String args[]) {
        long nanoStart = System.nanoTime();

        if (args.length < 3) {
            System.out.println("Usage: number, number, one or more letters");
            System.exit(-1);
        }

        int n = Integer.parseInt(args[0]);
        int k = Integer.parseInt(args[1]);
        int m = args.length - 2;
        char alphabet[] = new char[m];

        for (int i = 0; i < m; i++) {
            alphabet[i] = args[i + 2].charAt(0);
        }

        String words[] = new String[n];

        System.out.println("The generated array");

        for (int i = 0; i < n; i++) {
            StringBuilder sb = new StringBuilder();

            for (int j = 0; j < k; j++) { // create a word
                int r = (int) (Math.random() * m);

                sb.append(alphabet[r]);
            }

            words[i] = sb.toString();

            System.out.println(words[i]);
        }

        boolean matrix[][] = new boolean[n][n];
        int neighbours[] = new int[n]; // ith word has neighbours[i] neighbours
        int maxNeighbours = 0;
        int minNeighbours = n;

        System.out.println("The matrix");

        for (int i = 0; i < n; i++) {
            HashMap<Character, Boolean> hm = new HashMap<Character, Boolean>();
            int count = 0;

            for (int x = 0; x < k; x++) {
                hm.put(words[i].charAt(x), true); // mark used letters
            }

            for (int j = i + 1; j < n; j++) {
                for (int x = 0; x < k; x++) {
                    if (hm.containsKey(words[j].charAt(x)) == true) { // ith word and jth word have a common letter
                        matrix[i][j] = true;
                        matrix[j][i] = true;
                        break;
                    }
                }
            }

            for (int j = 0; j < n; j++) { // display current matrix row
                if (matrix[i][j] == true) count++;
                if (n <= 30_000) System.out.print(matrix[i][j] == true ? 1 : 0);
            }
            System.out.println();

            neighbours[i] = count;

            if (count > maxNeighbours) maxNeighbours = count;
            if (count < minNeighbours) minNeighbours = count;
        }

        if (minNeighbours == maxNeighbours) System.out.println("All words have the same number of neighbours");
        else {
            System.out.println("Words with the most number of neighbours");
            for (int i = 0; i < n; i++)
                if (neighbours[i] == maxNeighbours) System.out.println(words[i]);

            System.out.println("Words with the least number of neighbours");
            for (int i = 0; i < n; i++)
                if (neighbours[i] == minNeighbours) System.out.println(words[i]);
        }

        if (n > 30_000) {
            long nanoEnd = System.nanoTime();

            System.out.println("Running time: " + (nanoEnd - nanoStart) + " nanoseconds");
        }

        return matrix;
    }

    public static void dfs(int node, boolean matrix[][], boolean visited[]) {
        visited[node] = true;
        System.out.print(node + " ");

        for (int i = 0; i < matrix.length; i++) {
            if (visited[i] == false && matrix[i][node] == true) {
                dfs(i, matrix, visited);
            }
        }
    }

    public static void bonus(boolean matrix[][]) {
        int n = matrix.length;
        boolean visited[] = new boolean[n];
        int components = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] == false) {
                components++;

                System.out.print("Connected component no. " + components + ": ");
                dfs(i, matrix, visited);
                System.out.println();
            }
        }

        System.out.println((components == 1) ? "The graph is connected" : "The graph is not connected");
    }
}
