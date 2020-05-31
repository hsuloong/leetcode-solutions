class Solution1450 {
    private void PrintResult(final int expect, final int actual) {
        System.out.println((expect == actual ? "Correct" : "Wrong"));
    }
    public static void main(String[] args) {
        System.out.println("==========BeginTest==========");
        Solution1450 solution1450 = new Solution1450();
        solution1450.PrintResult(1, solution1450.busyStudent(new int[]{1,2,3}, new int[]{3,2,7}, 4));
        solution1450.PrintResult(1, solution1450.busyStudent(new int[]{4}, new int[]{4}, 4));
        solution1450.PrintResult(0, solution1450.busyStudent(new int[]{4}, new int[]{4}, 5));
        solution1450.PrintResult(0, solution1450.busyStudent(new int[]{1,1,1,1}, new int[]{1,3,2,4}, 7));
        solution1450.PrintResult(5, solution1450.busyStudent(new int[]{9,8,7,6,5,4,3,2,1}, new int[]{10,10,10,10,10,10,10,10,10}, 5));
        System.out.println("===========EndTest===========\n");
    }
    public int busyStudent(int[] startTime, int[] endTime, final int queryTime) {
        int counter = 0;
        for (int i = 0; i < startTime.length; i++) {
            if (queryTime >= startTime[i] && queryTime <= endTime[i]) {
                ++counter;
            }
        }
        return counter;
    }
};
