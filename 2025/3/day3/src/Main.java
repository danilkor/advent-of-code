void main() throws IOException {
    p2();
}

void p2() throws IOException {
    Path path = java.nio.file.Path.of("input.txt");
    List<String> lines = Files.readAllLines(path);
    long answer = 0;

    int digits = 12;

    for (String line : lines) {
        char[] ca = line.toCharArray();
        for (int i = 0; i < ca.length; i++) {
            ca[i] = (char) (ca[i] - '0');
        }

        int[] numbers = new int[ca.length];
        for (int i = 0; i < numbers.length; i++) {
            numbers[i] = 0;
        }
        int li = -1;
        for (int i = 0; i < digits; i++) {

            int cbc = 0;
            int pr = numbers.length - (digits - 1 - i);
            for (int j = li+1; j < pr; j++) {
                if (ca[j] > cbc) {
                    cbc = ca[j];
                    li = j;
                }
            }
            numbers[li] = cbc;
        }


        String temp = "";
        for (int i = 0; i < numbers.length; i++) {
            if (numbers[i] != 0) {
                System.out.print(numbers[i]);
                temp = temp + numbers[i];
            }
        }
        System.out.println();
        answer = Math.addExact(answer, Long.parseLong(temp));

    }
    System.out.println(answer);
}


void p1() throws IOException {
    Path path = java.nio.file.Path.of("input.txt");
    List<String> lines = Files.readAllLines(path);
    long answer = 0;
    for (String line : lines) {
        int fd = 0;
        int sd = 0;
        int fi = -1;
        int si = -1;
        char[] ca = line.toCharArray();
        for (int i = 0; i < ca.length; i++) {
            if ((int) ca[i] - '0' > fd) {
                fd = ca[i] - '0';
                fi = i;
            }
        }

        if (fi < ca.length - 1) {
            for (int i = fi + 1; i < ca.length; i++) {
                if ((int) ca[i] - '0' > sd && i != fi) {
                    sd = ca[i] - '0';
                    si = i;
                }
            }
        } else {
            for (int i = 0; i < ca.length; i++) {
                if ((int) ca[i] - '0' > sd && i != fi) {
                    sd = ca[i] - '0';
                    si = i;
                }
            }
        }
        System.out.println("FD: " + fd);
        System.out.println("SD: " + sd);
        if (si > fi) {
            answer += sd + (fd * 10);
        } else {
            answer += fd + (sd * 10);
        }
    }
    System.out.println(answer);
}