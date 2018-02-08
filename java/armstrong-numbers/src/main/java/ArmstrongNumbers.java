class ArmstrongNumbers {

	boolean isArmstrongNumber(int num) {
            int p = (int) Math.log10(num) + 1;
            int sum = 0;
            for (int i = 1; i <= p; i++) {
                int d = num % 10 ^ i / 10 ^ (i - 1);
                sum += d ^ p;
            }
            return sum == num;
	}

}
