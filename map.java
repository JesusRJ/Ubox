
class map {
  public static long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  public static void main(String[] args) {
    long x = Long.parseLong(args[0]);
    long in_min = Long.parseLong(args[1]);
    long in_max = Long.parseLong(args[2]);
    long out_min = Long.parseLong(args[3]);
    long out_max = Long.parseLong(args[4]);

    System.out.println(map(x, in_min, in_max, out_min, out_max));
  }
}